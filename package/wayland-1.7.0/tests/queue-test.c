/*
 * Copyright © 2012 Jonas Ådahl
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#include "wayland-client.h"
#include "wayland-server.h"
#include "test-runner.h"
#include "test-compositor.h"

#define ARRAY_LENGTH(a) (sizeof (a) / sizeof (a)[0])

static void
registry_handle_global(void *data, struct wl_registry *registry,
		       uint32_t id, const char *interface, uint32_t version)
{
	int *pcounter = data;
	(*pcounter)++;
	assert(*pcounter == 1);
	wl_registry_destroy(registry);
}

static const struct wl_registry_listener registry_listener = {
	registry_handle_global,
	NULL
};

/* Test that destroying a proxy object doesn't result in any more
 * callback being invoked, even though were many queued. */
static void
client_test_proxy_destroy(void)
{
	struct wl_display *display;
	struct wl_registry *registry;
	int counter = 0;

	display = wl_display_connect(NULL);
	assert(display);

	registry = wl_display_get_registry(display);
	assert(registry != NULL);
	wl_registry_add_listener(registry, &registry_listener,
				 &counter);
	assert(wl_display_roundtrip(display) != -1);

	assert(counter == 1);

	/* don't destroy the registry, we have already destroyed them
	 * in the global handler */
	wl_display_disconnect(display);
}

struct multiple_queues_state {
	struct wl_display *display;
	struct wl_callback* callback2;
	bool done;
};

static void
sync_callback(void *data, struct wl_callback *callback, uint32_t serial)
{
	struct multiple_queues_state *state = data;

	state->done = true;
	wl_callback_destroy(callback);

	wl_display_dispatch_pending(state->display);

	wl_callback_destroy(state->callback2);
}

static const struct wl_callback_listener sync_listener = {
	sync_callback
};

/* Test that when receiving the first of two synchronization
 * callback events, destroying the second one doesn't cause any
 * errors even if the delete_id event is handled out of order. */
static void
client_test_multiple_queues(void)
{
	struct wl_event_queue *queue;
	struct wl_callback *callback1;
	struct multiple_queues_state state;
	int ret = 0;

	state.display = wl_display_connect(NULL);
	assert(state.display);

	queue = wl_display_create_queue(state.display);
	assert(queue);

	state.done = false;
	callback1 = wl_display_sync(state.display);
	assert(callback1 != NULL);
	wl_callback_add_listener(callback1, &sync_listener, &state);
	wl_proxy_set_queue((struct wl_proxy *) callback1, queue);

	state.callback2 = wl_display_sync(state.display);
	assert(state.callback2 != NULL);
	wl_callback_add_listener(state.callback2, &sync_listener, NULL);
	wl_proxy_set_queue((struct wl_proxy *) state.callback2, queue);

	wl_display_flush(state.display);

	while (!state.done && !ret)
		ret = wl_display_dispatch_queue(state.display, queue);

	wl_event_queue_destroy(queue);
	wl_display_disconnect(state.display);

	exit(ret == -1 ? -1 : 0);
}

static void
sync_callback_roundtrip(void *data, struct wl_callback *callback, uint32_t serial)
{
	bool *done = data;
	*done = true;
}

static const struct wl_callback_listener sync_listener_roundtrip = {
	sync_callback_roundtrip
};

/* Test that doing a roundtrip on a queue only the events on that
 * queue get dispatched. */
static void
client_test_queue_roundtrip(void)
{
	struct wl_event_queue *queue;
	struct wl_callback *callback1;
	struct wl_callback *callback2;
	struct wl_display *display;
	bool done1 = false;
	bool done2 = false;

	display = wl_display_connect(NULL);
	assert(display);

	queue = wl_display_create_queue(display);
	assert(queue);

	/* arm a callback on the default queue */
	callback1 = wl_display_sync(display);
	assert(callback1 != NULL);
	wl_callback_add_listener(callback1, &sync_listener_roundtrip, &done1);

	/* arm a callback on the other queue */
	callback2 = wl_display_sync(display);
	assert(callback2 != NULL);
	wl_callback_add_listener(callback2, &sync_listener_roundtrip, &done2);
	wl_proxy_set_queue((struct wl_proxy *) callback2, queue);

	/* roundtrip on default queue must not dispatch the other queue. */
	wl_display_roundtrip(display);
	assert(done1 == true);
	assert(done2 == false);

	/* re-arm the sync callback on the default queue, so we see that
	 * wl_display_roundtrip_queue() does not dispatch the default queue. */
	wl_callback_destroy(callback1);
	done1 = false;
	callback1 = wl_display_sync(display);
	assert(callback1 != NULL);
	wl_callback_add_listener(callback1, &sync_listener_roundtrip, &done1);

	wl_display_roundtrip_queue(display, queue);
	assert(done1 == false);
	assert(done2 == true);

	wl_callback_destroy(callback1);
	wl_callback_destroy(callback2);
	wl_event_queue_destroy(queue);

	wl_display_disconnect(display);
}

static void
dummy_bind(struct wl_client *client,
	   void *data, uint32_t version, uint32_t id)
{
}

TEST(queue_proxy_destroy)
{
	struct display *d;
	const struct wl_interface *dummy_interfaces[] = {
		&wl_seat_interface,
		&wl_pointer_interface,
		&wl_keyboard_interface,
		&wl_surface_interface
	};
	unsigned int i;

	d = display_create();

	for (i = 0; i < ARRAY_LENGTH(dummy_interfaces); i++)
		wl_global_create(d->wl_display, dummy_interfaces[i],
				 dummy_interfaces[i]->version,
				 NULL, dummy_bind);

	test_set_timeout(2);

	client_create(d, client_test_proxy_destroy);
	display_run(d);

	display_destroy(d);
}

TEST(queue_multiple_queues)
{
	struct display *d = display_create();

	test_set_timeout(2);

	client_create(d, client_test_multiple_queues);
	display_run(d);

	display_destroy(d);
}

TEST(queue_roundtrip)
{
	struct display *d = display_create();

	test_set_timeout(2);

	client_create(d, client_test_queue_roundtrip);
	display_run(d);

	display_destroy(d);
}
