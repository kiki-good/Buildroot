/* libnih
 *
 * tests/com.netsplit.Nih.Test_proxy.c - auto-generated D-Bus bindings
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */


#include <dbus/dbus.h>

#include <stdint.h>
#include <string.h>

#include <nih/macros.h>
#include <nih/alloc.h>
#include <nih/string.h>
#include <nih/logging.h>
#include <nih/error.h>

#include <nih-dbus/dbus_error.h>
#include <nih-dbus/dbus_message.h>
#include <nih-dbus/dbus_pending_data.h>
#include <nih-dbus/dbus_proxy.h>
#include <nih-dbus/errors.h>

#include "tests/com.netsplit.Nih.Test_proxy.h"


/* Prototypes for static functions */
static void              proxy_com_netsplit_Nih_Test_OrdinaryMethod_notify        (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_NamelessMethod_notify        (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_AsyncMethod_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_ByteToStr_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToByte_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_BooleanToStr_notify          (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToBoolean_notify          (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_Int16ToStr_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToInt16_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_UInt16ToStr_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToUInt16_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_Int32ToStr_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToInt32_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_UInt32ToStr_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToUInt32_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_Int64ToStr_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToInt64_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_UInt64ToStr_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToUInt64_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_DoubleToStr_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToDouble_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_ObjectPathToStr_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToObjectPath_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_SignatureToStr_notify        (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToSignature_notify        (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StructToStr_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToStruct_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_Int32ArrayToStr_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToInt32Array_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrArrayToStr_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToStrArray_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_Int32ArrayArrayToStr_notify  (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToInt32ArrayArray_notify  (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StructArrayToStr_notify      (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToStructArray_notify      (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_DictEntryArrayToStr_notify   (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToDictEntryArray_notify   (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_UnixFdToStr_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_StrToUnixFd_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewByte_signal               (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewBoolean_signal            (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewInt16_signal              (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewUInt16_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewInt32_signal              (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewUInt32_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewInt64_signal              (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewUInt64_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewDouble_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewString_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewObjectPath_signal         (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewSignature_signal          (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewStruct_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewInt32Array_signal         (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewStrArray_signal           (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewInt32ArrayArray_signal    (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewStructArray_signal        (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewDictEntryArray_signal     (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult proxy_com_netsplit_Nih_Test_NewUnixFd_signal             (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static void              proxy_com_netsplit_Nih_Test_byte_get_notify              (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_byte_set_notify              (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_boolean_get_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_boolean_set_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int16_get_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int16_set_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_uint16_get_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_uint16_set_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int32_get_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int32_set_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_uint32_get_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_uint32_set_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int64_get_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int64_set_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_uint64_get_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_uint64_set_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_double_get_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_double_set_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_string_get_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_string_set_notify            (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_object_path_get_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_object_path_set_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_signature_get_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_signature_set_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_structure_get_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_structure_set_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int32_array_get_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int32_array_set_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_str_array_get_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_str_array_set_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int32_array_array_get_notify (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_int32_array_array_set_notify (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_struct_array_get_notify      (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_struct_array_set_notify      (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_dict_entry_array_get_notify  (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_dict_entry_array_set_notify  (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_unix_fd_get_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_unix_fd_set_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              proxy_com_netsplit_Nih_Test_get_all_notify               (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);


static const NihDBusArg proxy_com_netsplit_Nih_Test_OrdinaryMethod_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NamelessMethod_method_args[] = {
	{ NULL,   "s", NIH_DBUS_ARG_IN  },
	{ NULL,   "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_AsyncMethod_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_ByteToStr_method_args[] = {
	{ "input",  "y", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToByte_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "y", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_BooleanToStr_method_args[] = {
	{ "input",  "b", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToBoolean_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "b", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_Int16ToStr_method_args[] = {
	{ "input",  "n", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToInt16_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "n", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_UInt16ToStr_method_args[] = {
	{ "input",  "q", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToUInt16_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "q", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_Int32ToStr_method_args[] = {
	{ "input",  "i", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToInt32_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "i", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_UInt32ToStr_method_args[] = {
	{ "input",  "u", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToUInt32_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "u", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_Int64ToStr_method_args[] = {
	{ "input",  "x", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToInt64_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "x", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_UInt64ToStr_method_args[] = {
	{ "input",  "t", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToUInt64_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "t", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_DoubleToStr_method_args[] = {
	{ "input",  "d", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToDouble_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "d", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_ObjectPathToStr_method_args[] = {
	{ "input",  "o", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToObjectPath_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_SignatureToStr_method_args[] = {
	{ "input",  "g", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToSignature_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "g", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StructToStr_method_args[] = {
	{ "input",  "(su)", NIH_DBUS_ARG_IN  },
	{ "output", "s",    NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToStruct_method_args[] = {
	{ "input",  "s",    NIH_DBUS_ARG_IN  },
	{ "output", "(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_Int32ArrayToStr_method_args[] = {
	{ "input",  "ai", NIH_DBUS_ARG_IN  },
	{ "output", "s",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToInt32Array_method_args[] = {
	{ "input",  "s",  NIH_DBUS_ARG_IN  },
	{ "output", "ai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrArrayToStr_method_args[] = {
	{ "input",  "as", NIH_DBUS_ARG_IN  },
	{ "output", "s",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToStrArray_method_args[] = {
	{ "input",  "s",  NIH_DBUS_ARG_IN  },
	{ "output", "as", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method_args[] = {
	{ "input",  "aai", NIH_DBUS_ARG_IN  },
	{ "output", "s",   NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToInt32ArrayArray_method_args[] = {
	{ "input",  "s",   NIH_DBUS_ARG_IN  },
	{ "output", "aai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StructArrayToStr_method_args[] = {
	{ "input",  "a(su)", NIH_DBUS_ARG_IN  },
	{ "output", "s",     NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToStructArray_method_args[] = {
	{ "input",  "s",     NIH_DBUS_ARG_IN  },
	{ "output", "a(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_DictEntryArrayToStr_method_args[] = {
	{ "input",  "a{su}", NIH_DBUS_ARG_IN  },
	{ "output", "s",     NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToDictEntryArray_method_args[] = {
	{ "input",  "s",     NIH_DBUS_ARG_IN  },
	{ "output", "a{su}", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_UnixFdToStr_method_args[] = {
	{ "input",  "h", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_StrToUnixFd_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "h", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusMethod proxy_com_netsplit_Nih_Test_methods[] = {
	{ "OrdinaryMethod",       proxy_com_netsplit_Nih_Test_OrdinaryMethod_method_args,       NULL },
	{ "NamelessMethod",       proxy_com_netsplit_Nih_Test_NamelessMethod_method_args,       NULL },
	{ "AsyncMethod",          proxy_com_netsplit_Nih_Test_AsyncMethod_method_args,          NULL },
	{ "ByteToStr",            proxy_com_netsplit_Nih_Test_ByteToStr_method_args,            NULL },
	{ "StrToByte",            proxy_com_netsplit_Nih_Test_StrToByte_method_args,            NULL },
	{ "BooleanToStr",         proxy_com_netsplit_Nih_Test_BooleanToStr_method_args,         NULL },
	{ "StrToBoolean",         proxy_com_netsplit_Nih_Test_StrToBoolean_method_args,         NULL },
	{ "Int16ToStr",           proxy_com_netsplit_Nih_Test_Int16ToStr_method_args,           NULL },
	{ "StrToInt16",           proxy_com_netsplit_Nih_Test_StrToInt16_method_args,           NULL },
	{ "UInt16ToStr",          proxy_com_netsplit_Nih_Test_UInt16ToStr_method_args,          NULL },
	{ "StrToUInt16",          proxy_com_netsplit_Nih_Test_StrToUInt16_method_args,          NULL },
	{ "Int32ToStr",           proxy_com_netsplit_Nih_Test_Int32ToStr_method_args,           NULL },
	{ "StrToInt32",           proxy_com_netsplit_Nih_Test_StrToInt32_method_args,           NULL },
	{ "UInt32ToStr",          proxy_com_netsplit_Nih_Test_UInt32ToStr_method_args,          NULL },
	{ "StrToUInt32",          proxy_com_netsplit_Nih_Test_StrToUInt32_method_args,          NULL },
	{ "Int64ToStr",           proxy_com_netsplit_Nih_Test_Int64ToStr_method_args,           NULL },
	{ "StrToInt64",           proxy_com_netsplit_Nih_Test_StrToInt64_method_args,           NULL },
	{ "UInt64ToStr",          proxy_com_netsplit_Nih_Test_UInt64ToStr_method_args,          NULL },
	{ "StrToUInt64",          proxy_com_netsplit_Nih_Test_StrToUInt64_method_args,          NULL },
	{ "DoubleToStr",          proxy_com_netsplit_Nih_Test_DoubleToStr_method_args,          NULL },
	{ "StrToDouble",          proxy_com_netsplit_Nih_Test_StrToDouble_method_args,          NULL },
	{ "ObjectPathToStr",      proxy_com_netsplit_Nih_Test_ObjectPathToStr_method_args,      NULL },
	{ "StrToObjectPath",      proxy_com_netsplit_Nih_Test_StrToObjectPath_method_args,      NULL },
	{ "SignatureToStr",       proxy_com_netsplit_Nih_Test_SignatureToStr_method_args,       NULL },
	{ "StrToSignature",       proxy_com_netsplit_Nih_Test_StrToSignature_method_args,       NULL },
	{ "StructToStr",          proxy_com_netsplit_Nih_Test_StructToStr_method_args,          NULL },
	{ "StrToStruct",          proxy_com_netsplit_Nih_Test_StrToStruct_method_args,          NULL },
	{ "Int32ArrayToStr",      proxy_com_netsplit_Nih_Test_Int32ArrayToStr_method_args,      NULL },
	{ "StrToInt32Array",      proxy_com_netsplit_Nih_Test_StrToInt32Array_method_args,      NULL },
	{ "StrArrayToStr",        proxy_com_netsplit_Nih_Test_StrArrayToStr_method_args,        NULL },
	{ "StrToStrArray",        proxy_com_netsplit_Nih_Test_StrToStrArray_method_args,        NULL },
	{ "Int32ArrayArrayToStr", proxy_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method_args, NULL },
	{ "StrToInt32ArrayArray", proxy_com_netsplit_Nih_Test_StrToInt32ArrayArray_method_args, NULL },
	{ "StructArrayToStr",     proxy_com_netsplit_Nih_Test_StructArrayToStr_method_args,     NULL },
	{ "StrToStructArray",     proxy_com_netsplit_Nih_Test_StrToStructArray_method_args,     NULL },
	{ "DictEntryArrayToStr",  proxy_com_netsplit_Nih_Test_DictEntryArrayToStr_method_args,  NULL },
	{ "StrToDictEntryArray",  proxy_com_netsplit_Nih_Test_StrToDictEntryArray_method_args,  NULL },
	{ "UnixFdToStr",          proxy_com_netsplit_Nih_Test_UnixFdToStr_method_args,          NULL },
	{ "StrToUnixFd",          proxy_com_netsplit_Nih_Test_StrToUnixFd_method_args,          NULL },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewByte_signal_args[] = {
	{ "value", "y", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewBoolean_signal_args[] = {
	{ "value", "b", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewInt16_signal_args[] = {
	{ "value", "n", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewUInt16_signal_args[] = {
	{ "value", "q", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewInt32_signal_args[] = {
	{ "value", "i", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewUInt32_signal_args[] = {
	{ "value", "u", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewInt64_signal_args[] = {
	{ "value", "x", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewUInt64_signal_args[] = {
	{ "value", "t", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewDouble_signal_args[] = {
	{ "value", "d", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewString_signal_args[] = {
	{ "value", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewObjectPath_signal_args[] = {
	{ "value", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewSignature_signal_args[] = {
	{ "value", "g", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewStruct_signal_args[] = {
	{ "value", "(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewInt32Array_signal_args[] = {
	{ "value", "ai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewStrArray_signal_args[] = {
	{ "value", "as", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewInt32ArrayArray_signal_args[] = {
	{ "value", "aai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewStructArray_signal_args[] = {
	{ "value", "a(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewDictEntryArray_signal_args[] = {
	{ "value", "a{su}", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg proxy_com_netsplit_Nih_Test_NewUnixFd_signal_args[] = {
	{ "value", "h", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusSignal proxy_com_netsplit_Nih_Test_signals[] = {
	{ "NewByte",            proxy_com_netsplit_Nih_Test_NewByte_signal_args,            proxy_com_netsplit_Nih_Test_NewByte_signal            },
	{ "NewBoolean",         proxy_com_netsplit_Nih_Test_NewBoolean_signal_args,         proxy_com_netsplit_Nih_Test_NewBoolean_signal         },
	{ "NewInt16",           proxy_com_netsplit_Nih_Test_NewInt16_signal_args,           proxy_com_netsplit_Nih_Test_NewInt16_signal           },
	{ "NewUInt16",          proxy_com_netsplit_Nih_Test_NewUInt16_signal_args,          proxy_com_netsplit_Nih_Test_NewUInt16_signal          },
	{ "NewInt32",           proxy_com_netsplit_Nih_Test_NewInt32_signal_args,           proxy_com_netsplit_Nih_Test_NewInt32_signal           },
	{ "NewUInt32",          proxy_com_netsplit_Nih_Test_NewUInt32_signal_args,          proxy_com_netsplit_Nih_Test_NewUInt32_signal          },
	{ "NewInt64",           proxy_com_netsplit_Nih_Test_NewInt64_signal_args,           proxy_com_netsplit_Nih_Test_NewInt64_signal           },
	{ "NewUInt64",          proxy_com_netsplit_Nih_Test_NewUInt64_signal_args,          proxy_com_netsplit_Nih_Test_NewUInt64_signal          },
	{ "NewDouble",          proxy_com_netsplit_Nih_Test_NewDouble_signal_args,          proxy_com_netsplit_Nih_Test_NewDouble_signal          },
	{ "NewString",          proxy_com_netsplit_Nih_Test_NewString_signal_args,          proxy_com_netsplit_Nih_Test_NewString_signal          },
	{ "NewObjectPath",      proxy_com_netsplit_Nih_Test_NewObjectPath_signal_args,      proxy_com_netsplit_Nih_Test_NewObjectPath_signal      },
	{ "NewSignature",       proxy_com_netsplit_Nih_Test_NewSignature_signal_args,       proxy_com_netsplit_Nih_Test_NewSignature_signal       },
	{ "NewStruct",          proxy_com_netsplit_Nih_Test_NewStruct_signal_args,          proxy_com_netsplit_Nih_Test_NewStruct_signal          },
	{ "NewInt32Array",      proxy_com_netsplit_Nih_Test_NewInt32Array_signal_args,      proxy_com_netsplit_Nih_Test_NewInt32Array_signal      },
	{ "NewStrArray",        proxy_com_netsplit_Nih_Test_NewStrArray_signal_args,        proxy_com_netsplit_Nih_Test_NewStrArray_signal        },
	{ "NewInt32ArrayArray", proxy_com_netsplit_Nih_Test_NewInt32ArrayArray_signal_args, proxy_com_netsplit_Nih_Test_NewInt32ArrayArray_signal },
	{ "NewStructArray",     proxy_com_netsplit_Nih_Test_NewStructArray_signal_args,     proxy_com_netsplit_Nih_Test_NewStructArray_signal     },
	{ "NewDictEntryArray",  proxy_com_netsplit_Nih_Test_NewDictEntryArray_signal_args,  proxy_com_netsplit_Nih_Test_NewDictEntryArray_signal  },
	{ "NewUnixFd",          proxy_com_netsplit_Nih_Test_NewUnixFd_signal_args,          proxy_com_netsplit_Nih_Test_NewUnixFd_signal          },
	{ NULL }
};

static const NihDBusProperty proxy_com_netsplit_Nih_Test_properties[] = {
	{ "byte",              "y",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "boolean",           "b",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "int16",             "n",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "uint16",            "q",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "int32",             "i",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "uint32",            "u",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "int64",             "x",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "uint64",            "t",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "double",            "d",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "string",            "s",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "object_path",       "o",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "signature",         "g",     NIH_DBUS_READWRITE, NULL, NULL },
	{ "structure",         "(su)",  NIH_DBUS_READWRITE, NULL, NULL },
	{ "int32_array",       "ai",    NIH_DBUS_READWRITE, NULL, NULL },
	{ "str_array",         "as",    NIH_DBUS_READWRITE, NULL, NULL },
	{ "int32_array_array", "aai",   NIH_DBUS_READWRITE, NULL, NULL },
	{ "struct_array",      "a(su)", NIH_DBUS_READWRITE, NULL, NULL },
	{ "dict_entry_array",  "a{su}", NIH_DBUS_READWRITE, NULL, NULL },
	{ "unix_fd",           "h",     NIH_DBUS_READWRITE, NULL, NULL },
	{ NULL }
};

const NihDBusInterface proxy_com_netsplit_Nih_Test = {
	"com.netsplit.Nih.Test",
	proxy_com_netsplit_Nih_Test_methods,
	proxy_com_netsplit_Nih_Test_signals,
	proxy_com_netsplit_Nih_Test_properties
};

const NihDBusInterface *proxy_interfaces[] = {
	&proxy_com_netsplit_Nih_Test,
	NULL
};


DBusPendingCall *
proxy_test_ordinary_method (NihDBusProxy *               proxy,
                            const char *                 input,
                            ProxyTestOrdinaryMethodReply handler,
                            NihDBusErrorHandler          error_handler,
                            void *                       data,
                            int                          timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "OrdinaryMethod");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_OrdinaryMethod_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_OrdinaryMethod_notify (DBusPendingCall *   pending_call,
                                                   NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestOrdinaryMethodReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_ordinary_method_sync (const void *  parent,
                                 NihDBusProxy *proxy,
                                 const char *  input,
                                 char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "OrdinaryMethod");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_nameless_method (NihDBusProxy *               proxy,
                            const char *                 arg1,
                            ProxyTestNamelessMethodReply handler,
                            NihDBusErrorHandler          error_handler,
                            void *                       data,
                            int                          timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (arg1 != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "NamelessMethod");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &arg1)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_NamelessMethod_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_NamelessMethod_notify (DBusPendingCall *   pending_call,
                                                   NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          arg2;
	const char *    arg2_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &arg2_dbus);

		arg2 = nih_strdup (message, arg2_dbus);
		if (! arg2) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestNamelessMethodReply)pending_data->handler) (pending_data->data, message, arg2);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_nameless_method_sync (const void *  parent,
                                 NihDBusProxy *proxy,
                                 const char *  arg1,
                                 char **       arg2)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          arg2_local;
	const char *    arg2_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (arg1 != NULL);
	nih_assert (arg2 != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "NamelessMethod");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &arg1)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &arg2_local_dbus);

		arg2_local = nih_strdup (parent, arg2_local_dbus);
		if (! arg2_local) {
			*arg2 = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*arg2 = arg2_local;
	enomem: __attribute__ ((unused));
	} while (! *arg2);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (arg2_local);
		*arg2 = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_async_method (NihDBusProxy *            proxy,
                         const char *              input,
                         ProxyTestAsyncMethodReply handler,
                         NihDBusErrorHandler       error_handler,
                         void *                    data,
                         int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "AsyncMethod");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_AsyncMethod_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_AsyncMethod_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestAsyncMethodReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_async_method_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              const char *  input,
                              char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "AsyncMethod");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_byte_to_str (NihDBusProxy *          proxy,
                        uint8_t                 input,
                        ProxyTestByteToStrReply handler,
                        NihDBusErrorHandler     error_handler,
                        void *                  data,
                        int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "ByteToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint8_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BYTE, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_ByteToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_ByteToStr_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestByteToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_byte_to_str_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             uint8_t       input,
                             char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "ByteToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint8_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BYTE, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_byte (NihDBusProxy *          proxy,
                        const char *            input,
                        ProxyTestStrToByteReply handler,
                        NihDBusErrorHandler     error_handler,
                        void *                  data,
                        int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToByte");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToByte_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToByte_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	uint8_t         output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a uint8_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BYTE) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToByteReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_byte_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             const char *  input,
                             uint8_t *     output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	uint8_t         output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToByte");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a uint8_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BYTE) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_boolean_to_str (NihDBusProxy *             proxy,
                           int                        input,
                           ProxyTestBooleanToStrReply handler,
                           NihDBusErrorHandler        error_handler,
                           void *                     data,
                           int                        timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "BooleanToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_BooleanToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_BooleanToStr_notify (DBusPendingCall *   pending_call,
                                                 NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestBooleanToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_boolean_to_str_sync (const void *  parent,
                                NihDBusProxy *proxy,
                                int           input,
                                char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "BooleanToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_boolean (NihDBusProxy *             proxy,
                           const char *               input,
                           ProxyTestStrToBooleanReply handler,
                           NihDBusErrorHandler        error_handler,
                           void *                     data,
                           int                        timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToBoolean");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToBoolean_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToBoolean_notify (DBusPendingCall *   pending_call,
                                                 NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int             output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToBooleanReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_boolean_sync (const void *  parent,
                                NihDBusProxy *proxy,
                                const char *  input,
                                int *         output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int             output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToBoolean");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_int16_to_str (NihDBusProxy *           proxy,
                         int16_t                  input,
                         ProxyTestInt16ToStrReply handler,
                         NihDBusErrorHandler      error_handler,
                         void *                   data,
                         int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int16ToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int16_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT16, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_Int16ToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_Int16ToStr_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestInt16ToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_int16_to_str_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              int16_t       input,
                              char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int16ToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int16_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT16, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_int16 (NihDBusProxy *           proxy,
                         const char *             input,
                         ProxyTestStrToInt16Reply handler,
                         NihDBusErrorHandler      error_handler,
                         void *                   data,
                         int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt16");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToInt16_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToInt16_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int16_t         output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a int16_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT16) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToInt16Reply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_int16_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              const char *  input,
                              int16_t *     output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int16_t         output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt16");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a int16_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT16) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_uint16_to_str (NihDBusProxy *            proxy,
                          uint16_t                  input,
                          ProxyTestUint16ToStrReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UInt16ToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint16_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT16, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_UInt16ToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_UInt16ToStr_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestUint16ToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_uint16_to_str_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               uint16_t      input,
                               char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UInt16ToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint16_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT16, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_uint16 (NihDBusProxy *            proxy,
                          const char *              input,
                          ProxyTestStrToUint16Reply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUInt16");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToUInt16_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToUInt16_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	uint16_t        output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a uint16_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT16) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToUint16Reply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_uint16_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               const char *  input,
                               uint16_t *    output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	uint16_t        output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUInt16");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a uint16_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT16) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_int32_to_str (NihDBusProxy *           proxy,
                         int32_t                  input,
                         ProxyTestInt32ToStrReply handler,
                         NihDBusErrorHandler      error_handler,
                         void *                   data,
                         int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int32ToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_Int32ToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_Int32ToStr_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestInt32ToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_int32_to_str_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              int32_t       input,
                              char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int32ToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_int32 (NihDBusProxy *           proxy,
                         const char *             input,
                         ProxyTestStrToInt32Reply handler,
                         NihDBusErrorHandler      error_handler,
                         void *                   data,
                         int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt32");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToInt32_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToInt32_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int32_t         output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a int32_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT32) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToInt32Reply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_int32_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              const char *  input,
                              int32_t *     output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int32_t         output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt32");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a int32_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT32) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_uint32_to_str (NihDBusProxy *            proxy,
                          uint32_t                  input,
                          ProxyTestUint32ToStrReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UInt32ToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT32, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_UInt32ToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_UInt32ToStr_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestUint32ToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_uint32_to_str_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               uint32_t      input,
                               char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UInt32ToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT32, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_uint32 (NihDBusProxy *            proxy,
                          const char *              input,
                          ProxyTestStrToUint32Reply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUInt32");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToUInt32_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToUInt32_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	uint32_t        output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT32) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToUint32Reply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_uint32_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               const char *  input,
                               uint32_t *    output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	uint32_t        output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUInt32");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT32) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_int64_to_str (NihDBusProxy *           proxy,
                         int64_t                  input,
                         ProxyTestInt64ToStrReply handler,
                         NihDBusErrorHandler      error_handler,
                         void *                   data,
                         int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int64ToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int64_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT64, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_Int64ToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_Int64ToStr_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestInt64ToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_int64_to_str_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              int64_t       input,
                              char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int64ToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int64_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT64, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_int64 (NihDBusProxy *           proxy,
                         const char *             input,
                         ProxyTestStrToInt64Reply handler,
                         NihDBusErrorHandler      error_handler,
                         void *                   data,
                         int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt64");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToInt64_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToInt64_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int64_t         output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a int64_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT64) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToInt64Reply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_int64_sync (const void *  parent,
                              NihDBusProxy *proxy,
                              const char *  input,
                              int64_t *     output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int64_t         output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt64");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a int64_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT64) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_uint64_to_str (NihDBusProxy *            proxy,
                          uint64_t                  input,
                          ProxyTestUint64ToStrReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UInt64ToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint64_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT64, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_UInt64ToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_UInt64ToStr_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestUint64ToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_uint64_to_str_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               uint64_t      input,
                               char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UInt64ToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a uint64_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT64, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_uint64 (NihDBusProxy *            proxy,
                          const char *              input,
                          ProxyTestStrToUint64Reply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUInt64");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToUInt64_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToUInt64_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	uint64_t        output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a uint64_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT64) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToUint64Reply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_uint64_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               const char *  input,
                               uint64_t *    output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	uint64_t        output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUInt64");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a uint64_t from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT64) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_double_to_str (NihDBusProxy *            proxy,
                          double                    input,
                          ProxyTestDoubleToStrReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "DoubleToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a double onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_DOUBLE, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_DoubleToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_DoubleToStr_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestDoubleToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_double_to_str_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               double        input,
                               char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "DoubleToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a double onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_DOUBLE, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_double (NihDBusProxy *            proxy,
                          const char *              input,
                          ProxyTestStrToDoubleReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToDouble");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToDouble_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToDouble_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	double          output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a double from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_DOUBLE) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToDoubleReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_double_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               const char *  input,
                               double *      output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	double          output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToDouble");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a double from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_DOUBLE) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_object_path_to_str (NihDBusProxy *                proxy,
                               const char *                  input,
                               ProxyTestObjectPathToStrReply handler,
                               NihDBusErrorHandler           error_handler,
                               void *                        data,
                               int                           timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "ObjectPathToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_ObjectPathToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_ObjectPathToStr_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestObjectPathToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_object_path_to_str_sync (const void *  parent,
                                    NihDBusProxy *proxy,
                                    const char *  input,
                                    char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "ObjectPathToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_object_path (NihDBusProxy *                proxy,
                               const char *                  input,
                               ProxyTestStrToObjectPathReply handler,
                               NihDBusErrorHandler           error_handler,
                               void *                        data,
                               int                           timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToObjectPath");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToObjectPath_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToObjectPath_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToObjectPathReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_object_path_sync (const void *  parent,
                                    NihDBusProxy *proxy,
                                    const char *  input,
                                    char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToObjectPath");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_signature_to_str (NihDBusProxy *               proxy,
                             const char *                 input,
                             ProxyTestSignatureToStrReply handler,
                             NihDBusErrorHandler          error_handler,
                             void *                       data,
                             int                          timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "SignatureToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_SIGNATURE, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_SignatureToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_SignatureToStr_notify (DBusPendingCall *   pending_call,
                                                   NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSignatureToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_signature_to_str_sync (const void *  parent,
                                  NihDBusProxy *proxy,
                                  const char *  input,
                                  char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "SignatureToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_SIGNATURE, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_signature (NihDBusProxy *               proxy,
                             const char *                 input,
                             ProxyTestStrToSignatureReply handler,
                             NihDBusErrorHandler          error_handler,
                             void *                       data,
                             int                          timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToSignature");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToSignature_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToSignature_notify (DBusPendingCall *   pending_call,
                                                   NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_SIGNATURE) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToSignatureReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_signature_sync (const void *  parent,
                                  NihDBusProxy *proxy,
                                  const char *  input,
                                  char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToSignature");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_SIGNATURE) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_struct_to_str (NihDBusProxy *                   proxy,
                          const ProxyTestStructToStrInput *input,
                          ProxyTestStructToStrReply        handler,
                          NihDBusErrorHandler              error_handler,
                          void *                           data,
                          int                              timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     input_iter;
	const char *        input_item0;
	uint32_t            input_item1;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StructToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a structure onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_STRUCT, NULL, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	input_item0 = input->item0;

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_STRING, &input_item0)) {
		dbus_message_iter_abandon_container (&iter, &input_iter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	input_item1 = input->item1;

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_UINT32, &input_item1)) {
		dbus_message_iter_abandon_container (&iter, &input_iter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StructToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StructToStr_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStructToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_struct_to_str_sync (const void *                     parent,
                               NihDBusProxy *                   proxy,
                               const ProxyTestStructToStrInput *input,
                               char **                          output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter input_iter;
	const char *    input_item0;
	uint32_t        input_item1;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StructToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a structure onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_STRUCT, NULL, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	input_item0 = input->item0;

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_STRING, &input_item0)) {
		dbus_message_iter_abandon_container (&iter, &input_iter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	input_item1 = input->item1;

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_UINT32, &input_item1)) {
		dbus_message_iter_abandon_container (&iter, &input_iter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_struct (NihDBusProxy *            proxy,
                          const char *              input,
                          ProxyTestStrToStructReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToStruct");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToStruct_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToStruct_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *               reply;
	DBusMessageIter             iter;
	NihDBusMessage *            message;
	DBusError                   error;
	ProxyTestStrToStructOutput *output;
	DBusMessageIter             output_iter;
	const char *                output_item0_dbus;
	char *                      output_item0;
	uint32_t                    output_item1;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRUCT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &output_iter);

		output = nih_new (message, ProxyTestStrToStructOutput);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_STRING) {
			nih_free (output);
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&output_iter, &output_item0_dbus);

		output_item0 = nih_strdup (output, output_item0_dbus);
		if (! output_item0) {
			nih_free (output);
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&output_iter);

		output->item0 = output_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_UINT32) {
			nih_free (output);
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&output_iter, &output_item1);

		dbus_message_iter_next (&output_iter);

		output->item1 = output_item1;

		if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INVALID) {
			nih_free (output);
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToStructReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_struct_sync (const void *                 parent,
                               NihDBusProxy *               proxy,
                               const char *                 input,
                               ProxyTestStrToStructOutput **output)
{
	DBusMessage *               method_call;
	DBusMessageIter             iter;
	DBusError                   error;
	DBusMessage *               reply;
	ProxyTestStrToStructOutput *output_local;
	DBusMessageIter             output_local_iter;
	const char *                output_local_item0_dbus;
	char *                      output_local_item0;
	uint32_t                    output_local_item1;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToStruct");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRUCT) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &output_local_iter);

		output_local = nih_new (parent, ProxyTestStrToStructOutput);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_STRING) {
			nih_free (output_local);
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&output_local_iter, &output_local_item0_dbus);

		output_local_item0 = nih_strdup (output_local, output_local_item0_dbus);
		if (! output_local_item0) {
			nih_free (output_local);
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&output_local_iter);

		output_local->item0 = output_local_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_UINT32) {
			nih_free (output_local);
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&output_local_iter, &output_local_item1);

		dbus_message_iter_next (&output_local_iter);

		output_local->item1 = output_local_item1;

		if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INVALID) {
			nih_free (output_local);
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_int32_array_to_str (NihDBusProxy *                proxy,
                               const int32_t *               input,
                               size_t                        input_len,
                               ProxyTestInt32ArrayToStrReply handler,
                               NihDBusErrorHandler           error_handler,
                               void *                        data,
                               int                           timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     input_iter;

	nih_assert (proxy != NULL);
	nih_assert ((input_len == 0) || (input != NULL));
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int32ArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "i", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	for (size_t input_i = 0; input_i < input_len; input_i++) {
		int32_t input_element;

		input_element = input[input_i];

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_INT32, &input_element)) {
			dbus_message_iter_abandon_container (&iter, &input_iter);
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_Int32ArrayToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_Int32ArrayToStr_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestInt32ArrayToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_int32_array_to_str_sync (const void *   parent,
                                    NihDBusProxy * proxy,
                                    const int32_t *input,
                                    size_t         input_len,
                                    char **        output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter input_iter;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert ((input_len == 0) || (input != NULL));
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int32ArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "i", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	for (size_t input_i = 0; input_i < input_len; input_i++) {
		int32_t input_element;

		input_element = input[input_i];

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_INT32, &input_element)) {
			dbus_message_iter_abandon_container (&iter, &input_iter);
			dbus_message_unref (method_call);
			nih_return_no_memory_error (-1);
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_int32_array (NihDBusProxy *                proxy,
                               const char *                  input,
                               ProxyTestStrToInt32ArrayReply handler,
                               NihDBusErrorHandler           error_handler,
                               void *                        data,
                               int                           timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt32Array");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToInt32Array_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToInt32Array_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int32_t *       output;
	size_t          output_len;
	DBusMessageIter output_iter;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &output_iter);

		output_len = 0;
		output = NULL;

		while (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INVALID) {
			int32_t *output_tmp;
			int32_t  output_element;

			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INT32) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&output_iter, &output_element);

			dbus_message_iter_next (&output_iter);

			if (output_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			output_tmp = nih_realloc (output, message, sizeof (int32_t) * (output_len + 1));
			if (! output_tmp) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			output = output_tmp;
			output[output_len] = output_element;

			output_len++;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToInt32ArrayReply)pending_data->handler) (pending_data->data, message, output, output_len);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_int32_array_sync (const void *  parent,
                                    NihDBusProxy *proxy,
                                    const char *  input,
                                    int32_t **    output,
                                    size_t *      output_len)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int32_t *       output_local;
	size_t          output_local_len;
	DBusMessageIter output_local_iter;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);
	nih_assert (output_len != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt32Array");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &output_local_iter);

		output_local_len = 0;
		output_local = NULL;

		while (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INVALID) {
			int32_t *output_local_tmp;
			int32_t  output_local_element;

			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INT32) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&output_local_iter, &output_local_element);

			dbus_message_iter_next (&output_local_iter);

			if (output_local_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			output_local_tmp = nih_realloc (output_local, parent, sizeof (int32_t) * (output_local_len + 1));
			if (! output_local_tmp) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			output_local = output_local_tmp;
			output_local[output_local_len] = output_local_element;

			output_local_len++;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
		*output_len = output_local_len;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_array_to_str (NihDBusProxy *              proxy,
                             char * const *              input,
                             ProxyTestStrArrayToStrReply handler,
                             NihDBusErrorHandler         error_handler,
                             void *                      data,
                             int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     input_iter;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			const char *input_element;

			input_element = input[input_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_STRING, &input_element)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrArrayToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrArrayToStr_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrArrayToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_array_to_str_sync (const void *  parent,
                                  NihDBusProxy *proxy,
                                  char * const *input,
                                  char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter input_iter;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			const char *input_element;

			input_element = input[input_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&input_iter, DBUS_TYPE_STRING, &input_element)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_str_array (NihDBusProxy *              proxy,
                             const char *                input,
                             ProxyTestStrToStrArrayReply handler,
                             NihDBusErrorHandler         error_handler,
                             void *                      data,
                             int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToStrArray");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToStrArray_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToStrArray_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char **         output;
	DBusMessageIter output_iter;
	size_t          output_size;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &output_iter);

		output_size = 0;
		output = NULL;

		output = nih_alloc (message, sizeof (char *));
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		output[output_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INVALID) {
			const char *output_element_dbus;
			char **     output_tmp;
			char *      output_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_STRING) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&output_iter, &output_element_dbus);

			output_element = nih_strdup (output, output_element_dbus);
			if (! output_element) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&output_iter);

			if (output_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			output_tmp = nih_realloc (output, message, sizeof (char *) * (output_size + 2));
			if (! output_tmp) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			output = output_tmp;
			output[output_size] = output_element;
			output[output_size + 1] = NULL;

			output_size++;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToStrArrayReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_str_array_sync (const void *  parent,
                                  NihDBusProxy *proxy,
                                  const char *  input,
                                  char ***      output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char **         output_local;
	DBusMessageIter output_local_iter;
	size_t          output_local_size;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToStrArray");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &output_local_iter);

		output_local_size = 0;
		output_local = NULL;

		output_local = nih_alloc (parent, sizeof (char *));
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		output_local[output_local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INVALID) {
			const char *output_local_element_dbus;
			char **     output_local_tmp;
			char *      output_local_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_STRING) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&output_local_iter, &output_local_element_dbus);

			output_local_element = nih_strdup (output_local, output_local_element_dbus);
			if (! output_local_element) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&output_local_iter);

			if (output_local_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			output_local_tmp = nih_realloc (output_local, parent, sizeof (char *) * (output_local_size + 2));
			if (! output_local_tmp) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			output_local = output_local_tmp;
			output_local[output_local_size] = output_local_element;
			output_local[output_local_size + 1] = NULL;

			output_local_size++;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_int32_array_array_to_str (NihDBusProxy *                     proxy,
                                     int32_t * const *                  input,
                                     const size_t *                     input_len,
                                     ProxyTestInt32ArrayArrayToStrReply handler,
                                     NihDBusErrorHandler                error_handler,
                                     void *                             data,
                                     int                                timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     input_iter;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((*input == NULL) || (input_len != NULL));
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int32ArrayArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "ai", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			DBusMessageIter input_element_iter;
			const int32_t * input_element;
			size_t          input_element_len;

			input_element = input[input_i];
			input_element_len = input_len[input_i];

			/* Marshal an array onto the message */
			if (! dbus_message_iter_open_container (&input_iter, DBUS_TYPE_ARRAY, "i", &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			for (size_t input_element_i = 0; input_element_i < input_element_len; input_element_i++) {
				int32_t input_element_element;

				input_element_element = input_element[input_element_i];

				/* Marshal a int32_t onto the message */
				if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_INT32, &input_element_element)) {
					dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
					dbus_message_iter_abandon_container (&iter, &input_iter);
					dbus_message_unref (method_call);
					nih_return_no_memory_error (NULL);
				}
			}

			if (! dbus_message_iter_close_container (&input_iter, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_Int32ArrayArrayToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_Int32ArrayArrayToStr_notify (DBusPendingCall *   pending_call,
                                                         NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestInt32ArrayArrayToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_int32_array_array_to_str_sync (const void *     parent,
                                          NihDBusProxy *   proxy,
                                          int32_t * const *input,
                                          const size_t *   input_len,
                                          char **          output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter input_iter;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((*input == NULL) || (input_len != NULL));
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "Int32ArrayArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "ai", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			DBusMessageIter input_element_iter;
			const int32_t * input_element;
			size_t          input_element_len;

			input_element = input[input_i];
			input_element_len = input_len[input_i];

			/* Marshal an array onto the message */
			if (! dbus_message_iter_open_container (&input_iter, DBUS_TYPE_ARRAY, "i", &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			for (size_t input_element_i = 0; input_element_i < input_element_len; input_element_i++) {
				int32_t input_element_element;

				input_element_element = input_element[input_element_i];

				/* Marshal a int32_t onto the message */
				if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_INT32, &input_element_element)) {
					dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
					dbus_message_iter_abandon_container (&iter, &input_iter);
					dbus_message_unref (method_call);
					nih_return_no_memory_error (-1);
				}
			}

			if (! dbus_message_iter_close_container (&input_iter, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_int32_array_array (NihDBusProxy *                     proxy,
                                     const char *                       input,
                                     ProxyTestStrToInt32ArrayArrayReply handler,
                                     NihDBusErrorHandler                error_handler,
                                     void *                             data,
                                     int                                timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt32ArrayArray");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToInt32ArrayArray_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToInt32ArrayArray_notify (DBusPendingCall *   pending_call,
                                                         NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int32_t **      output;
	size_t *        output_len;
	DBusMessageIter output_iter;
	size_t          output_size;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &output_iter);

		output_size = 0;
		output = NULL;
		output_len = NULL;

		output = nih_alloc (message, sizeof (int32_t *));
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		output[output_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter output_element_iter;
			int32_t **      output_tmp;
			int32_t *       output_element;
			size_t *        output_len_tmp;
			size_t          output_element_len;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_ARRAY) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&output_iter, &output_element_iter);

			output_element_len = 0;
			output_element = NULL;

			while (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_INVALID) {
				int32_t *output_element_tmp;
				int32_t  output_element_element;

				/* Demarshal a int32_t from the message */
				if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_INT32) {
					if (output_element)
						nih_free (output_element);
					if (output)
						nih_free (output);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&output_element_iter, &output_element_element);

				dbus_message_iter_next (&output_element_iter);

				if (output_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
					if (output_element)
						nih_free (output_element);
					if (output)
						nih_free (output);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				output_element_tmp = nih_realloc (output_element, output, sizeof (int32_t) * (output_element_len + 1));
				if (! output_element_tmp) {
					if (output_element)
						nih_free (output_element);
					if (output)
						nih_free (output);
					nih_free (message);
					message = NULL;
					goto enomem;
				}

				output_element = output_element_tmp;
				output_element[output_element_len] = output_element_element;

				output_element_len++;
			}

			dbus_message_iter_next (&output_iter);

			if (output_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			output_tmp = nih_realloc (output, message, sizeof (int32_t *) * (output_size + 2));
			if (! output_tmp) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			output = output_tmp;
			output[output_size] = output_element;
			output[output_size + 1] = NULL;

			if (output_size + 1 > SIZE_MAX / sizeof (size_t)) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			output_len_tmp = nih_realloc (output_len, output, sizeof (size_t) * (output_size + 1));
			if (! output_len_tmp) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			output_len = output_len_tmp;
			output_len[output_size] = output_element_len;

			output_size++;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToInt32ArrayArrayReply)pending_data->handler) (pending_data->data, message, output, output_len);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_int32_array_array_sync (const void *  parent,
                                          NihDBusProxy *proxy,
                                          const char *  input,
                                          int32_t ***   output,
                                          size_t **     output_len)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int32_t **      output_local;
	size_t *        output_local_len;
	DBusMessageIter output_local_iter;
	size_t          output_local_size;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);
	nih_assert (output_len != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToInt32ArrayArray");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &output_local_iter);

		output_local_size = 0;
		output_local = NULL;
		output_local_len = NULL;

		output_local = nih_alloc (parent, sizeof (int32_t *));
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		output_local[output_local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter output_local_element_iter;
			int32_t **      output_local_tmp;
			int32_t *       output_local_element;
			size_t *        output_local_len_tmp;
			size_t          output_local_element_len;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_ARRAY) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&output_local_iter, &output_local_element_iter);

			output_local_element_len = 0;
			output_local_element = NULL;

			while (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_INVALID) {
				int32_t *output_local_element_tmp;
				int32_t  output_local_element_element;

				/* Demarshal a int32_t from the message */
				if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_INT32) {
					if (output_local_element)
						nih_free (output_local_element);
					if (output_local)
						nih_free (output_local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&output_local_element_iter, &output_local_element_element);

				dbus_message_iter_next (&output_local_element_iter);

				if (output_local_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
					if (output_local_element)
						nih_free (output_local_element);
					if (output_local)
						nih_free (output_local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				output_local_element_tmp = nih_realloc (output_local_element, output_local, sizeof (int32_t) * (output_local_element_len + 1));
				if (! output_local_element_tmp) {
					if (output_local_element)
						nih_free (output_local_element);
					if (output_local)
						nih_free (output_local);
					*output = NULL;
					goto enomem;
				}

				output_local_element = output_local_element_tmp;
				output_local_element[output_local_element_len] = output_local_element_element;

				output_local_element_len++;
			}

			dbus_message_iter_next (&output_local_iter);

			if (output_local_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			output_local_tmp = nih_realloc (output_local, parent, sizeof (int32_t *) * (output_local_size + 2));
			if (! output_local_tmp) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			output_local = output_local_tmp;
			output_local[output_local_size] = output_local_element;
			output_local[output_local_size + 1] = NULL;

			if (output_local_size + 1 > SIZE_MAX / sizeof (size_t)) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			output_local_len_tmp = nih_realloc (output_local_len, output_local, sizeof (size_t) * (output_local_size + 1));
			if (! output_local_len_tmp) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			output_local_len = output_local_len_tmp;
			output_local_len[output_local_size] = output_local_element_len;

			output_local_size++;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
		*output_len = output_local_len;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local_len);
		*output_len = NULL;
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_struct_array_to_str (NihDBusProxy *                                 proxy,
                                ProxyTestStructArrayToStrInputElement * const *input,
                                ProxyTestStructArrayToStrReply                 handler,
                                NihDBusErrorHandler                            error_handler,
                                void *                                         data,
                                int                                            timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     input_iter;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StructArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "(su)", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			DBusMessageIter                              input_element_iter;
			const char *                                 input_element_item0;
			uint32_t                                     input_element_item1;
			const ProxyTestStructArrayToStrInputElement *input_element;

			input_element = input[input_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&input_iter, DBUS_TYPE_STRUCT, NULL, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			input_element_item0 = input_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_STRING, &input_element_item0)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			input_element_item1 = input_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_UINT32, &input_element_item1)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			if (! dbus_message_iter_close_container (&input_iter, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StructArrayToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StructArrayToStr_notify (DBusPendingCall *   pending_call,
                                                     NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStructArrayToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_struct_array_to_str_sync (const void *                                   parent,
                                     NihDBusProxy *                                 proxy,
                                     ProxyTestStructArrayToStrInputElement * const *input,
                                     char **                                        output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter input_iter;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StructArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "(su)", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			DBusMessageIter                              input_element_iter;
			const char *                                 input_element_item0;
			uint32_t                                     input_element_item1;
			const ProxyTestStructArrayToStrInputElement *input_element;

			input_element = input[input_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&input_iter, DBUS_TYPE_STRUCT, NULL, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			input_element_item0 = input_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_STRING, &input_element_item0)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			input_element_item1 = input_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_UINT32, &input_element_item1)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			if (! dbus_message_iter_close_container (&input_iter, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_struct_array (NihDBusProxy *                 proxy,
                                const char *                   input,
                                ProxyTestStrToStructArrayReply handler,
                                NihDBusErrorHandler            error_handler,
                                void *                         data,
                                int                            timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToStructArray");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToStructArray_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToStructArray_notify (DBusPendingCall *   pending_call,
                                                     NihDBusPendingData *pending_data)
{
	DBusMessage *                            reply;
	DBusMessageIter                          iter;
	NihDBusMessage *                         message;
	DBusError                                error;
	ProxyTestStrToStructArrayOutputElement **output;
	DBusMessageIter                          output_iter;
	size_t                                   output_size;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &output_iter);

		output_size = 0;
		output = NULL;

		output = nih_alloc (message, sizeof (ProxyTestStrToStructArrayOutputElement *));
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		output[output_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter                          output_element_iter;
			const char *                             output_element_item0_dbus;
			char *                                   output_element_item0;
			uint32_t                                 output_element_item1;
			ProxyTestStrToStructArrayOutputElement **output_tmp;
			ProxyTestStrToStructArrayOutputElement * output_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_STRUCT) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&output_iter, &output_element_iter);

			output_element = nih_new (output, ProxyTestStrToStructArrayOutputElement);
			if (! output_element) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_STRING) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&output_element_iter, &output_element_item0_dbus);

			output_element_item0 = nih_strdup (output_element, output_element_item0_dbus);
			if (! output_element_item0) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&output_element_iter);

			output_element->item0 = output_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&output_element_iter, &output_element_item1);

			dbus_message_iter_next (&output_element_iter);

			output_element->item1 = output_element_item1;

			if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_next (&output_iter);

			if (output_size + 2 > SIZE_MAX / sizeof (ProxyTestStrToStructArrayOutputElement *)) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			output_tmp = nih_realloc (output, message, sizeof (ProxyTestStrToStructArrayOutputElement *) * (output_size + 2));
			if (! output_tmp) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			output = output_tmp;
			output[output_size] = output_element;
			output[output_size + 1] = NULL;

			output_size++;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToStructArrayReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_struct_array_sync (const void *                              parent,
                                     NihDBusProxy *                            proxy,
                                     const char *                              input,
                                     ProxyTestStrToStructArrayOutputElement ***output)
{
	DBusMessage *                            method_call;
	DBusMessageIter                          iter;
	DBusError                                error;
	DBusMessage *                            reply;
	ProxyTestStrToStructArrayOutputElement **output_local;
	DBusMessageIter                          output_local_iter;
	size_t                                   output_local_size;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToStructArray");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &output_local_iter);

		output_local_size = 0;
		output_local = NULL;

		output_local = nih_alloc (parent, sizeof (ProxyTestStrToStructArrayOutputElement *));
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		output_local[output_local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter                          output_local_element_iter;
			const char *                             output_local_element_item0_dbus;
			char *                                   output_local_element_item0;
			uint32_t                                 output_local_element_item1;
			ProxyTestStrToStructArrayOutputElement **output_local_tmp;
			ProxyTestStrToStructArrayOutputElement * output_local_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_STRUCT) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&output_local_iter, &output_local_element_iter);

			output_local_element = nih_new (output_local, ProxyTestStrToStructArrayOutputElement);
			if (! output_local_element) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_STRING) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&output_local_element_iter, &output_local_element_item0_dbus);

			output_local_element_item0 = nih_strdup (output_local_element, output_local_element_item0_dbus);
			if (! output_local_element_item0) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&output_local_element_iter);

			output_local_element->item0 = output_local_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&output_local_element_iter, &output_local_element_item1);

			dbus_message_iter_next (&output_local_element_iter);

			output_local_element->item1 = output_local_element_item1;

			if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_next (&output_local_iter);

			if (output_local_size + 2 > SIZE_MAX / sizeof (ProxyTestStrToStructArrayOutputElement *)) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			output_local_tmp = nih_realloc (output_local, parent, sizeof (ProxyTestStrToStructArrayOutputElement *) * (output_local_size + 2));
			if (! output_local_tmp) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			output_local = output_local_tmp;
			output_local[output_local_size] = output_local_element;
			output_local[output_local_size + 1] = NULL;

			output_local_size++;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_dict_entry_array_to_str (NihDBusProxy *                                    proxy,
                                    ProxyTestDictEntryArrayToStrInputElement * const *input,
                                    ProxyTestDictEntryArrayToStrReply                 handler,
                                    NihDBusErrorHandler                               error_handler,
                                    void *                                            data,
                                    int                                               timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     input_iter;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "DictEntryArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "{su}", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			DBusMessageIter                                 input_element_iter;
			const char *                                    input_element_item0;
			uint32_t                                        input_element_item1;
			const ProxyTestDictEntryArrayToStrInputElement *input_element;

			input_element = input[input_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&input_iter, DBUS_TYPE_DICT_ENTRY, NULL, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			input_element_item0 = input_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_STRING, &input_element_item0)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			input_element_item1 = input_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_UINT32, &input_element_item1)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			if (! dbus_message_iter_close_container (&input_iter, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_DictEntryArrayToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_DictEntryArrayToStr_notify (DBusPendingCall *   pending_call,
                                                        NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestDictEntryArrayToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_dict_entry_array_to_str_sync (const void *                                      parent,
                                         NihDBusProxy *                                    proxy,
                                         ProxyTestDictEntryArrayToStrInputElement * const *input,
                                         char **                                           output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter input_iter;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "DictEntryArrayToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "{su}", &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (input) {
		for (size_t input_i = 0; input[input_i]; input_i++) {
			DBusMessageIter                                 input_element_iter;
			const char *                                    input_element_item0;
			uint32_t                                        input_element_item1;
			const ProxyTestDictEntryArrayToStrInputElement *input_element;

			input_element = input[input_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&input_iter, DBUS_TYPE_DICT_ENTRY, NULL, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			input_element_item0 = input_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_STRING, &input_element_item0)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			input_element_item1 = input_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&input_element_iter, DBUS_TYPE_UINT32, &input_element_item1)) {
				dbus_message_iter_abandon_container (&input_iter, &input_element_iter);
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			if (! dbus_message_iter_close_container (&input_iter, &input_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &input_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &input_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_dict_entry_array (NihDBusProxy *                    proxy,
                                    const char *                      input,
                                    ProxyTestStrToDictEntryArrayReply handler,
                                    NihDBusErrorHandler               error_handler,
                                    void *                            data,
                                    int                               timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToDictEntryArray");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToDictEntryArray_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToDictEntryArray_notify (DBusPendingCall *   pending_call,
                                                        NihDBusPendingData *pending_data)
{
	DBusMessage *                               reply;
	DBusMessageIter                             iter;
	NihDBusMessage *                            message;
	DBusError                                   error;
	ProxyTestStrToDictEntryArrayOutputElement **output;
	DBusMessageIter                             output_iter;
	size_t                                      output_size;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &output_iter);

		output_size = 0;
		output = NULL;

		output = nih_alloc (message, sizeof (ProxyTestStrToDictEntryArrayOutputElement *));
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		output[output_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter                             output_element_iter;
			const char *                                output_element_item0_dbus;
			char *                                      output_element_item0;
			uint32_t                                    output_element_item1;
			ProxyTestStrToDictEntryArrayOutputElement **output_tmp;
			ProxyTestStrToDictEntryArrayOutputElement * output_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&output_iter) != DBUS_TYPE_DICT_ENTRY) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&output_iter, &output_element_iter);

			output_element = nih_new (output, ProxyTestStrToDictEntryArrayOutputElement);
			if (! output_element) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_STRING) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&output_element_iter, &output_element_item0_dbus);

			output_element_item0 = nih_strdup (output_element, output_element_item0_dbus);
			if (! output_element_item0) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&output_element_iter);

			output_element->item0 = output_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&output_element_iter, &output_element_item1);

			dbus_message_iter_next (&output_element_iter);

			output_element->item1 = output_element_item1;

			if (dbus_message_iter_get_arg_type (&output_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (output_element);
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_next (&output_iter);

			if (output_size + 2 > SIZE_MAX / sizeof (ProxyTestStrToDictEntryArrayOutputElement *)) {
				if (output)
					nih_free (output);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			output_tmp = nih_realloc (output, message, sizeof (ProxyTestStrToDictEntryArrayOutputElement *) * (output_size + 2));
			if (! output_tmp) {
				if (output)
					nih_free (output);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			output = output_tmp;
			output[output_size] = output_element;
			output[output_size + 1] = NULL;

			output_size++;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToDictEntryArrayReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_dict_entry_array_sync (const void *                                 parent,
                                         NihDBusProxy *                               proxy,
                                         const char *                                 input,
                                         ProxyTestStrToDictEntryArrayOutputElement ***output)
{
	DBusMessage *                               method_call;
	DBusMessageIter                             iter;
	DBusError                                   error;
	DBusMessage *                               reply;
	ProxyTestStrToDictEntryArrayOutputElement **output_local;
	DBusMessageIter                             output_local_iter;
	size_t                                      output_local_size;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToDictEntryArray");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &output_local_iter);

		output_local_size = 0;
		output_local = NULL;

		output_local = nih_alloc (parent, sizeof (ProxyTestStrToDictEntryArrayOutputElement *));
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		output_local[output_local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter                             output_local_element_iter;
			const char *                                output_local_element_item0_dbus;
			char *                                      output_local_element_item0;
			uint32_t                                    output_local_element_item1;
			ProxyTestStrToDictEntryArrayOutputElement **output_local_tmp;
			ProxyTestStrToDictEntryArrayOutputElement * output_local_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&output_local_iter) != DBUS_TYPE_DICT_ENTRY) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&output_local_iter, &output_local_element_iter);

			output_local_element = nih_new (output_local, ProxyTestStrToDictEntryArrayOutputElement);
			if (! output_local_element) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_STRING) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&output_local_element_iter, &output_local_element_item0_dbus);

			output_local_element_item0 = nih_strdup (output_local_element, output_local_element_item0_dbus);
			if (! output_local_element_item0) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&output_local_element_iter);

			output_local_element->item0 = output_local_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&output_local_element_iter, &output_local_element_item1);

			dbus_message_iter_next (&output_local_element_iter);

			output_local_element->item1 = output_local_element_item1;

			if (dbus_message_iter_get_arg_type (&output_local_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (output_local_element);
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_next (&output_local_iter);

			if (output_local_size + 2 > SIZE_MAX / sizeof (ProxyTestStrToDictEntryArrayOutputElement *)) {
				if (output_local)
					nih_free (output_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			output_local_tmp = nih_realloc (output_local, parent, sizeof (ProxyTestStrToDictEntryArrayOutputElement *) * (output_local_size + 2));
			if (! output_local_tmp) {
				if (output_local)
					nih_free (output_local);
				*output = NULL;
				goto enomem;
			}

			output_local = output_local_tmp;
			output_local[output_local_size] = output_local_element;
			output_local[output_local_size + 1] = NULL;

			output_local_size++;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_unix_fd_to_str (NihDBusProxy *            proxy,
                           int                       input,
                           ProxyTestUnixFdToStrReply handler,
                           NihDBusErrorHandler       error_handler,
                           void *                    data,
                           int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UnixFdToStr");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UNIX_FD, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_UnixFdToStr_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_UnixFdToStr_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          output;
	const char *    output_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output_dbus);

		output = nih_strdup (message, output_dbus);
		if (! output) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestUnixFdToStrReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_unix_fd_to_str_sync (const void *  parent,
                                NihDBusProxy *proxy,
                                int           input,
                                char **       output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          output_local;
	const char *    output_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "UnixFdToStr");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UNIX_FD, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local_dbus);

		output_local = nih_strdup (parent, output_local_dbus);
		if (! output_local) {
			*output = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (output_local);
		*output = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_str_to_unix_fd (NihDBusProxy *            proxy,
                           const char *              input,
                           ProxyTestStrToUnixFdReply handler,
                           NihDBusErrorHandler       error_handler,
                           void *                    data,
                           int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUnixFd");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_StrToUnixFd_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_StrToUnixFd_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	int             output;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UNIX_FD) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &output);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestStrToUnixFdReply)pending_data->handler) (pending_data->data, message, output);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_str_to_unix_fd_sync (const void *  parent,
                                NihDBusProxy *proxy,
                                const char *  input,
                                int *         output)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	int             output_local;

	nih_assert (proxy != NULL);
	nih_assert (input != NULL);
	nih_assert (output != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.netsplit.Nih.Test", "StrToUnixFd");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &input)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UNIX_FD) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &output_local);

		dbus_message_iter_next (&iter);

		*output = output_local;
	enomem: __attribute__ ((unused));
	} while (! *output);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewByte_signal (DBusConnection *    connection,
                                            DBusMessage *       signal,
                                            NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	uint8_t         value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint8_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BYTE) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewByteHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewBoolean_signal (DBusConnection *    connection,
                                               DBusMessage *       signal,
                                               NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int             value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewBooleanHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewInt16_signal (DBusConnection *    connection,
                                             DBusMessage *       signal,
                                             NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int16_t         value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int16_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT16) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewInt16Handler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewUInt16_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	uint16_t        value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint16_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT16) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewUint16Handler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewInt32_signal (DBusConnection *    connection,
                                             DBusMessage *       signal,
                                             NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int32_t         value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int32_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT32) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewInt32Handler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewUInt32_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	uint32_t        value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint32_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT32) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewUint32Handler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewInt64_signal (DBusConnection *    connection,
                                             DBusMessage *       signal,
                                             NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int64_t         value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int64_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT64) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewInt64Handler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewUInt64_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	uint64_t        value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint64_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT64) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewUint64Handler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewDouble_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	double          value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a double from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_DOUBLE) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewDoubleHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewString_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	char *          value;
	const char *    value_dbus;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewStringHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewObjectPath_signal (DBusConnection *    connection,
                                                  DBusMessage *       signal,
                                                  NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	char *          value;
	const char *    value_dbus;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewObjectPathHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewSignature_signal (DBusConnection *    connection,
                                                 DBusMessage *       signal,
                                                 NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	char *          value;
	const char *    value_dbus;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_SIGNATURE) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewSignatureHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewStruct_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter          iter;
	NihDBusMessage *         message;
	ProxyTestNewStructValue *value;
	DBusMessageIter          value_iter;
	const char *             value_item0_dbus;
	char *                   value_item0;
	uint32_t                 value_item1;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a structure from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRUCT) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &value_iter);

	value = nih_new (message, ProxyTestNewStructValue);
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRING) {
		nih_free (value);
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&value_iter, &value_item0_dbus);

	value_item0 = nih_strdup (value, value_item0_dbus);
	if (! value_item0) {
		nih_free (value);
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&value_iter);

	value->item0 = value_item0;

	/* Demarshal a uint32_t from the message */
	if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_UINT32) {
		nih_free (value);
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&value_iter, &value_item1);

	dbus_message_iter_next (&value_iter);

	value->item1 = value_item1;

	if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		nih_free (value);
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewStructHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewInt32Array_signal (DBusConnection *    connection,
                                                  DBusMessage *       signal,
                                                  NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int32_t *       value;
	size_t          value_len;
	DBusMessageIter value_iter;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &value_iter);

	value_len = 0;
	value = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		int32_t *value_tmp;
		int32_t  value_element;

		/* Demarshal a int32_t from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INT32) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_get_basic (&value_iter, &value_element);

		dbus_message_iter_next (&value_iter);

		if (value_len + 1 > SIZE_MAX / sizeof (int32_t)) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		value_tmp = nih_realloc (value, message, sizeof (int32_t) * (value_len + 1));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		value = value_tmp;
		value[value_len] = value_element;

		value_len++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewInt32ArrayHandler)proxied->handler) (proxied->data, message, value, value_len);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewStrArray_signal (DBusConnection *    connection,
                                                DBusMessage *       signal,
                                                NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	char **         value;
	DBusMessageIter value_iter;
	size_t          value_size;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &value_iter);

	value_size = 0;
	value = NULL;

	value = nih_alloc (message, sizeof (char *));
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	value[value_size] = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		const char *value_element_dbus;
		char **     value_tmp;
		char *      value_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRING) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_get_basic (&value_iter, &value_element_dbus);

		value_element = nih_strdup (value, value_element_dbus);
		if (! value_element) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		value_tmp = nih_realloc (value, message, sizeof (char *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		value_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewStrArrayHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewInt32ArrayArray_signal (DBusConnection *    connection,
                                                       DBusMessage *       signal,
                                                       NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int32_t **      value;
	size_t *        value_len;
	DBusMessageIter value_iter;
	size_t          value_size;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &value_iter);

	value_size = 0;
	value = NULL;
	value_len = NULL;

	value = nih_alloc (message, sizeof (int32_t *));
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	value[value_size] = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter value_element_iter;
		int32_t **      value_tmp;
		int32_t *       value_element;
		size_t *        value_len_tmp;
		size_t          value_element_len;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_ARRAY) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_recurse (&value_iter, &value_element_iter);

		value_element_len = 0;
		value_element = NULL;

		while (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
			int32_t *value_element_tmp;
			int32_t  value_element_element;

			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INT32) {
				if (value_element)
					nih_free (value_element);
				if (value)
					nih_free (value);
				nih_free (message);
				return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
			}

			dbus_message_iter_get_basic (&value_element_iter, &value_element_element);

			dbus_message_iter_next (&value_element_iter);

			if (value_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (value_element)
					nih_free (value_element);
				if (value)
					nih_free (value);
				nih_free (message);
				return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
			}

			value_element_tmp = nih_realloc (value_element, value, sizeof (int32_t) * (value_element_len + 1));
			if (! value_element_tmp) {
				if (value_element)
					nih_free (value_element);
				if (value)
					nih_free (value);
				nih_free (message);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			value_element = value_element_tmp;
			value_element[value_element_len] = value_element_element;

			value_element_len++;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		value_tmp = nih_realloc (value, message, sizeof (int32_t *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		if (value_size + 1 > SIZE_MAX / sizeof (size_t)) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		value_len_tmp = nih_realloc (value_len, value, sizeof (size_t) * (value_size + 1));
		if (! value_len_tmp) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		value_len = value_len_tmp;
		value_len[value_size] = value_element_len;

		value_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewInt32ArrayArrayHandler)proxied->handler) (proxied->data, message, value, value_len);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewStructArray_signal (DBusConnection *    connection,
                                                   DBusMessage *       signal,
                                                   NihDBusProxySignal *proxied)
{
	DBusMessageIter                       iter;
	NihDBusMessage *                      message;
	ProxyTestNewStructArrayValueElement **value;
	DBusMessageIter                       value_iter;
	size_t                                value_size;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &value_iter);

	value_size = 0;
	value = NULL;

	value = nih_alloc (message, sizeof (ProxyTestNewStructArrayValueElement *));
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	value[value_size] = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter                       value_element_iter;
		const char *                          value_element_item0_dbus;
		char *                                value_element_item0;
		uint32_t                              value_element_item1;
		ProxyTestNewStructArrayValueElement **value_tmp;
		ProxyTestNewStructArrayValueElement * value_element;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRUCT) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_recurse (&value_iter, &value_element_iter);

		value_element = nih_new (value, ProxyTestNewStructArrayValueElement);
		if (! value_element) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item0_dbus);

		value_element_item0 = nih_strdup (value_element, value_element_item0_dbus);
		if (! value_element_item0) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&value_element_iter);

		value_element->item0 = value_element_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_UINT32) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item1);

		dbus_message_iter_next (&value_element_iter);

		value_element->item1 = value_element_item1;

		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (ProxyTestNewStructArrayValueElement *)) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		value_tmp = nih_realloc (value, message, sizeof (ProxyTestNewStructArrayValueElement *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		value_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewStructArrayHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewDictEntryArray_signal (DBusConnection *    connection,
                                                      DBusMessage *       signal,
                                                      NihDBusProxySignal *proxied)
{
	DBusMessageIter                          iter;
	NihDBusMessage *                         message;
	ProxyTestNewDictEntryArrayValueElement **value;
	DBusMessageIter                          value_iter;
	size_t                                   value_size;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &value_iter);

	value_size = 0;
	value = NULL;

	value = nih_alloc (message, sizeof (ProxyTestNewDictEntryArrayValueElement *));
	if (! value) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	value[value_size] = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter                          value_element_iter;
		const char *                             value_element_item0_dbus;
		char *                                   value_element_item0;
		uint32_t                                 value_element_item1;
		ProxyTestNewDictEntryArrayValueElement **value_tmp;
		ProxyTestNewDictEntryArrayValueElement * value_element;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_DICT_ENTRY) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_recurse (&value_iter, &value_element_iter);

		value_element = nih_new (value, ProxyTestNewDictEntryArrayValueElement);
		if (! value_element) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item0_dbus);

		value_element_item0 = nih_strdup (value_element, value_element_item0_dbus);
		if (! value_element_item0) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&value_element_iter);

		value_element->item0 = value_element_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_UINT32) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item1);

		dbus_message_iter_next (&value_element_iter);

		value_element->item1 = value_element_item1;

		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (ProxyTestNewDictEntryArrayValueElement *)) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		}

		value_tmp = nih_realloc (value, message, sizeof (ProxyTestNewDictEntryArrayValueElement *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_free (message);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		value_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewDictEntryArrayHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
proxy_com_netsplit_Nih_Test_NewUnixFd_signal (DBusConnection *    connection,
                                              DBusMessage *       signal,
                                              NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	int             value;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UNIX_FD) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &value);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestNewUnixFdHandler)proxied->handler) (proxied->data, message, value);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


DBusPendingCall *
proxy_test_get_byte (NihDBusProxy *        proxy,
                     ProxyTestGetByteReply handler,
                     NihDBusErrorHandler   error_handler,
                     void *                data,
                     int                   timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "byte";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_byte_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_byte_get_notify (DBusPendingCall *   pending_call,
                                             NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	uint8_t         value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a uint8_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BYTE) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetByteReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_byte_sync (const void *  parent,
                          NihDBusProxy *proxy,
                          uint8_t *     value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	uint8_t         local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "byte";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a uint8_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BYTE) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_byte (NihDBusProxy *        proxy,
                     uint8_t               value,
                     ProxyTestSetByteReply handler,
                     NihDBusErrorHandler   error_handler,
                     void *                data,
                     int                   timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "byte";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "y", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a uint8_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_BYTE, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_byte_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_byte_set_notify (DBusPendingCall *   pending_call,
                                             NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetByteReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_byte_sync (const void *  parent,
                          NihDBusProxy *proxy,
                          uint8_t       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "byte";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "y", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a uint8_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_BYTE, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_boolean (NihDBusProxy *           proxy,
                        ProxyTestGetBooleanReply handler,
                        NihDBusErrorHandler      error_handler,
                        void *                   data,
                        int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "boolean";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_boolean_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_boolean_get_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	int             value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BOOLEAN) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetBooleanReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_boolean_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             int *         value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	int             local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "boolean";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BOOLEAN) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_boolean (NihDBusProxy *           proxy,
                        int                      value,
                        ProxyTestSetBooleanReply handler,
                        NihDBusErrorHandler      error_handler,
                        void *                   data,
                        int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "boolean";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "b", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_BOOLEAN, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_boolean_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_boolean_set_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetBooleanReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_boolean_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             int           value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "boolean";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "b", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_BOOLEAN, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_int16 (NihDBusProxy *         proxy,
                      ProxyTestGetInt16Reply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int16_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int16_get_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	int16_t         value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a int16_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT16) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetInt16Reply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_int16_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           int16_t *     value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	int16_t         local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a int16_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT16) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_int16 (NihDBusProxy *         proxy,
                      int16_t                value,
                      ProxyTestSetInt16Reply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "n", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int16_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT16, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int16_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int16_set_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetInt16Reply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_int16_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           int16_t       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "n", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int16_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT16, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_uint16 (NihDBusProxy *          proxy,
                       ProxyTestGetUint16Reply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "uint16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_uint16_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_uint16_get_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	uint16_t        value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a uint16_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT16) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetUint16Reply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_uint16_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            uint16_t *    value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	uint16_t        local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "uint16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a uint16_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT16) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_uint16 (NihDBusProxy *          proxy,
                       uint16_t                value,
                       ProxyTestSetUint16Reply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "uint16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "q", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a uint16_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT16, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_uint16_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_uint16_set_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetUint16Reply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_uint16_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            uint16_t      value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "uint16";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "q", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a uint16_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT16, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_int32 (NihDBusProxy *         proxy,
                      ProxyTestGetInt32Reply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int32_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int32_get_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	int32_t         value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a int32_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT32) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetInt32Reply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_int32_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           int32_t *     value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	int32_t         local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a int32_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT32) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_int32 (NihDBusProxy *         proxy,
                      int32_t                value,
                      ProxyTestSetInt32Reply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "i", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT32, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int32_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int32_set_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetInt32Reply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_int32_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           int32_t       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "i", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT32, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_uint32 (NihDBusProxy *          proxy,
                       ProxyTestGetUint32Reply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "uint32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_uint32_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_uint32_get_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	uint32_t        value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT32) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetUint32Reply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_uint32_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            uint32_t *    value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	uint32_t        local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "uint32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT32) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_uint32 (NihDBusProxy *          proxy,
                       uint32_t                value,
                       ProxyTestSetUint32Reply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "uint32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "u", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT32, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_uint32_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_uint32_set_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetUint32Reply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_uint32_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            uint32_t      value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "uint32";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "u", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT32, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_int64 (NihDBusProxy *         proxy,
                      ProxyTestGetInt64Reply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int64_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int64_get_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	int64_t         value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a int64_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT64) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetInt64Reply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_int64_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           int64_t *     value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	int64_t         local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a int64_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT64) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_int64 (NihDBusProxy *         proxy,
                      int64_t                value,
                      ProxyTestSetInt64Reply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "x", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int64_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT64, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int64_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int64_set_notify (DBusPendingCall *   pending_call,
                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetInt64Reply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_int64_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           int64_t       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "x", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int64_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT64, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_uint64 (NihDBusProxy *          proxy,
                       ProxyTestGetUint64Reply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "uint64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_uint64_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_uint64_get_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	uint64_t        value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a uint64_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT64) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetUint64Reply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_uint64_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            uint64_t *    value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	uint64_t        local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "uint64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a uint64_t from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT64) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_uint64 (NihDBusProxy *          proxy,
                       uint64_t                value,
                       ProxyTestSetUint64Reply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "uint64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "t", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a uint64_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT64, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_uint64_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_uint64_set_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetUint64Reply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_uint64_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            uint64_t      value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "uint64";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "t", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a uint64_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT64, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_dubble (NihDBusProxy *          proxy,
                       ProxyTestGetDubbleReply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "double";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_double_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_double_get_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	double          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a double from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_DOUBLE) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetDubbleReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_dubble_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            double *      value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	double          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "double";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a double from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_DOUBLE) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_dubble (NihDBusProxy *          proxy,
                       double                  value,
                       ProxyTestSetDubbleReply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "double";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "d", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a double onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_DOUBLE, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_double_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_double_set_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetDubbleReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_dubble_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            double        value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "double";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "d", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a double onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_DOUBLE, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_string (NihDBusProxy *          proxy,
                       ProxyTestGetStringReply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "string";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_string_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_string_get_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetStringReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_string_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "string";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_string (NihDBusProxy *          proxy,
                       const char *            value,
                       ProxyTestSetStringReply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "string";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "s", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_STRING, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_string_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_string_set_notify (DBusPendingCall *   pending_call,
                                               NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetStringReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_string_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            const char *  value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "string";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "s", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_STRING, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_object_path (NihDBusProxy *              proxy,
                            ProxyTestGetObjectPathReply handler,
                            NihDBusErrorHandler         error_handler,
                            void *                      data,
                            int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "object_path";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_object_path_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_object_path_get_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_OBJECT_PATH) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetObjectPathReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_object_path_sync (const void *  parent,
                                 NihDBusProxy *proxy,
                                 char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "object_path";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_OBJECT_PATH) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_object_path (NihDBusProxy *              proxy,
                            const char *                value,
                            ProxyTestSetObjectPathReply handler,
                            NihDBusErrorHandler         error_handler,
                            void *                      data,
                            int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "object_path";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "o", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_OBJECT_PATH, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_object_path_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_object_path_set_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetObjectPathReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_object_path_sync (const void *  parent,
                                 NihDBusProxy *proxy,
                                 const char *  value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "object_path";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "o", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_OBJECT_PATH, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_signature (NihDBusProxy *             proxy,
                          ProxyTestGetSignatureReply handler,
                          NihDBusErrorHandler        error_handler,
                          void *                     data,
                          int                        timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "signature";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_signature_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_signature_get_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_SIGNATURE) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetSignatureReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_signature_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "signature";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_SIGNATURE) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_signature (NihDBusProxy *             proxy,
                          const char *               value,
                          ProxyTestSetSignatureReply handler,
                          NihDBusErrorHandler        error_handler,
                          void *                     data,
                          int                        timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "signature";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "g", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_SIGNATURE, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_signature_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_signature_set_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetSignatureReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_signature_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               const char *  value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "signature";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "g", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_SIGNATURE, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_structure (NihDBusProxy *             proxy,
                          ProxyTestGetStructureReply handler,
                          NihDBusErrorHandler        error_handler,
                          void *                     data,
                          int                        timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "structure";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_structure_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_structure_get_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *       reply;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	NihDBusMessage *    message;
	DBusError           error;
	DBusMessageIter     value_iter;
	const char *        value_item0_dbus;
	char *              value_item0;
	uint32_t            value_item1;
	ProxyTestStructure *value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRUCT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value = nih_new (message, ProxyTestStructure);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRING) {
			nih_free (value);
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&value_iter, &value_item0_dbus);

		value_item0 = nih_strdup (value, value_item0_dbus);
		if (! value_item0) {
			nih_free (value);
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&value_iter);

		value->item0 = value_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_UINT32) {
			nih_free (value);
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&value_iter, &value_item1);

		dbus_message_iter_next (&value_iter);

		value->item1 = value_item1;

		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			nih_free (value);
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetStructureReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_structure_sync (const void *         parent,
                               NihDBusProxy *       proxy,
                               ProxyTestStructure **value)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusError           error;
	DBusMessage *       reply;
	const char *        interface;
	const char *        property;
	DBusMessageIter     local_iter;
	const char *        local_item0_dbus;
	char *              local_item0;
	uint32_t            local_item1;
	ProxyTestStructure *local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "structure";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRUCT) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local = nih_new (parent, ProxyTestStructure);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_STRING) {
			nih_free (local);
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&local_iter, &local_item0_dbus);

		local_item0 = nih_strdup (local, local_item0_dbus);
		if (! local_item0) {
			nih_free (local);
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&local_iter);

		local->item0 = local_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_UINT32) {
			nih_free (local);
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&local_iter, &local_item1);

		dbus_message_iter_next (&local_iter);

		local->item1 = local_item1;

		if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			nih_free (local);
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_structure (NihDBusProxy *             proxy,
                          const ProxyTestStructure * value,
                          ProxyTestSetStructureReply handler,
                          NihDBusErrorHandler        error_handler,
                          void *                     data,
                          int                        timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;
	DBusMessageIter     value_iter;
	const char *        value_item0;
	uint32_t            value_item1;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "structure";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "(su)", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a structure onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_STRUCT, NULL, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	value_item0 = value->item0;

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_item0)) {
		dbus_message_iter_abandon_container (&variter, &value_iter);
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	value_item1 = value->item1;

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_UINT32, &value_item1)) {
		dbus_message_iter_abandon_container (&variter, &value_iter);
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_structure_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_structure_set_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetStructureReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_structure_sync (const void *              parent,
                               NihDBusProxy *            proxy,
                               const ProxyTestStructure *value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter value_iter;
	const char *    value_item0;
	uint32_t        value_item1;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "structure";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "(su)", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a structure onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_STRUCT, NULL, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	value_item0 = value->item0;

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_item0)) {
		dbus_message_iter_abandon_container (&variter, &value_iter);
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	value_item1 = value->item1;

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_UINT32, &value_item1)) {
		dbus_message_iter_abandon_container (&variter, &value_iter);
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_int32_array (NihDBusProxy *              proxy,
                            ProxyTestGetInt32ArrayReply handler,
                            NihDBusErrorHandler         error_handler,
                            void *                      data,
                            int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int32_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int32_array_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int32_array_get_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	DBusMessageIter value_iter;
	int32_t *       value;
	size_t          value_len;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_len = 0;
		value = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			int32_t *value_tmp;
			int32_t  value_element;

			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INT32) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_iter, &value_element);

			dbus_message_iter_next (&value_iter);

			if (value_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (int32_t) * (value_len + 1));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_len] = value_element;

			value_len++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetInt32ArrayReply)pending_data->handler) (pending_data->data, message, value, value_len);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_int32_array_sync (const void *  parent,
                                 NihDBusProxy *proxy,
                                 int32_t **    value,
                                 size_t *      value_len)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter local_iter;
	int32_t *       local;
	size_t          local_len;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert (value_len != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int32_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_len = 0;
		local = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			int32_t *local_tmp;
			int32_t  local_element;

			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INT32) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_iter, &local_element);

			dbus_message_iter_next (&local_iter);

			if (local_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (int32_t) * (local_len + 1));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_len] = local_element;

			local_len++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
		*value_len = local_len;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_int32_array (NihDBusProxy *              proxy,
                            const int32_t *             value,
                            size_t                      value_len,
                            ProxyTestSetInt32ArrayReply handler,
                            NihDBusErrorHandler         error_handler,
                            void *                      data,
                            int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;
	DBusMessageIter     value_iter;

	nih_assert (proxy != NULL);
	nih_assert ((value_len == 0) || (value != NULL));
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int32_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "ai", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "i", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	for (size_t value_i = 0; value_i < value_len; value_i++) {
		int32_t value_element;

		value_element = value[value_i];

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_INT32, &value_element)) {
			dbus_message_iter_abandon_container (&variter, &value_iter);
			dbus_message_iter_abandon_container (&iter, &variter);
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int32_array_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int32_array_set_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetInt32ArrayReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_int32_array_sync (const void *   parent,
                                 NihDBusProxy * proxy,
                                 const int32_t *value,
                                 size_t         value_len)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter value_iter;

	nih_assert (proxy != NULL);
	nih_assert ((value_len == 0) || (value != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int32_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "ai", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "i", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	for (size_t value_i = 0; value_i < value_len; value_i++) {
		int32_t value_element;

		value_element = value[value_i];

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_INT32, &value_element)) {
			dbus_message_iter_abandon_container (&variter, &value_iter);
			dbus_message_iter_abandon_container (&iter, &variter);
			dbus_message_unref (method_call);
			nih_return_no_memory_error (-1);
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_str_array (NihDBusProxy *            proxy,
                          ProxyTestGetStrArrayReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "str_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_str_array_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_str_array_get_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	DBusMessageIter value_iter;
	size_t          value_size;
	char **         value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;

		value = nih_alloc (message, sizeof (char *));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			const char *value_element_dbus;
			char **     value_tmp;
			char *      value_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRING) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_iter, &value_element_dbus);

			value_element = nih_strdup (value, value_element_dbus);
			if (! value_element) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (char *) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetStrArrayReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_str_array_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               char ***      value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter local_iter;
	size_t          local_size;
	char **         local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "str_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;

		local = nih_alloc (parent, sizeof (char *));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			const char *local_element_dbus;
			char **     local_tmp;
			char *      local_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_STRING) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_iter, &local_element_dbus);

			local_element = nih_strdup (local, local_element_dbus);
			if (! local_element) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (char *) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_str_array (NihDBusProxy *            proxy,
                          char * const *            value,
                          ProxyTestSetStrArrayReply handler,
                          NihDBusErrorHandler       error_handler,
                          void *                    data,
                          int                       timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;
	DBusMessageIter     value_iter;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "str_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "as", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "s", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			const char *value_element;

			value_element = value[value_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_element)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_str_array_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_str_array_set_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetStrArrayReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_str_array_sync (const void *  parent,
                               NihDBusProxy *proxy,
                               char * const *value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter value_iter;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "str_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "as", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "s", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			const char *value_element;

			value_element = value[value_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_element)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_int32_array_array (NihDBusProxy *                   proxy,
                                  ProxyTestGetInt32ArrayArrayReply handler,
                                  NihDBusErrorHandler              error_handler,
                                  void *                           data,
                                  int                              timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int32_array_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int32_array_array_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int32_array_array_get_notify (DBusPendingCall *   pending_call,
                                                          NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	DBusMessageIter value_iter;
	size_t          value_size;
	int32_t **      value;
	size_t *        value_len;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;
		value_len = NULL;

		value = nih_alloc (message, sizeof (int32_t *));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter value_element_iter;
			int32_t **      value_tmp;
			int32_t *       value_element;
			size_t *        value_len_tmp;
			size_t          value_element_len;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_ARRAY) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&value_iter, &value_element_iter);

			value_element_len = 0;
			value_element = NULL;

			while (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
				int32_t *value_element_tmp;
				int32_t  value_element_element;

				/* Demarshal a int32_t from the message */
				if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INT32) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&value_element_iter, &value_element_element);

				dbus_message_iter_next (&value_element_iter);

				if (value_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				value_element_tmp = nih_realloc (value_element, value, sizeof (int32_t) * (value_element_len + 1));
				if (! value_element_tmp) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_free (message);
					message = NULL;
					goto enomem;
				}

				value_element = value_element_tmp;
				value_element[value_element_len] = value_element_element;

				value_element_len++;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (int32_t *) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			if (value_size + 1 > SIZE_MAX / sizeof (size_t)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_len_tmp = nih_realloc (value_len, value, sizeof (size_t) * (value_size + 1));
			if (! value_len_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value_len = value_len_tmp;
			value_len[value_size] = value_element_len;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetInt32ArrayArrayReply)pending_data->handler) (pending_data->data, message, value, value_len);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_int32_array_array_sync (const void *  parent,
                                       NihDBusProxy *proxy,
                                       int32_t ***   value,
                                       size_t **     value_len)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter local_iter;
	size_t          local_size;
	int32_t **      local;
	size_t *        local_len;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert (value_len != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int32_array_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;
		local_len = NULL;

		local = nih_alloc (parent, sizeof (int32_t *));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter local_element_iter;
			int32_t **      local_tmp;
			int32_t *       local_element;
			size_t *        local_len_tmp;
			size_t          local_element_len;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_ARRAY) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&local_iter, &local_element_iter);

			local_element_len = 0;
			local_element = NULL;

			while (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_INVALID) {
				int32_t *local_element_tmp;
				int32_t  local_element_element;

				/* Demarshal a int32_t from the message */
				if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_INT32) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&local_element_iter, &local_element_element);

				dbus_message_iter_next (&local_element_iter);

				if (local_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				local_element_tmp = nih_realloc (local_element, local, sizeof (int32_t) * (local_element_len + 1));
				if (! local_element_tmp) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					*value = NULL;
					goto enomem;
				}

				local_element = local_element_tmp;
				local_element[local_element_len] = local_element_element;

				local_element_len++;
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (int32_t *) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			if (local_size + 1 > SIZE_MAX / sizeof (size_t)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_len_tmp = nih_realloc (local_len, local, sizeof (size_t) * (local_size + 1));
			if (! local_len_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local_len = local_len_tmp;
			local_len[local_size] = local_element_len;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
		*value_len = local_len;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_int32_array_array (NihDBusProxy *                   proxy,
                                  int32_t * const *                value,
                                  const size_t *                   value_len,
                                  ProxyTestSetInt32ArrayArrayReply handler,
                                  NihDBusErrorHandler              error_handler,
                                  void *                           data,
                                  int                              timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;
	DBusMessageIter     value_iter;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((*value == NULL) || (value_len != NULL));
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "int32_array_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "aai", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "ai", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter value_element_iter;
			const int32_t * value_element;
			size_t          value_element_len;

			value_element = value[value_i];
			value_element_len = value_len[value_i];

			/* Marshal an array onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_ARRAY, "i", &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			for (size_t value_element_i = 0; value_element_i < value_element_len; value_element_i++) {
				int32_t value_element_element;

				value_element_element = value_element[value_element_i];

				/* Marshal a int32_t onto the message */
				if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_INT32, &value_element_element)) {
					dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
					dbus_message_iter_abandon_container (&variter, &value_iter);
					dbus_message_iter_abandon_container (&iter, &variter);
					dbus_message_unref (method_call);
					nih_return_no_memory_error (NULL);
				}
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_int32_array_array_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_int32_array_array_set_notify (DBusPendingCall *   pending_call,
                                                          NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetInt32ArrayArrayReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_int32_array_array_sync (const void *     parent,
                                       NihDBusProxy *   proxy,
                                       int32_t * const *value,
                                       const size_t *   value_len)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter value_iter;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((*value == NULL) || (value_len != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "int32_array_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "aai", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "ai", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter value_element_iter;
			const int32_t * value_element;
			size_t          value_element_len;

			value_element = value[value_i];
			value_element_len = value_len[value_i];

			/* Marshal an array onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_ARRAY, "i", &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			for (size_t value_element_i = 0; value_element_i < value_element_len; value_element_i++) {
				int32_t value_element_element;

				value_element_element = value_element[value_element_i];

				/* Marshal a int32_t onto the message */
				if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_INT32, &value_element_element)) {
					dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
					dbus_message_iter_abandon_container (&variter, &value_iter);
					dbus_message_iter_abandon_container (&iter, &variter);
					dbus_message_unref (method_call);
					nih_return_no_memory_error (-1);
				}
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_struct_array (NihDBusProxy *               proxy,
                             ProxyTestGetStructArrayReply handler,
                             NihDBusErrorHandler          error_handler,
                             void *                       data,
                             int                          timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "struct_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_struct_array_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_struct_array_get_notify (DBusPendingCall *   pending_call,
                                                     NihDBusPendingData *pending_data)
{
	DBusMessage *                 reply;
	DBusMessageIter               iter;
	DBusMessageIter               variter;
	NihDBusMessage *              message;
	DBusError                     error;
	DBusMessageIter               value_iter;
	size_t                        value_size;
	ProxyTestStructArrayElement **value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;

		value = nih_alloc (message, sizeof (ProxyTestStructArrayElement *));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter               value_element_iter;
			const char *                  value_element_item0_dbus;
			char *                        value_element_item0;
			uint32_t                      value_element_item1;
			ProxyTestStructArrayElement **value_tmp;
			ProxyTestStructArrayElement * value_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRUCT) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&value_iter, &value_element_iter);

			value_element = nih_new (value, ProxyTestStructArrayElement);
			if (! value_element) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_element_iter, &value_element_item0_dbus);

			value_element_item0 = nih_strdup (value_element, value_element_item0_dbus);
			if (! value_element_item0) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&value_element_iter);

			value_element->item0 = value_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_element_iter, &value_element_item1);

			dbus_message_iter_next (&value_element_iter);

			value_element->item1 = value_element_item1;

			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (ProxyTestStructArrayElement *)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (ProxyTestStructArrayElement *) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetStructArrayReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_struct_array_sync (const void *                   parent,
                                  NihDBusProxy *                 proxy,
                                  ProxyTestStructArrayElement ***value)
{
	DBusMessage *                 method_call;
	DBusMessageIter               iter;
	DBusMessageIter               variter;
	DBusError                     error;
	DBusMessage *                 reply;
	const char *                  interface;
	const char *                  property;
	DBusMessageIter               local_iter;
	size_t                        local_size;
	ProxyTestStructArrayElement **local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "struct_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;

		local = nih_alloc (parent, sizeof (ProxyTestStructArrayElement *));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter               local_element_iter;
			const char *                  local_element_item0_dbus;
			char *                        local_element_item0;
			uint32_t                      local_element_item1;
			ProxyTestStructArrayElement **local_tmp;
			ProxyTestStructArrayElement * local_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_STRUCT) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&local_iter, &local_element_iter);

			local_element = nih_new (local, ProxyTestStructArrayElement);
			if (! local_element) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_STRING) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_element_iter, &local_element_item0_dbus);

			local_element_item0 = nih_strdup (local_element, local_element_item0_dbus);
			if (! local_element_item0) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&local_element_iter);

			local_element->item0 = local_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_element_iter, &local_element_item1);

			dbus_message_iter_next (&local_element_iter);

			local_element->item1 = local_element_item1;

			if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (ProxyTestStructArrayElement *)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (ProxyTestStructArrayElement *) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_struct_array (NihDBusProxy *                       proxy,
                             ProxyTestStructArrayElement * const *value,
                             ProxyTestSetStructArrayReply         handler,
                             NihDBusErrorHandler                  error_handler,
                             void *                               data,
                             int                                  timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;
	DBusMessageIter     value_iter;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "struct_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "a(su)", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "(su)", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                    value_element_iter;
			const char *                       value_element_item0;
			uint32_t                           value_element_item1;
			const ProxyTestStructArrayElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_STRUCT, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_struct_array_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_struct_array_set_notify (DBusPendingCall *   pending_call,
                                                     NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetStructArrayReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_struct_array_sync (const void *                         parent,
                                  NihDBusProxy *                       proxy,
                                  ProxyTestStructArrayElement * const *value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter value_iter;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "struct_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "a(su)", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "(su)", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                    value_element_iter;
			const char *                       value_element_item0;
			uint32_t                           value_element_item1;
			const ProxyTestStructArrayElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_STRUCT, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_dict_entry_array (NihDBusProxy *                  proxy,
                                 ProxyTestGetDictEntryArrayReply handler,
                                 NihDBusErrorHandler             error_handler,
                                 void *                          data,
                                 int                             timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "dict_entry_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_dict_entry_array_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_dict_entry_array_get_notify (DBusPendingCall *   pending_call,
                                                         NihDBusPendingData *pending_data)
{
	DBusMessage *                    reply;
	DBusMessageIter                  iter;
	DBusMessageIter                  variter;
	NihDBusMessage *                 message;
	DBusError                        error;
	DBusMessageIter                  value_iter;
	size_t                           value_size;
	ProxyTestDictEntryArrayElement **value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;

		value = nih_alloc (message, sizeof (ProxyTestDictEntryArrayElement *));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter                  value_element_iter;
			const char *                     value_element_item0_dbus;
			char *                           value_element_item0;
			uint32_t                         value_element_item1;
			ProxyTestDictEntryArrayElement **value_tmp;
			ProxyTestDictEntryArrayElement * value_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_DICT_ENTRY) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&value_iter, &value_element_iter);

			value_element = nih_new (value, ProxyTestDictEntryArrayElement);
			if (! value_element) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_element_iter, &value_element_item0_dbus);

			value_element_item0 = nih_strdup (value_element, value_element_item0_dbus);
			if (! value_element_item0) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&value_element_iter);

			value_element->item0 = value_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_element_iter, &value_element_item1);

			dbus_message_iter_next (&value_element_iter);

			value_element->item1 = value_element_item1;

			if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (ProxyTestDictEntryArrayElement *)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (ProxyTestDictEntryArrayElement *) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetDictEntryArrayReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_dict_entry_array_sync (const void *                      parent,
                                      NihDBusProxy *                    proxy,
                                      ProxyTestDictEntryArrayElement ***value)
{
	DBusMessage *                    method_call;
	DBusMessageIter                  iter;
	DBusMessageIter                  variter;
	DBusError                        error;
	DBusMessage *                    reply;
	const char *                     interface;
	const char *                     property;
	DBusMessageIter                  local_iter;
	size_t                           local_size;
	ProxyTestDictEntryArrayElement **local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "dict_entry_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;

		local = nih_alloc (parent, sizeof (ProxyTestDictEntryArrayElement *));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter                  local_element_iter;
			const char *                     local_element_item0_dbus;
			char *                           local_element_item0;
			uint32_t                         local_element_item1;
			ProxyTestDictEntryArrayElement **local_tmp;
			ProxyTestDictEntryArrayElement * local_element;

			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_DICT_ENTRY) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&local_iter, &local_element_iter);

			local_element = nih_new (local, ProxyTestDictEntryArrayElement);
			if (! local_element) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_STRING) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_element_iter, &local_element_item0_dbus);

			local_element_item0 = nih_strdup (local_element, local_element_item0_dbus);
			if (! local_element_item0) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&local_element_iter);

			local_element->item0 = local_element_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_UINT32) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_element_iter, &local_element_item1);

			dbus_message_iter_next (&local_element_iter);

			local_element->item1 = local_element_item1;

			if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_INVALID) {
				nih_free (local_element);
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (ProxyTestDictEntryArrayElement *)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (ProxyTestDictEntryArrayElement *) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_dict_entry_array (NihDBusProxy *                          proxy,
                                 ProxyTestDictEntryArrayElement * const *value,
                                 ProxyTestSetDictEntryArrayReply         handler,
                                 NihDBusErrorHandler                     error_handler,
                                 void *                                  data,
                                 int                                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;
	DBusMessageIter     value_iter;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "dict_entry_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "a{su}", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "{su}", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                       value_element_iter;
			const char *                          value_element_item0;
			uint32_t                              value_element_item1;
			const ProxyTestDictEntryArrayElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_DICT_ENTRY, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_dict_entry_array_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_dict_entry_array_set_notify (DBusPendingCall *   pending_call,
                                                         NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetDictEntryArrayReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_dict_entry_array_sync (const void *                            parent,
                                      NihDBusProxy *                          proxy,
                                      ProxyTestDictEntryArrayElement * const *value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter value_iter;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "dict_entry_array";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "a{su}", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "{su}", &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                       value_element_iter;
			const char *                          value_element_item0;
			uint32_t                              value_element_item1;
			const ProxyTestDictEntryArrayElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_DICT_ENTRY, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (&iter, &variter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_unix_fd (NihDBusProxy *          proxy,
                        ProxyTestGetUnixFdReply handler,
                        NihDBusErrorHandler     error_handler,
                        void *                  data,
                        int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "unix_fd";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_unix_fd_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_unix_fd_get_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	int             value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UNIX_FD) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value);

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetUnixFdReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_unix_fd_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             int *         value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	int             local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "unix_fd";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a int from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UNIX_FD) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local);

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}

DBusPendingCall *
proxy_test_set_unix_fd (NihDBusProxy *          proxy,
                        int                     value,
                        ProxyTestSetUnixFdReply handler,
                        NihDBusErrorHandler     error_handler,
                        void *                  data,
                        int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusMessageIter     variter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "unix_fd";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "h", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UNIX_FD, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_unix_fd_set_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_unix_fd_set_notify (DBusPendingCall *   pending_call,
                                                NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and check
	 * there are no arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((ProxyTestSetUnixFdReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_set_unix_fd_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             int           value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Set");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "unix_fd";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT, "h", &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UNIX_FD, &value)) {
		dbus_message_iter_abandon_container (&iter, &variter);
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (! dbus_message_iter_close_container (&iter, &variter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	/* Check the reply has no arguments */
	dbus_message_unref (method_call);
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
proxy_test_get_all (NihDBusProxy *       proxy,
                    ProxyTestGetAllReply handler,
                    NihDBusErrorHandler  error_handler,
                    void *               data,
                    int                  timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "GetAll");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)proxy_com_netsplit_Nih_Test_get_all_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
proxy_com_netsplit_Nih_Test_get_all_notify (DBusPendingCall *   pending_call,
                                            NihDBusPendingData *pending_data)
{
	DBusMessage *                    reply;
	DBusMessageIter                  iter;
	DBusMessageIter                  arrayiter;
	DBusMessageIter                  dictiter;
	DBusMessageIter                  variter;
	NihDBusMessage *                 message;
	DBusError                        error;
	const char *                     property;
	ProxyTestProperties *            properties;
	size_t                           property_count;
	uint8_t                          byte;
	int                              boolean;
	int16_t                          int16;
	uint16_t                         uint16;
	int32_t                          int32;
	uint32_t                         uint32;
	int64_t                          int64;
	uint64_t                         uint64;
	double                           dubble;
	char *                           string;
	const char *                     string_dbus;
	char *                           object_path;
	const char *                     object_path_dbus;
	char *                           signature;
	const char *                     signature_dbus;
	ProxyTestStructure *             structure;
	DBusMessageIter                  structure_iter;
	const char *                     structure_item0_dbus;
	char *                           structure_item0;
	uint32_t                         structure_item1;
	int32_t *                        int32_array;
	size_t                           int32_array_len;
	DBusMessageIter                  int32_array_iter;
	char **                          str_array;
	DBusMessageIter                  str_array_iter;
	size_t                           str_array_size;
	int32_t **                       int32_array_array;
	size_t *                         int32_array_array_len;
	DBusMessageIter                  int32_array_array_iter;
	size_t                           int32_array_array_size;
	ProxyTestStructArrayElement **   struct_array;
	DBusMessageIter                  struct_array_iter;
	size_t                           struct_array_size;
	ProxyTestDictEntryArrayElement **dict_entry_array;
	DBusMessageIter                  dict_entry_array_iter;
	size_t                           dict_entry_array_size;
	int                              unix_fd;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and iterate
	 * over and recurse into the arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

	/* Iterate the method arguments, recursing into the array */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	properties = NIH_MUST (nih_new (message, ProxyTestProperties));
	property_count = 0;

	dbus_message_iter_recurse (&iter, &arrayiter);

	while (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_INVALID) {
		__label__ enomem;

		if (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_DICT_ENTRY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&arrayiter, &dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&dictiter, &property);

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&dictiter, &variter);

		if (! strcmp (property, "byte")) {
			/* Demarshal a uint8_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BYTE) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &byte);

			dbus_message_iter_next (&variter);

			properties->byte = byte;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "boolean")) {
			/* Demarshal a int from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BOOLEAN) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &boolean);

			dbus_message_iter_next (&variter);

			properties->boolean = boolean;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int16")) {
			/* Demarshal a int16_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT16) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &int16);

			dbus_message_iter_next (&variter);

			properties->int16 = int16;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "uint16")) {
			/* Demarshal a uint16_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT16) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &uint16);

			dbus_message_iter_next (&variter);

			properties->uint16 = uint16;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int32")) {
			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT32) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &int32);

			dbus_message_iter_next (&variter);

			properties->int32 = int32;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "uint32")) {
			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT32) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &uint32);

			dbus_message_iter_next (&variter);

			properties->uint32 = uint32;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int64")) {
			/* Demarshal a int64_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT64) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &int64);

			dbus_message_iter_next (&variter);

			properties->int64 = int64;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "uint64")) {
			/* Demarshal a uint64_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT64) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &uint64);

			dbus_message_iter_next (&variter);

			properties->uint64 = uint64;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "double")) {
			/* Demarshal a double from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_DOUBLE) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &dubble);

			dbus_message_iter_next (&variter);

			properties->dubble = dubble;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "string")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &string_dbus);

			string = nih_strdup (properties, string_dbus);
			if (! string) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->string = string;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "object_path")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_OBJECT_PATH) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &object_path_dbus);

			object_path = nih_strdup (properties, object_path_dbus);
			if (! object_path) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->object_path = object_path;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "signature")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_SIGNATURE) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &signature_dbus);

			signature = nih_strdup (properties, signature_dbus);
			if (! signature) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->signature = signature;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "structure")) {
			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRUCT) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &structure_iter);

			structure = nih_new (properties, ProxyTestStructure);
			if (! structure) {
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&structure_iter) != DBUS_TYPE_STRING) {
				nih_free (structure);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&structure_iter, &structure_item0_dbus);

			structure_item0 = nih_strdup (structure, structure_item0_dbus);
			if (! structure_item0) {
				nih_free (structure);
				goto enomem;
			}

			dbus_message_iter_next (&structure_iter);

			structure->item0 = structure_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&structure_iter) != DBUS_TYPE_UINT32) {
				nih_free (structure);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&structure_iter, &structure_item1);

			dbus_message_iter_next (&structure_iter);

			structure->item1 = structure_item1;

			if (dbus_message_iter_get_arg_type (&structure_iter) != DBUS_TYPE_INVALID) {
				nih_free (structure);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_next (&variter);

			properties->structure = structure;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int32_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &int32_array_iter);

			int32_array_len = 0;
			int32_array = NULL;

			while (dbus_message_iter_get_arg_type (&int32_array_iter) != DBUS_TYPE_INVALID) {
				int32_t *int32_array_tmp;
				int32_t  int32_array_element;

				/* Demarshal a int32_t from the message */
				if (dbus_message_iter_get_arg_type (&int32_array_iter) != DBUS_TYPE_INT32) {
					if (int32_array)
						nih_free (int32_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&int32_array_iter, &int32_array_element);

				dbus_message_iter_next (&int32_array_iter);

				if (int32_array_len + 1 > SIZE_MAX / sizeof (int32_t)) {
					if (int32_array)
						nih_free (int32_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				int32_array_tmp = nih_realloc (int32_array, properties, sizeof (int32_t) * (int32_array_len + 1));
				if (! int32_array_tmp) {
					if (int32_array)
						nih_free (int32_array);
					goto enomem;
				}

				int32_array = int32_array_tmp;
				int32_array[int32_array_len] = int32_array_element;

				int32_array_len++;
			}

			dbus_message_iter_next (&variter);

			properties->int32_array = int32_array;
			properties->int32_array_len = int32_array_len;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "str_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &str_array_iter);

			str_array_size = 0;
			str_array = NULL;

			str_array = nih_alloc (properties, sizeof (char *));
			if (! str_array) {
				goto enomem;
			}

			str_array[str_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&str_array_iter) != DBUS_TYPE_INVALID) {
				const char *str_array_element_dbus;
				char **     str_array_tmp;
				char *      str_array_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&str_array_iter) != DBUS_TYPE_STRING) {
					if (str_array)
						nih_free (str_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&str_array_iter, &str_array_element_dbus);

				str_array_element = nih_strdup (str_array, str_array_element_dbus);
				if (! str_array_element) {
					if (str_array)
						nih_free (str_array);
					goto enomem;
				}

				dbus_message_iter_next (&str_array_iter);

				if (str_array_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (str_array)
						nih_free (str_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				str_array_tmp = nih_realloc (str_array, properties, sizeof (char *) * (str_array_size + 2));
				if (! str_array_tmp) {
					if (str_array)
						nih_free (str_array);
					goto enomem;
				}

				str_array = str_array_tmp;
				str_array[str_array_size] = str_array_element;
				str_array[str_array_size + 1] = NULL;

				str_array_size++;
			}

			dbus_message_iter_next (&variter);

			properties->str_array = str_array;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int32_array_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &int32_array_array_iter);

			int32_array_array_size = 0;
			int32_array_array = NULL;
			int32_array_array_len = NULL;

			int32_array_array = nih_alloc (properties, sizeof (int32_t *));
			if (! int32_array_array) {
				goto enomem;
			}

			int32_array_array[int32_array_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&int32_array_array_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter int32_array_array_element_iter;
				int32_t **      int32_array_array_tmp;
				int32_t *       int32_array_array_element;
				size_t *        int32_array_array_len_tmp;
				size_t          int32_array_array_element_len;

				/* Demarshal an array from the message */
				if (dbus_message_iter_get_arg_type (&int32_array_array_iter) != DBUS_TYPE_ARRAY) {
					if (int32_array_array)
						nih_free (int32_array_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_recurse (&int32_array_array_iter, &int32_array_array_element_iter);

				int32_array_array_element_len = 0;
				int32_array_array_element = NULL;

				while (dbus_message_iter_get_arg_type (&int32_array_array_element_iter) != DBUS_TYPE_INVALID) {
					int32_t *int32_array_array_element_tmp;
					int32_t  int32_array_array_element_element;

					/* Demarshal a int32_t from the message */
					if (dbus_message_iter_get_arg_type (&int32_array_array_element_iter) != DBUS_TYPE_INT32) {
						if (int32_array_array_element)
							nih_free (int32_array_array_element);
						if (int32_array_array)
							nih_free (int32_array_array);
						nih_error_push_context ();
						nih_error_raise (NIH_DBUS_INVALID_ARGS,
						                 _(NIH_DBUS_INVALID_ARGS_STR));
						pending_data->error_handler (pending_data->data, message);
						nih_error_pop_context ();

						nih_free (message);
						dbus_message_unref (reply);
						return;
					}

					dbus_message_iter_get_basic (&int32_array_array_element_iter, &int32_array_array_element_element);

					dbus_message_iter_next (&int32_array_array_element_iter);

					if (int32_array_array_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
						if (int32_array_array_element)
							nih_free (int32_array_array_element);
						if (int32_array_array)
							nih_free (int32_array_array);
						nih_error_push_context ();
						nih_error_raise (NIH_DBUS_INVALID_ARGS,
						                 _(NIH_DBUS_INVALID_ARGS_STR));
						pending_data->error_handler (pending_data->data, message);
						nih_error_pop_context ();

						nih_free (message);
						dbus_message_unref (reply);
						return;
					}

					int32_array_array_element_tmp = nih_realloc (int32_array_array_element, int32_array_array, sizeof (int32_t) * (int32_array_array_element_len + 1));
					if (! int32_array_array_element_tmp) {
						if (int32_array_array_element)
							nih_free (int32_array_array_element);
						if (int32_array_array)
							nih_free (int32_array_array);
						goto enomem;
					}

					int32_array_array_element = int32_array_array_element_tmp;
					int32_array_array_element[int32_array_array_element_len] = int32_array_array_element_element;

					int32_array_array_element_len++;
				}

				dbus_message_iter_next (&int32_array_array_iter);

				if (int32_array_array_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
					if (int32_array_array)
						nih_free (int32_array_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				int32_array_array_tmp = nih_realloc (int32_array_array, properties, sizeof (int32_t *) * (int32_array_array_size + 2));
				if (! int32_array_array_tmp) {
					if (int32_array_array)
						nih_free (int32_array_array);
					goto enomem;
				}

				int32_array_array = int32_array_array_tmp;
				int32_array_array[int32_array_array_size] = int32_array_array_element;
				int32_array_array[int32_array_array_size + 1] = NULL;

				if (int32_array_array_size + 1 > SIZE_MAX / sizeof (size_t)) {
					if (int32_array_array)
						nih_free (int32_array_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				int32_array_array_len_tmp = nih_realloc (int32_array_array_len, int32_array_array, sizeof (size_t) * (int32_array_array_size + 1));
				if (! int32_array_array_len_tmp) {
					if (int32_array_array)
						nih_free (int32_array_array);
					goto enomem;
				}

				int32_array_array_len = int32_array_array_len_tmp;
				int32_array_array_len[int32_array_array_size] = int32_array_array_element_len;

				int32_array_array_size++;
			}

			dbus_message_iter_next (&variter);

			properties->int32_array_array = int32_array_array;
			properties->int32_array_array_len = int32_array_array_len;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "struct_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &struct_array_iter);

			struct_array_size = 0;
			struct_array = NULL;

			struct_array = nih_alloc (properties, sizeof (ProxyTestStructArrayElement *));
			if (! struct_array) {
				goto enomem;
			}

			struct_array[struct_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&struct_array_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter               struct_array_element_iter;
				const char *                  struct_array_element_item0_dbus;
				char *                        struct_array_element_item0;
				uint32_t                      struct_array_element_item1;
				ProxyTestStructArrayElement **struct_array_tmp;
				ProxyTestStructArrayElement * struct_array_element;

				/* Demarshal a structure from the message */
				if (dbus_message_iter_get_arg_type (&struct_array_iter) != DBUS_TYPE_STRUCT) {
					if (struct_array)
						nih_free (struct_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_recurse (&struct_array_iter, &struct_array_element_iter);

				struct_array_element = nih_new (struct_array, ProxyTestStructArrayElement);
				if (! struct_array_element) {
					if (struct_array)
						nih_free (struct_array);
					goto enomem;
				}

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&struct_array_element_iter) != DBUS_TYPE_STRING) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&struct_array_element_iter, &struct_array_element_item0_dbus);

				struct_array_element_item0 = nih_strdup (struct_array_element, struct_array_element_item0_dbus);
				if (! struct_array_element_item0) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					goto enomem;
				}

				dbus_message_iter_next (&struct_array_element_iter);

				struct_array_element->item0 = struct_array_element_item0;

				/* Demarshal a uint32_t from the message */
				if (dbus_message_iter_get_arg_type (&struct_array_element_iter) != DBUS_TYPE_UINT32) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&struct_array_element_iter, &struct_array_element_item1);

				dbus_message_iter_next (&struct_array_element_iter);

				struct_array_element->item1 = struct_array_element_item1;

				if (dbus_message_iter_get_arg_type (&struct_array_element_iter) != DBUS_TYPE_INVALID) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_next (&struct_array_iter);

				if (struct_array_size + 2 > SIZE_MAX / sizeof (ProxyTestStructArrayElement *)) {
					if (struct_array)
						nih_free (struct_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				struct_array_tmp = nih_realloc (struct_array, properties, sizeof (ProxyTestStructArrayElement *) * (struct_array_size + 2));
				if (! struct_array_tmp) {
					if (struct_array)
						nih_free (struct_array);
					goto enomem;
				}

				struct_array = struct_array_tmp;
				struct_array[struct_array_size] = struct_array_element;
				struct_array[struct_array_size + 1] = NULL;

				struct_array_size++;
			}

			dbus_message_iter_next (&variter);

			properties->struct_array = struct_array;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "dict_entry_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &dict_entry_array_iter);

			dict_entry_array_size = 0;
			dict_entry_array = NULL;

			dict_entry_array = nih_alloc (properties, sizeof (ProxyTestDictEntryArrayElement *));
			if (! dict_entry_array) {
				goto enomem;
			}

			dict_entry_array[dict_entry_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&dict_entry_array_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter                  dict_entry_array_element_iter;
				const char *                     dict_entry_array_element_item0_dbus;
				char *                           dict_entry_array_element_item0;
				uint32_t                         dict_entry_array_element_item1;
				ProxyTestDictEntryArrayElement **dict_entry_array_tmp;
				ProxyTestDictEntryArrayElement * dict_entry_array_element;

				/* Demarshal a structure from the message */
				if (dbus_message_iter_get_arg_type (&dict_entry_array_iter) != DBUS_TYPE_DICT_ENTRY) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_recurse (&dict_entry_array_iter, &dict_entry_array_element_iter);

				dict_entry_array_element = nih_new (dict_entry_array, ProxyTestDictEntryArrayElement);
				if (! dict_entry_array_element) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					goto enomem;
				}

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&dict_entry_array_element_iter) != DBUS_TYPE_STRING) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&dict_entry_array_element_iter, &dict_entry_array_element_item0_dbus);

				dict_entry_array_element_item0 = nih_strdup (dict_entry_array_element, dict_entry_array_element_item0_dbus);
				if (! dict_entry_array_element_item0) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					goto enomem;
				}

				dbus_message_iter_next (&dict_entry_array_element_iter);

				dict_entry_array_element->item0 = dict_entry_array_element_item0;

				/* Demarshal a uint32_t from the message */
				if (dbus_message_iter_get_arg_type (&dict_entry_array_element_iter) != DBUS_TYPE_UINT32) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&dict_entry_array_element_iter, &dict_entry_array_element_item1);

				dbus_message_iter_next (&dict_entry_array_element_iter);

				dict_entry_array_element->item1 = dict_entry_array_element_item1;

				if (dbus_message_iter_get_arg_type (&dict_entry_array_element_iter) != DBUS_TYPE_INVALID) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_next (&dict_entry_array_iter);

				if (dict_entry_array_size + 2 > SIZE_MAX / sizeof (ProxyTestDictEntryArrayElement *)) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dict_entry_array_tmp = nih_realloc (dict_entry_array, properties, sizeof (ProxyTestDictEntryArrayElement *) * (dict_entry_array_size + 2));
				if (! dict_entry_array_tmp) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					goto enomem;
				}

				dict_entry_array = dict_entry_array_tmp;
				dict_entry_array[dict_entry_array_size] = dict_entry_array_element;
				dict_entry_array[dict_entry_array_size + 1] = NULL;

				dict_entry_array_size++;
			}

			dbus_message_iter_next (&variter);

			properties->dict_entry_array = dict_entry_array;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "unix_fd")) {
			/* Demarshal a int from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UNIX_FD) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &unix_fd);

			dbus_message_iter_next (&variter);

			properties->unix_fd = unix_fd;

			nih_assert (++property_count);
		}

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_next (&arrayiter);
	enomem: __attribute__ ((unused));
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	if (property_count < 19) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((ProxyTestGetAllReply)pending_data->handler) (pending_data->data, message, properties);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
proxy_test_get_all_sync (const void *          parent,
                         NihDBusProxy *        proxy,
                         ProxyTestProperties **properties)
{
	DBusMessage *                    method_call;
	DBusMessageIter                  iter;
	DBusMessageIter                  arrayiter;
	DBusMessageIter                  dictiter;
	DBusMessageIter                  variter;
	DBusError                        error;
	DBusMessage *                    reply;
	size_t                           property_count;
	const char *                     interface;
	const char *                     property;
	uint8_t                          byte;
	int                              boolean;
	int16_t                          int16;
	uint16_t                         uint16;
	int32_t                          int32;
	uint32_t                         uint32;
	int64_t                          int64;
	uint64_t                         uint64;
	double                           dubble;
	char *                           string;
	const char *                     string_dbus;
	char *                           object_path;
	const char *                     object_path_dbus;
	char *                           signature;
	const char *                     signature_dbus;
	ProxyTestStructure *             structure;
	DBusMessageIter                  structure_iter;
	const char *                     structure_item0_dbus;
	char *                           structure_item0;
	uint32_t                         structure_item1;
	int32_t *                        int32_array;
	size_t                           int32_array_len;
	DBusMessageIter                  int32_array_iter;
	char **                          str_array;
	DBusMessageIter                  str_array_iter;
	size_t                           str_array_size;
	int32_t **                       int32_array_array;
	size_t *                         int32_array_array_len;
	DBusMessageIter                  int32_array_array_iter;
	size_t                           int32_array_array_size;
	ProxyTestStructArrayElement **   struct_array;
	DBusMessageIter                  struct_array_iter;
	size_t                           struct_array_size;
	ProxyTestDictEntryArrayElement **dict_entry_array;
	DBusMessageIter                  dict_entry_array_iter;
	size_t                           dict_entry_array_size;
	int                              unix_fd;

	nih_assert (proxy != NULL);
	nih_assert (properties != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "GetAll");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.netsplit.Nih.Test";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the array */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	*properties = NIH_MUST (nih_new (parent, ProxyTestProperties));
	property_count = 0;

	dbus_message_iter_recurse (&iter, &arrayiter);

	while (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_INVALID) {
		__label__ enomem;

		if (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_DICT_ENTRY) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&arrayiter, &dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_STRING) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&dictiter, &property);

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_VARIANT) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&dictiter, &variter);

		if (! strcmp (property, "byte")) {
			/* Demarshal a uint8_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BYTE) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &byte);

			dbus_message_iter_next (&variter);

			(*properties)->byte = byte;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "boolean")) {
			/* Demarshal a int from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BOOLEAN) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &boolean);

			dbus_message_iter_next (&variter);

			(*properties)->boolean = boolean;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int16")) {
			/* Demarshal a int16_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT16) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &int16);

			dbus_message_iter_next (&variter);

			(*properties)->int16 = int16;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "uint16")) {
			/* Demarshal a uint16_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT16) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &uint16);

			dbus_message_iter_next (&variter);

			(*properties)->uint16 = uint16;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int32")) {
			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT32) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &int32);

			dbus_message_iter_next (&variter);

			(*properties)->int32 = int32;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "uint32")) {
			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT32) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &uint32);

			dbus_message_iter_next (&variter);

			(*properties)->uint32 = uint32;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int64")) {
			/* Demarshal a int64_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT64) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &int64);

			dbus_message_iter_next (&variter);

			(*properties)->int64 = int64;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "uint64")) {
			/* Demarshal a uint64_t from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT64) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &uint64);

			dbus_message_iter_next (&variter);

			(*properties)->uint64 = uint64;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "double")) {
			/* Demarshal a double from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_DOUBLE) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &dubble);

			dbus_message_iter_next (&variter);

			(*properties)->dubble = dubble;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "string")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &string_dbus);

			string = nih_strdup (*properties, string_dbus);
			if (! string) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->string = string;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "object_path")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_OBJECT_PATH) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &object_path_dbus);

			object_path = nih_strdup (*properties, object_path_dbus);
			if (! object_path) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->object_path = object_path;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "signature")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_SIGNATURE) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &signature_dbus);

			signature = nih_strdup (*properties, signature_dbus);
			if (! signature) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->signature = signature;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "structure")) {
			/* Demarshal a structure from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRUCT) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &structure_iter);

			structure = nih_new (*properties, ProxyTestStructure);
			if (! structure) {
				goto enomem;
			}

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&structure_iter) != DBUS_TYPE_STRING) {
				nih_free (structure);
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&structure_iter, &structure_item0_dbus);

			structure_item0 = nih_strdup (structure, structure_item0_dbus);
			if (! structure_item0) {
				nih_free (structure);
				goto enomem;
			}

			dbus_message_iter_next (&structure_iter);

			structure->item0 = structure_item0;

			/* Demarshal a uint32_t from the message */
			if (dbus_message_iter_get_arg_type (&structure_iter) != DBUS_TYPE_UINT32) {
				nih_free (structure);
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&structure_iter, &structure_item1);

			dbus_message_iter_next (&structure_iter);

			structure->item1 = structure_item1;

			if (dbus_message_iter_get_arg_type (&structure_iter) != DBUS_TYPE_INVALID) {
				nih_free (structure);
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_next (&variter);

			(*properties)->structure = structure;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int32_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &int32_array_iter);

			int32_array_len = 0;
			int32_array = NULL;

			while (dbus_message_iter_get_arg_type (&int32_array_iter) != DBUS_TYPE_INVALID) {
				int32_t *int32_array_tmp;
				int32_t  int32_array_element;

				/* Demarshal a int32_t from the message */
				if (dbus_message_iter_get_arg_type (&int32_array_iter) != DBUS_TYPE_INT32) {
					if (int32_array)
						nih_free (int32_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&int32_array_iter, &int32_array_element);

				dbus_message_iter_next (&int32_array_iter);

				if (int32_array_len + 1 > SIZE_MAX / sizeof (int32_t)) {
					if (int32_array)
						nih_free (int32_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				int32_array_tmp = nih_realloc (int32_array, *properties, sizeof (int32_t) * (int32_array_len + 1));
				if (! int32_array_tmp) {
					if (int32_array)
						nih_free (int32_array);
					goto enomem;
				}

				int32_array = int32_array_tmp;
				int32_array[int32_array_len] = int32_array_element;

				int32_array_len++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->int32_array = int32_array;
			(*properties)->int32_array_len = int32_array_len;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "str_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &str_array_iter);

			str_array_size = 0;
			str_array = NULL;

			str_array = nih_alloc (*properties, sizeof (char *));
			if (! str_array) {
				goto enomem;
			}

			str_array[str_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&str_array_iter) != DBUS_TYPE_INVALID) {
				const char *str_array_element_dbus;
				char **     str_array_tmp;
				char *      str_array_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&str_array_iter) != DBUS_TYPE_STRING) {
					if (str_array)
						nih_free (str_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&str_array_iter, &str_array_element_dbus);

				str_array_element = nih_strdup (str_array, str_array_element_dbus);
				if (! str_array_element) {
					if (str_array)
						nih_free (str_array);
					goto enomem;
				}

				dbus_message_iter_next (&str_array_iter);

				if (str_array_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (str_array)
						nih_free (str_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				str_array_tmp = nih_realloc (str_array, *properties, sizeof (char *) * (str_array_size + 2));
				if (! str_array_tmp) {
					if (str_array)
						nih_free (str_array);
					goto enomem;
				}

				str_array = str_array_tmp;
				str_array[str_array_size] = str_array_element;
				str_array[str_array_size + 1] = NULL;

				str_array_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->str_array = str_array;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "int32_array_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &int32_array_array_iter);

			int32_array_array_size = 0;
			int32_array_array = NULL;
			int32_array_array_len = NULL;

			int32_array_array = nih_alloc (*properties, sizeof (int32_t *));
			if (! int32_array_array) {
				goto enomem;
			}

			int32_array_array[int32_array_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&int32_array_array_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter int32_array_array_element_iter;
				int32_t **      int32_array_array_tmp;
				int32_t *       int32_array_array_element;
				size_t *        int32_array_array_len_tmp;
				size_t          int32_array_array_element_len;

				/* Demarshal an array from the message */
				if (dbus_message_iter_get_arg_type (&int32_array_array_iter) != DBUS_TYPE_ARRAY) {
					if (int32_array_array)
						nih_free (int32_array_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_recurse (&int32_array_array_iter, &int32_array_array_element_iter);

				int32_array_array_element_len = 0;
				int32_array_array_element = NULL;

				while (dbus_message_iter_get_arg_type (&int32_array_array_element_iter) != DBUS_TYPE_INVALID) {
					int32_t *int32_array_array_element_tmp;
					int32_t  int32_array_array_element_element;

					/* Demarshal a int32_t from the message */
					if (dbus_message_iter_get_arg_type (&int32_array_array_element_iter) != DBUS_TYPE_INT32) {
						if (int32_array_array_element)
							nih_free (int32_array_array_element);
						if (int32_array_array)
							nih_free (int32_array_array);
						nih_free (*properties);
						*properties = NULL;
						dbus_message_unref (reply);
						nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
						                  _(NIH_DBUS_INVALID_ARGS_STR));
					}

					dbus_message_iter_get_basic (&int32_array_array_element_iter, &int32_array_array_element_element);

					dbus_message_iter_next (&int32_array_array_element_iter);

					if (int32_array_array_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
						if (int32_array_array_element)
							nih_free (int32_array_array_element);
						if (int32_array_array)
							nih_free (int32_array_array);
						nih_free (*properties);
						*properties = NULL;
						dbus_message_unref (reply);
						nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
						                  _(NIH_DBUS_INVALID_ARGS_STR));
					}

					int32_array_array_element_tmp = nih_realloc (int32_array_array_element, int32_array_array, sizeof (int32_t) * (int32_array_array_element_len + 1));
					if (! int32_array_array_element_tmp) {
						if (int32_array_array_element)
							nih_free (int32_array_array_element);
						if (int32_array_array)
							nih_free (int32_array_array);
						goto enomem;
					}

					int32_array_array_element = int32_array_array_element_tmp;
					int32_array_array_element[int32_array_array_element_len] = int32_array_array_element_element;

					int32_array_array_element_len++;
				}

				dbus_message_iter_next (&int32_array_array_iter);

				if (int32_array_array_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
					if (int32_array_array)
						nih_free (int32_array_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				int32_array_array_tmp = nih_realloc (int32_array_array, *properties, sizeof (int32_t *) * (int32_array_array_size + 2));
				if (! int32_array_array_tmp) {
					if (int32_array_array)
						nih_free (int32_array_array);
					goto enomem;
				}

				int32_array_array = int32_array_array_tmp;
				int32_array_array[int32_array_array_size] = int32_array_array_element;
				int32_array_array[int32_array_array_size + 1] = NULL;

				if (int32_array_array_size + 1 > SIZE_MAX / sizeof (size_t)) {
					if (int32_array_array)
						nih_free (int32_array_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				int32_array_array_len_tmp = nih_realloc (int32_array_array_len, int32_array_array, sizeof (size_t) * (int32_array_array_size + 1));
				if (! int32_array_array_len_tmp) {
					if (int32_array_array)
						nih_free (int32_array_array);
					goto enomem;
				}

				int32_array_array_len = int32_array_array_len_tmp;
				int32_array_array_len[int32_array_array_size] = int32_array_array_element_len;

				int32_array_array_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->int32_array_array = int32_array_array;
			(*properties)->int32_array_array_len = int32_array_array_len;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "struct_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &struct_array_iter);

			struct_array_size = 0;
			struct_array = NULL;

			struct_array = nih_alloc (*properties, sizeof (ProxyTestStructArrayElement *));
			if (! struct_array) {
				goto enomem;
			}

			struct_array[struct_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&struct_array_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter               struct_array_element_iter;
				const char *                  struct_array_element_item0_dbus;
				char *                        struct_array_element_item0;
				uint32_t                      struct_array_element_item1;
				ProxyTestStructArrayElement **struct_array_tmp;
				ProxyTestStructArrayElement * struct_array_element;

				/* Demarshal a structure from the message */
				if (dbus_message_iter_get_arg_type (&struct_array_iter) != DBUS_TYPE_STRUCT) {
					if (struct_array)
						nih_free (struct_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_recurse (&struct_array_iter, &struct_array_element_iter);

				struct_array_element = nih_new (struct_array, ProxyTestStructArrayElement);
				if (! struct_array_element) {
					if (struct_array)
						nih_free (struct_array);
					goto enomem;
				}

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&struct_array_element_iter) != DBUS_TYPE_STRING) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&struct_array_element_iter, &struct_array_element_item0_dbus);

				struct_array_element_item0 = nih_strdup (struct_array_element, struct_array_element_item0_dbus);
				if (! struct_array_element_item0) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					goto enomem;
				}

				dbus_message_iter_next (&struct_array_element_iter);

				struct_array_element->item0 = struct_array_element_item0;

				/* Demarshal a uint32_t from the message */
				if (dbus_message_iter_get_arg_type (&struct_array_element_iter) != DBUS_TYPE_UINT32) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&struct_array_element_iter, &struct_array_element_item1);

				dbus_message_iter_next (&struct_array_element_iter);

				struct_array_element->item1 = struct_array_element_item1;

				if (dbus_message_iter_get_arg_type (&struct_array_element_iter) != DBUS_TYPE_INVALID) {
					nih_free (struct_array_element);
					if (struct_array)
						nih_free (struct_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_next (&struct_array_iter);

				if (struct_array_size + 2 > SIZE_MAX / sizeof (ProxyTestStructArrayElement *)) {
					if (struct_array)
						nih_free (struct_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				struct_array_tmp = nih_realloc (struct_array, *properties, sizeof (ProxyTestStructArrayElement *) * (struct_array_size + 2));
				if (! struct_array_tmp) {
					if (struct_array)
						nih_free (struct_array);
					goto enomem;
				}

				struct_array = struct_array_tmp;
				struct_array[struct_array_size] = struct_array_element;
				struct_array[struct_array_size + 1] = NULL;

				struct_array_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->struct_array = struct_array;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "dict_entry_array")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &dict_entry_array_iter);

			dict_entry_array_size = 0;
			dict_entry_array = NULL;

			dict_entry_array = nih_alloc (*properties, sizeof (ProxyTestDictEntryArrayElement *));
			if (! dict_entry_array) {
				goto enomem;
			}

			dict_entry_array[dict_entry_array_size] = NULL;

			while (dbus_message_iter_get_arg_type (&dict_entry_array_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter                  dict_entry_array_element_iter;
				const char *                     dict_entry_array_element_item0_dbus;
				char *                           dict_entry_array_element_item0;
				uint32_t                         dict_entry_array_element_item1;
				ProxyTestDictEntryArrayElement **dict_entry_array_tmp;
				ProxyTestDictEntryArrayElement * dict_entry_array_element;

				/* Demarshal a structure from the message */
				if (dbus_message_iter_get_arg_type (&dict_entry_array_iter) != DBUS_TYPE_DICT_ENTRY) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_recurse (&dict_entry_array_iter, &dict_entry_array_element_iter);

				dict_entry_array_element = nih_new (dict_entry_array, ProxyTestDictEntryArrayElement);
				if (! dict_entry_array_element) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					goto enomem;
				}

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&dict_entry_array_element_iter) != DBUS_TYPE_STRING) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&dict_entry_array_element_iter, &dict_entry_array_element_item0_dbus);

				dict_entry_array_element_item0 = nih_strdup (dict_entry_array_element, dict_entry_array_element_item0_dbus);
				if (! dict_entry_array_element_item0) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					goto enomem;
				}

				dbus_message_iter_next (&dict_entry_array_element_iter);

				dict_entry_array_element->item0 = dict_entry_array_element_item0;

				/* Demarshal a uint32_t from the message */
				if (dbus_message_iter_get_arg_type (&dict_entry_array_element_iter) != DBUS_TYPE_UINT32) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&dict_entry_array_element_iter, &dict_entry_array_element_item1);

				dbus_message_iter_next (&dict_entry_array_element_iter);

				dict_entry_array_element->item1 = dict_entry_array_element_item1;

				if (dbus_message_iter_get_arg_type (&dict_entry_array_element_iter) != DBUS_TYPE_INVALID) {
					nih_free (dict_entry_array_element);
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_next (&dict_entry_array_iter);

				if (dict_entry_array_size + 2 > SIZE_MAX / sizeof (ProxyTestDictEntryArrayElement *)) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dict_entry_array_tmp = nih_realloc (dict_entry_array, *properties, sizeof (ProxyTestDictEntryArrayElement *) * (dict_entry_array_size + 2));
				if (! dict_entry_array_tmp) {
					if (dict_entry_array)
						nih_free (dict_entry_array);
					goto enomem;
				}

				dict_entry_array = dict_entry_array_tmp;
				dict_entry_array[dict_entry_array_size] = dict_entry_array_element;
				dict_entry_array[dict_entry_array_size + 1] = NULL;

				dict_entry_array_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->dict_entry_array = dict_entry_array;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "unix_fd")) {
			/* Demarshal a int from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UNIX_FD) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &unix_fd);

			dbus_message_iter_next (&variter);

			(*properties)->unix_fd = unix_fd;

			nih_assert (++property_count);
		}

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_INVALID) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_next (&arrayiter);
	enomem: __attribute__ ((unused));
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (*properties);
		*properties = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	if (property_count < 19) {
		nih_free (*properties);
		*properties = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}
