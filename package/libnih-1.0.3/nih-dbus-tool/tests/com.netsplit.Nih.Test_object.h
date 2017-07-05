/* libnih
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifndef LIBNIH_TESTS_COM_NETSPLIT_NIH_TEST_OBJECT_H
#define LIBNIH_TESTS_COM_NETSPLIT_NIH_TEST_OBJECT_H

#include <dbus/dbus.h>

#include <stdint.h>

#include <nih/macros.h>

#include <nih-dbus/dbus_interface.h>
#include <nih-dbus/dbus_message.h>


typedef struct my_test_struct_to_str_input {
	char *   item0;
	uint32_t item1;
} MyTestStructToStrInput;

typedef struct my_test_str_to_struct_output {
	char *   item0;
	uint32_t item1;
} MyTestStrToStructOutput;

typedef struct my_test_struct_array_to_str_input_element {
	char *   item0;
	uint32_t item1;
} MyTestStructArrayToStrInputElement;

typedef struct my_test_str_to_struct_array_output_element {
	char *   item0;
	uint32_t item1;
} MyTestStrToStructArrayOutputElement;

typedef struct my_test_dict_entry_array_to_str_input_element {
	char *   item0;
	uint32_t item1;
} MyTestDictEntryArrayToStrInputElement;

typedef struct my_test_str_to_dict_entry_array_output_element {
	char *   item0;
	uint32_t item1;
} MyTestStrToDictEntryArrayOutputElement;

typedef struct my_test_new_struct_value {
	char *   item0;
	uint32_t item1;
} MyTestNewStructValue;

typedef struct my_test_new_struct_array_value_element {
	char *   item0;
	uint32_t item1;
} MyTestNewStructArrayValueElement;

typedef struct my_test_new_dict_entry_array_value_element {
	char *   item0;
	uint32_t item1;
} MyTestNewDictEntryArrayValueElement;

typedef struct my_test_structure {
	char *   item0;
	uint32_t item1;
} MyTestStructure;

typedef struct my_test_struct_array_element {
	char *   item0;
	uint32_t item1;
} MyTestStructArrayElement;

typedef struct my_test_dict_entry_array_element {
	char *   item0;
	uint32_t item1;
} MyTestDictEntryArrayElement;


NIH_BEGIN_EXTERN

extern const NihDBusInterface  my_com_netsplit_Nih_Test;
extern const NihDBusInterface *my_interfaces[];


int my_test_async_method_reply         (NihDBusMessage *message, const char *output)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_byte              (DBusConnection *connection, const char *origin_path, uint8_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_boolean           (DBusConnection *connection, const char *origin_path, int value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_int16             (DBusConnection *connection, const char *origin_path, int16_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_uint16            (DBusConnection *connection, const char *origin_path, uint16_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_int32             (DBusConnection *connection, const char *origin_path, int32_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_uint32            (DBusConnection *connection, const char *origin_path, uint32_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_int64             (DBusConnection *connection, const char *origin_path, int64_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_uint64            (DBusConnection *connection, const char *origin_path, uint64_t value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_double            (DBusConnection *connection, const char *origin_path, double value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_string            (DBusConnection *connection, const char *origin_path, const char *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_object_path       (DBusConnection *connection, const char *origin_path, const char *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_signature         (DBusConnection *connection, const char *origin_path, const char *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_struct            (DBusConnection *connection, const char *origin_path, const MyTestNewStructValue *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_int32_array       (DBusConnection *connection, const char *origin_path, const int32_t *value, size_t value_len)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_str_array         (DBusConnection *connection, const char *origin_path, char * const *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_int32_array_array (DBusConnection *connection, const char *origin_path, int32_t * const *value, const size_t *value_len)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_struct_array      (DBusConnection *connection, const char *origin_path, MyTestNewStructArrayValueElement * const *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_dict_entry_array  (DBusConnection *connection, const char *origin_path, MyTestNewDictEntryArrayValueElement * const *value)
	__attribute__ ((warn_unused_result));
int my_test_emit_new_unix_fd           (DBusConnection *connection, const char *origin_path, int value)
	__attribute__ ((warn_unused_result));

NIH_END_EXTERN

#endif /* LIBNIH_TESTS_COM_NETSPLIT_NIH_TEST_OBJECT_H */
