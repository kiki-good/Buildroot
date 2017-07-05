
#ifndef _AWF_EVENT_H_
#define _AWF_EVENT_H_


#define AWF_PRINT_STATUS(_arg)			\
		do {				\
			if (awf_mode)		\
			{			\
				awf_event_t t;		\
				t.status = _arg;	\
				fwrite(&t, sizeof(awf_event_t), 1, stdout);	\
			}			\
		} while (0)

typedef struct awf_event_s	awf_event_t;
typedef enum conn_status_e	conn_status_e;

enum conn_status_e {
	ASSOCIATED,	// associated
	AUTHENTICATED,	// authenticated
	AUTHORIZED,	// authorized
	DISCONNECTED,
	NETWORK_NOT_FOUND,
	WPA_HANDSHAKE_FAIL,
	AUTH_FAILED,
	CONFIG_MISMATCH,
	HIDDEN_SSID,
};

struct awf_event_s
{
	conn_status_e status;
};

#endif
