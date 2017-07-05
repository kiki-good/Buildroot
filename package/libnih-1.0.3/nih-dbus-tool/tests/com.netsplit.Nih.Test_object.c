/* libnih
 *
 * tests/com.netsplit.Nih.Test_object.c - auto-generated D-Bus bindings
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
#include <nih-dbus/dbus_object.h>
#include <nih-dbus/errors.h>

#include "tests/com.netsplit.Nih.Test_object.h"


/* Prototypes for static functions */
static DBusHandlerResult my_com_netsplit_Nih_Test_OrdinaryMethod_method       (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_NamelessMethod_method       (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_AsyncMethod_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_ByteToStr_method            (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToByte_method            (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_BooleanToStr_method         (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToBoolean_method         (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_Int16ToStr_method           (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToInt16_method           (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_UInt16ToStr_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToUInt16_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_Int32ToStr_method           (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToInt32_method           (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_UInt32ToStr_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToUInt32_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_Int64ToStr_method           (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToInt64_method           (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_UInt64ToStr_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToUInt64_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_DoubleToStr_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToDouble_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_ObjectPathToStr_method      (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToObjectPath_method      (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_SignatureToStr_method       (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToSignature_method       (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StructToStr_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToStruct_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_Int32ArrayToStr_method      (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToInt32Array_method      (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrArrayToStr_method        (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToStrArray_method        (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToInt32ArrayArray_method (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StructArrayToStr_method     (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToStructArray_method     (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_DictEntryArrayToStr_method  (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToDictEntryArray_method  (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_UnixFdToStr_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult my_com_netsplit_Nih_Test_StrToUnixFd_method          (NihDBusObject *object, NihDBusMessage *message);
static int               my_com_netsplit_Nih_Test_byte_get                    (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_byte_set                    (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_boolean_get                 (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_boolean_set                 (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int16_get                   (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int16_set                   (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_uint16_get                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_uint16_set                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int32_get                   (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int32_set                   (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_uint32_get                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_uint32_set                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int64_get                   (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int64_set                   (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_uint64_get                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_uint64_set                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_double_get                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_double_set                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_string_get                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_string_set                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_object_path_get             (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_object_path_set             (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_signature_get               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_signature_set               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_structure_get               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_structure_set               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int32_array_get             (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int32_array_set             (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_str_array_get               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_str_array_set               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int32_array_array_get       (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_int32_array_array_set       (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_struct_array_get            (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_struct_array_set            (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_dict_entry_array_get        (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_dict_entry_array_set        (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_unix_fd_get                 (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               my_com_netsplit_Nih_Test_unix_fd_set                 (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);


/* Prototypes for externally implemented handler functions */
extern int my_test_ordinary_method          (void *data, NihDBusMessage *message, const char *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_nameless_method          (void *data, NihDBusMessage *message, const char *arg1, char **arg2)
	__attribute__ ((warn_unused_result));
extern int my_test_async_method             (void *data, NihDBusMessage *message, const char *input)
	__attribute__ ((warn_unused_result));
extern int my_test_byte_to_str              (void *data, NihDBusMessage *message, uint8_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_byte              (void *data, NihDBusMessage *message, const char *input, uint8_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_boolean_to_str           (void *data, NihDBusMessage *message, int input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_boolean           (void *data, NihDBusMessage *message, const char *input, int *output)
	__attribute__ ((warn_unused_result));
extern int my_test_int16_to_str             (void *data, NihDBusMessage *message, int16_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_int16             (void *data, NihDBusMessage *message, const char *input, int16_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_uint16_to_str            (void *data, NihDBusMessage *message, uint16_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_uint16            (void *data, NihDBusMessage *message, const char *input, uint16_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_int32_to_str             (void *data, NihDBusMessage *message, int32_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_int32             (void *data, NihDBusMessage *message, const char *input, int32_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_uint32_to_str            (void *data, NihDBusMessage *message, uint32_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_uint32            (void *data, NihDBusMessage *message, const char *input, uint32_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_int64_to_str             (void *data, NihDBusMessage *message, int64_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_int64             (void *data, NihDBusMessage *message, const char *input, int64_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_uint64_to_str            (void *data, NihDBusMessage *message, uint64_t input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_uint64            (void *data, NihDBusMessage *message, const char *input, uint64_t *output)
	__attribute__ ((warn_unused_result));
extern int my_test_double_to_str            (void *data, NihDBusMessage *message, double input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_double            (void *data, NihDBusMessage *message, const char *input, double *output)
	__attribute__ ((warn_unused_result));
extern int my_test_object_path_to_str       (void *data, NihDBusMessage *message, const char *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_object_path       (void *data, NihDBusMessage *message, const char *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_signature_to_str         (void *data, NihDBusMessage *message, const char *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_signature         (void *data, NihDBusMessage *message, const char *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_struct_to_str            (void *data, NihDBusMessage *message, const MyTestStructToStrInput *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_struct            (void *data, NihDBusMessage *message, const char *input, MyTestStrToStructOutput **output)
	__attribute__ ((warn_unused_result));
extern int my_test_int32_array_to_str       (void *data, NihDBusMessage *message, const int32_t *input, size_t input_len, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_int32_array       (void *data, NihDBusMessage *message, const char *input, int32_t **output, size_t *output_len)
	__attribute__ ((warn_unused_result));
extern int my_test_str_array_to_str         (void *data, NihDBusMessage *message, char * const *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_str_array         (void *data, NihDBusMessage *message, const char *input, char ***output)
	__attribute__ ((warn_unused_result));
extern int my_test_int32_array_array_to_str (void *data, NihDBusMessage *message, int32_t * const *input, const size_t *input_len, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_int32_array_array (void *data, NihDBusMessage *message, const char *input, int32_t ***output, size_t **output_len)
	__attribute__ ((warn_unused_result));
extern int my_test_struct_array_to_str      (void *data, NihDBusMessage *message, MyTestStructArrayToStrInputElement * const *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_struct_array      (void *data, NihDBusMessage *message, const char *input, MyTestStrToStructArrayOutputElement ***output)
	__attribute__ ((warn_unused_result));
extern int my_test_dict_entry_array_to_str  (void *data, NihDBusMessage *message, MyTestDictEntryArrayToStrInputElement * const *input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_dict_entry_array  (void *data, NihDBusMessage *message, const char *input, MyTestStrToDictEntryArrayOutputElement ***output)
	__attribute__ ((warn_unused_result));
extern int my_test_unix_fd_to_str           (void *data, NihDBusMessage *message, int input, char **output)
	__attribute__ ((warn_unused_result));
extern int my_test_str_to_unix_fd           (void *data, NihDBusMessage *message, const char *input, int *output)
	__attribute__ ((warn_unused_result));
extern int my_test_get_byte                 (void *data, NihDBusMessage *message, uint8_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_byte                 (void *data, NihDBusMessage *message, uint8_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_boolean              (void *data, NihDBusMessage *message, int *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_boolean              (void *data, NihDBusMessage *message, int value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_int16                (void *data, NihDBusMessage *message, int16_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_int16                (void *data, NihDBusMessage *message, int16_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_uint16               (void *data, NihDBusMessage *message, uint16_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_uint16               (void *data, NihDBusMessage *message, uint16_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_int32                (void *data, NihDBusMessage *message, int32_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_int32                (void *data, NihDBusMessage *message, int32_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_uint32               (void *data, NihDBusMessage *message, uint32_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_uint32               (void *data, NihDBusMessage *message, uint32_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_int64                (void *data, NihDBusMessage *message, int64_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_int64                (void *data, NihDBusMessage *message, int64_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_uint64               (void *data, NihDBusMessage *message, uint64_t *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_uint64               (void *data, NihDBusMessage *message, uint64_t value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_dubble               (void *data, NihDBusMessage *message, double *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_dubble               (void *data, NihDBusMessage *message, double value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_string               (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_string               (void *data, NihDBusMessage *message, const char *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_object_path          (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_object_path          (void *data, NihDBusMessage *message, const char *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_signature            (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_signature            (void *data, NihDBusMessage *message, const char *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_structure            (void *data, NihDBusMessage *message, MyTestStructure **value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_structure            (void *data, NihDBusMessage *message, const MyTestStructure *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_int32_array          (void *data, NihDBusMessage *message, int32_t **value, size_t *value_len)
	__attribute__ ((warn_unused_result));
extern int my_test_set_int32_array          (void *data, NihDBusMessage *message, const int32_t *value, size_t value_len)
	__attribute__ ((warn_unused_result));
extern int my_test_get_str_array            (void *data, NihDBusMessage *message, char ***value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_str_array            (void *data, NihDBusMessage *message, char * const *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_int32_array_array    (void *data, NihDBusMessage *message, int32_t ***value, size_t **value_len)
	__attribute__ ((warn_unused_result));
extern int my_test_set_int32_array_array    (void *data, NihDBusMessage *message, int32_t * const *value, const size_t *value_len)
	__attribute__ ((warn_unused_result));
extern int my_test_get_struct_array         (void *data, NihDBusMessage *message, MyTestStructArrayElement ***value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_struct_array         (void *data, NihDBusMessage *message, MyTestStructArrayElement * const *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_dict_entry_array     (void *data, NihDBusMessage *message, MyTestDictEntryArrayElement ***value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_dict_entry_array     (void *data, NihDBusMessage *message, MyTestDictEntryArrayElement * const *value)
	__attribute__ ((warn_unused_result));
extern int my_test_get_unix_fd              (void *data, NihDBusMessage *message, int *value)
	__attribute__ ((warn_unused_result));
extern int my_test_set_unix_fd              (void *data, NihDBusMessage *message, int value)
	__attribute__ ((warn_unused_result));


static const NihDBusArg my_com_netsplit_Nih_Test_OrdinaryMethod_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NamelessMethod_method_args[] = {
	{ NULL,   "s", NIH_DBUS_ARG_IN  },
	{ NULL,   "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_AsyncMethod_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_ByteToStr_method_args[] = {
	{ "input",  "y", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToByte_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "y", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_BooleanToStr_method_args[] = {
	{ "input",  "b", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToBoolean_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "b", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_Int16ToStr_method_args[] = {
	{ "input",  "n", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToInt16_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "n", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_UInt16ToStr_method_args[] = {
	{ "input",  "q", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToUInt16_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "q", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_Int32ToStr_method_args[] = {
	{ "input",  "i", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToInt32_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "i", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_UInt32ToStr_method_args[] = {
	{ "input",  "u", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToUInt32_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "u", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_Int64ToStr_method_args[] = {
	{ "input",  "x", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToInt64_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "x", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_UInt64ToStr_method_args[] = {
	{ "input",  "t", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToUInt64_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "t", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_DoubleToStr_method_args[] = {
	{ "input",  "d", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToDouble_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "d", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_ObjectPathToStr_method_args[] = {
	{ "input",  "o", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToObjectPath_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_SignatureToStr_method_args[] = {
	{ "input",  "g", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToSignature_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "g", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StructToStr_method_args[] = {
	{ "input",  "(su)", NIH_DBUS_ARG_IN  },
	{ "output", "s",    NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToStruct_method_args[] = {
	{ "input",  "s",    NIH_DBUS_ARG_IN  },
	{ "output", "(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_Int32ArrayToStr_method_args[] = {
	{ "input",  "ai", NIH_DBUS_ARG_IN  },
	{ "output", "s",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToInt32Array_method_args[] = {
	{ "input",  "s",  NIH_DBUS_ARG_IN  },
	{ "output", "ai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrArrayToStr_method_args[] = {
	{ "input",  "as", NIH_DBUS_ARG_IN  },
	{ "output", "s",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToStrArray_method_args[] = {
	{ "input",  "s",  NIH_DBUS_ARG_IN  },
	{ "output", "as", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method_args[] = {
	{ "input",  "aai", NIH_DBUS_ARG_IN  },
	{ "output", "s",   NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToInt32ArrayArray_method_args[] = {
	{ "input",  "s",   NIH_DBUS_ARG_IN  },
	{ "output", "aai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StructArrayToStr_method_args[] = {
	{ "input",  "a(su)", NIH_DBUS_ARG_IN  },
	{ "output", "s",     NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToStructArray_method_args[] = {
	{ "input",  "s",     NIH_DBUS_ARG_IN  },
	{ "output", "a(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_DictEntryArrayToStr_method_args[] = {
	{ "input",  "a{su}", NIH_DBUS_ARG_IN  },
	{ "output", "s",     NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToDictEntryArray_method_args[] = {
	{ "input",  "s",     NIH_DBUS_ARG_IN  },
	{ "output", "a{su}", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_UnixFdToStr_method_args[] = {
	{ "input",  "h", NIH_DBUS_ARG_IN  },
	{ "output", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_StrToUnixFd_method_args[] = {
	{ "input",  "s", NIH_DBUS_ARG_IN  },
	{ "output", "h", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusMethod my_com_netsplit_Nih_Test_methods[] = {
	{ "OrdinaryMethod",       my_com_netsplit_Nih_Test_OrdinaryMethod_method_args,       my_com_netsplit_Nih_Test_OrdinaryMethod_method       },
	{ "NamelessMethod",       my_com_netsplit_Nih_Test_NamelessMethod_method_args,       my_com_netsplit_Nih_Test_NamelessMethod_method       },
	{ "AsyncMethod",          my_com_netsplit_Nih_Test_AsyncMethod_method_args,          my_com_netsplit_Nih_Test_AsyncMethod_method          },
	{ "ByteToStr",            my_com_netsplit_Nih_Test_ByteToStr_method_args,            my_com_netsplit_Nih_Test_ByteToStr_method            },
	{ "StrToByte",            my_com_netsplit_Nih_Test_StrToByte_method_args,            my_com_netsplit_Nih_Test_StrToByte_method            },
	{ "BooleanToStr",         my_com_netsplit_Nih_Test_BooleanToStr_method_args,         my_com_netsplit_Nih_Test_BooleanToStr_method         },
	{ "StrToBoolean",         my_com_netsplit_Nih_Test_StrToBoolean_method_args,         my_com_netsplit_Nih_Test_StrToBoolean_method         },
	{ "Int16ToStr",           my_com_netsplit_Nih_Test_Int16ToStr_method_args,           my_com_netsplit_Nih_Test_Int16ToStr_method           },
	{ "StrToInt16",           my_com_netsplit_Nih_Test_StrToInt16_method_args,           my_com_netsplit_Nih_Test_StrToInt16_method           },
	{ "UInt16ToStr",          my_com_netsplit_Nih_Test_UInt16ToStr_method_args,          my_com_netsplit_Nih_Test_UInt16ToStr_method          },
	{ "StrToUInt16",          my_com_netsplit_Nih_Test_StrToUInt16_method_args,          my_com_netsplit_Nih_Test_StrToUInt16_method          },
	{ "Int32ToStr",           my_com_netsplit_Nih_Test_Int32ToStr_method_args,           my_com_netsplit_Nih_Test_Int32ToStr_method           },
	{ "StrToInt32",           my_com_netsplit_Nih_Test_StrToInt32_method_args,           my_com_netsplit_Nih_Test_StrToInt32_method           },
	{ "UInt32ToStr",          my_com_netsplit_Nih_Test_UInt32ToStr_method_args,          my_com_netsplit_Nih_Test_UInt32ToStr_method          },
	{ "StrToUInt32",          my_com_netsplit_Nih_Test_StrToUInt32_method_args,          my_com_netsplit_Nih_Test_StrToUInt32_method          },
	{ "Int64ToStr",           my_com_netsplit_Nih_Test_Int64ToStr_method_args,           my_com_netsplit_Nih_Test_Int64ToStr_method           },
	{ "StrToInt64",           my_com_netsplit_Nih_Test_StrToInt64_method_args,           my_com_netsplit_Nih_Test_StrToInt64_method           },
	{ "UInt64ToStr",          my_com_netsplit_Nih_Test_UInt64ToStr_method_args,          my_com_netsplit_Nih_Test_UInt64ToStr_method          },
	{ "StrToUInt64",          my_com_netsplit_Nih_Test_StrToUInt64_method_args,          my_com_netsplit_Nih_Test_StrToUInt64_method          },
	{ "DoubleToStr",          my_com_netsplit_Nih_Test_DoubleToStr_method_args,          my_com_netsplit_Nih_Test_DoubleToStr_method          },
	{ "StrToDouble",          my_com_netsplit_Nih_Test_StrToDouble_method_args,          my_com_netsplit_Nih_Test_StrToDouble_method          },
	{ "ObjectPathToStr",      my_com_netsplit_Nih_Test_ObjectPathToStr_method_args,      my_com_netsplit_Nih_Test_ObjectPathToStr_method      },
	{ "StrToObjectPath",      my_com_netsplit_Nih_Test_StrToObjectPath_method_args,      my_com_netsplit_Nih_Test_StrToObjectPath_method      },
	{ "SignatureToStr",       my_com_netsplit_Nih_Test_SignatureToStr_method_args,       my_com_netsplit_Nih_Test_SignatureToStr_method       },
	{ "StrToSignature",       my_com_netsplit_Nih_Test_StrToSignature_method_args,       my_com_netsplit_Nih_Test_StrToSignature_method       },
	{ "StructToStr",          my_com_netsplit_Nih_Test_StructToStr_method_args,          my_com_netsplit_Nih_Test_StructToStr_method          },
	{ "StrToStruct",          my_com_netsplit_Nih_Test_StrToStruct_method_args,          my_com_netsplit_Nih_Test_StrToStruct_method          },
	{ "Int32ArrayToStr",      my_com_netsplit_Nih_Test_Int32ArrayToStr_method_args,      my_com_netsplit_Nih_Test_Int32ArrayToStr_method      },
	{ "StrToInt32Array",      my_com_netsplit_Nih_Test_StrToInt32Array_method_args,      my_com_netsplit_Nih_Test_StrToInt32Array_method      },
	{ "StrArrayToStr",        my_com_netsplit_Nih_Test_StrArrayToStr_method_args,        my_com_netsplit_Nih_Test_StrArrayToStr_method        },
	{ "StrToStrArray",        my_com_netsplit_Nih_Test_StrToStrArray_method_args,        my_com_netsplit_Nih_Test_StrToStrArray_method        },
	{ "Int32ArrayArrayToStr", my_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method_args, my_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method },
	{ "StrToInt32ArrayArray", my_com_netsplit_Nih_Test_StrToInt32ArrayArray_method_args, my_com_netsplit_Nih_Test_StrToInt32ArrayArray_method },
	{ "StructArrayToStr",     my_com_netsplit_Nih_Test_StructArrayToStr_method_args,     my_com_netsplit_Nih_Test_StructArrayToStr_method     },
	{ "StrToStructArray",     my_com_netsplit_Nih_Test_StrToStructArray_method_args,     my_com_netsplit_Nih_Test_StrToStructArray_method     },
	{ "DictEntryArrayToStr",  my_com_netsplit_Nih_Test_DictEntryArrayToStr_method_args,  my_com_netsplit_Nih_Test_DictEntryArrayToStr_method  },
	{ "StrToDictEntryArray",  my_com_netsplit_Nih_Test_StrToDictEntryArray_method_args,  my_com_netsplit_Nih_Test_StrToDictEntryArray_method  },
	{ "UnixFdToStr",          my_com_netsplit_Nih_Test_UnixFdToStr_method_args,          my_com_netsplit_Nih_Test_UnixFdToStr_method          },
	{ "StrToUnixFd",          my_com_netsplit_Nih_Test_StrToUnixFd_method_args,          my_com_netsplit_Nih_Test_StrToUnixFd_method          },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewByte_signal_args[] = {
	{ "value", "y", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewBoolean_signal_args[] = {
	{ "value", "b", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewInt16_signal_args[] = {
	{ "value", "n", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewUInt16_signal_args[] = {
	{ "value", "q", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewInt32_signal_args[] = {
	{ "value", "i", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewUInt32_signal_args[] = {
	{ "value", "u", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewInt64_signal_args[] = {
	{ "value", "x", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewUInt64_signal_args[] = {
	{ "value", "t", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewDouble_signal_args[] = {
	{ "value", "d", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewString_signal_args[] = {
	{ "value", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewObjectPath_signal_args[] = {
	{ "value", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewSignature_signal_args[] = {
	{ "value", "g", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewStruct_signal_args[] = {
	{ "value", "(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewInt32Array_signal_args[] = {
	{ "value", "ai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewStrArray_signal_args[] = {
	{ "value", "as", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewInt32ArrayArray_signal_args[] = {
	{ "value", "aai", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewStructArray_signal_args[] = {
	{ "value", "a(su)", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewDictEntryArray_signal_args[] = {
	{ "value", "a{su}", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg my_com_netsplit_Nih_Test_NewUnixFd_signal_args[] = {
	{ "value", "h", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusSignal my_com_netsplit_Nih_Test_signals[] = {
	{ "NewByte",            my_com_netsplit_Nih_Test_NewByte_signal_args,            NULL },
	{ "NewBoolean",         my_com_netsplit_Nih_Test_NewBoolean_signal_args,         NULL },
	{ "NewInt16",           my_com_netsplit_Nih_Test_NewInt16_signal_args,           NULL },
	{ "NewUInt16",          my_com_netsplit_Nih_Test_NewUInt16_signal_args,          NULL },
	{ "NewInt32",           my_com_netsplit_Nih_Test_NewInt32_signal_args,           NULL },
	{ "NewUInt32",          my_com_netsplit_Nih_Test_NewUInt32_signal_args,          NULL },
	{ "NewInt64",           my_com_netsplit_Nih_Test_NewInt64_signal_args,           NULL },
	{ "NewUInt64",          my_com_netsplit_Nih_Test_NewUInt64_signal_args,          NULL },
	{ "NewDouble",          my_com_netsplit_Nih_Test_NewDouble_signal_args,          NULL },
	{ "NewString",          my_com_netsplit_Nih_Test_NewString_signal_args,          NULL },
	{ "NewObjectPath",      my_com_netsplit_Nih_Test_NewObjectPath_signal_args,      NULL },
	{ "NewSignature",       my_com_netsplit_Nih_Test_NewSignature_signal_args,       NULL },
	{ "NewStruct",          my_com_netsplit_Nih_Test_NewStruct_signal_args,          NULL },
	{ "NewInt32Array",      my_com_netsplit_Nih_Test_NewInt32Array_signal_args,      NULL },
	{ "NewStrArray",        my_com_netsplit_Nih_Test_NewStrArray_signal_args,        NULL },
	{ "NewInt32ArrayArray", my_com_netsplit_Nih_Test_NewInt32ArrayArray_signal_args, NULL },
	{ "NewStructArray",     my_com_netsplit_Nih_Test_NewStructArray_signal_args,     NULL },
	{ "NewDictEntryArray",  my_com_netsplit_Nih_Test_NewDictEntryArray_signal_args,  NULL },
	{ "NewUnixFd",          my_com_netsplit_Nih_Test_NewUnixFd_signal_args,          NULL },
	{ NULL }
};

static const NihDBusProperty my_com_netsplit_Nih_Test_properties[] = {
	{ "byte",              "y",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_byte_get,              my_com_netsplit_Nih_Test_byte_set              },
	{ "boolean",           "b",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_boolean_get,           my_com_netsplit_Nih_Test_boolean_set           },
	{ "int16",             "n",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_int16_get,             my_com_netsplit_Nih_Test_int16_set             },
	{ "uint16",            "q",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_uint16_get,            my_com_netsplit_Nih_Test_uint16_set            },
	{ "int32",             "i",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_int32_get,             my_com_netsplit_Nih_Test_int32_set             },
	{ "uint32",            "u",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_uint32_get,            my_com_netsplit_Nih_Test_uint32_set            },
	{ "int64",             "x",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_int64_get,             my_com_netsplit_Nih_Test_int64_set             },
	{ "uint64",            "t",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_uint64_get,            my_com_netsplit_Nih_Test_uint64_set            },
	{ "double",            "d",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_double_get,            my_com_netsplit_Nih_Test_double_set            },
	{ "string",            "s",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_string_get,            my_com_netsplit_Nih_Test_string_set            },
	{ "object_path",       "o",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_object_path_get,       my_com_netsplit_Nih_Test_object_path_set       },
	{ "signature",         "g",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_signature_get,         my_com_netsplit_Nih_Test_signature_set         },
	{ "structure",         "(su)",  NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_structure_get,         my_com_netsplit_Nih_Test_structure_set         },
	{ "int32_array",       "ai",    NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_int32_array_get,       my_com_netsplit_Nih_Test_int32_array_set       },
	{ "str_array",         "as",    NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_str_array_get,         my_com_netsplit_Nih_Test_str_array_set         },
	{ "int32_array_array", "aai",   NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_int32_array_array_get, my_com_netsplit_Nih_Test_int32_array_array_set },
	{ "struct_array",      "a(su)", NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_struct_array_get,      my_com_netsplit_Nih_Test_struct_array_set      },
	{ "dict_entry_array",  "a{su}", NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_dict_entry_array_get,  my_com_netsplit_Nih_Test_dict_entry_array_set  },
	{ "unix_fd",           "h",     NIH_DBUS_READWRITE, my_com_netsplit_Nih_Test_unix_fd_get,           my_com_netsplit_Nih_Test_unix_fd_set           },
	{ NULL }
};

const NihDBusInterface my_com_netsplit_Nih_Test = {
	"com.netsplit.Nih.Test",
	my_com_netsplit_Nih_Test_methods,
	my_com_netsplit_Nih_Test_signals,
	my_com_netsplit_Nih_Test_properties
};

const NihDBusInterface *my_interfaces[] = {
	&my_com_netsplit_Nih_Test,
	NULL
};


static DBusHandlerResult
my_com_netsplit_Nih_Test_OrdinaryMethod_method (NihDBusObject * object,
                                                NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to OrdinaryMethod method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to OrdinaryMethod method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_ordinary_method (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_NamelessMethod_method (NihDBusObject * object,
                                                NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          arg1;
	const char *    arg1_dbus;
	char *          arg2;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to NamelessMethod method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &arg1_dbus);

	arg1 = nih_strdup (message, arg1_dbus);
	if (! arg1) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to NamelessMethod method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_nameless_method (object->data, message, arg1, &arg2) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &arg2)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_AsyncMethod_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to AsyncMethod method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to AsyncMethod method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_async_method (object->data, message, input) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	return DBUS_HANDLER_RESULT_HANDLED;
}

int
my_test_async_method_reply (NihDBusMessage *message,
                            const char *    output)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);
	nih_assert (output != NULL);

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return 0;

	/* Construct the reply message. */
	reply = dbus_message_new_method_return (message->message);
	if (! reply)
		return -1;

	dbus_message_iter_init_append (reply, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
		dbus_message_unref (reply);
		return -1;
	}

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_ByteToStr_method (NihDBusObject * object,
                                           NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	uint8_t         input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint8_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BYTE) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ByteToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ByteToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_byte_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToByte_method (NihDBusObject * object,
                                           NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	uint8_t         output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToByte method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToByte method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_byte (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a uint8_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BYTE, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_BooleanToStr_method (NihDBusObject * object,
                                              NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int             input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to BooleanToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to BooleanToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_boolean_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToBoolean_method (NihDBusObject * object,
                                              NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int             output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToBoolean method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToBoolean method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_boolean (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a int onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_Int16ToStr_method (NihDBusObject * object,
                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int16_t         input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int16_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT16) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int16ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int16ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_int16_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToInt16_method (NihDBusObject * object,
                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int16_t         output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt16 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt16 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_int16 (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a int16_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT16, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_UInt16ToStr_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	uint16_t        input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint16_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT16) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UInt16ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UInt16ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_uint16_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToUInt16_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	uint16_t        output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUInt16 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUInt16 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_uint16 (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a uint16_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT16, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_Int32ToStr_method (NihDBusObject * object,
                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int32_t         input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int32_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT32) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int32ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int32ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_int32_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToInt32_method (NihDBusObject * object,
                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int32_t         output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt32 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt32 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_int32 (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_UInt32ToStr_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	uint32_t        input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint32_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT32) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UInt32ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UInt32ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_uint32_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToUInt32_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	uint32_t        output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUInt32 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUInt32 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_uint32 (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a uint32_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT32, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_Int64ToStr_method (NihDBusObject * object,
                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int64_t         input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int64_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INT64) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int64ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int64ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_int64_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToInt64_method (NihDBusObject * object,
                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int64_t         output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt64 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt64 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_int64 (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a int64_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT64, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_UInt64ToStr_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	uint64_t        input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a uint64_t from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UINT64) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UInt64ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UInt64ToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_uint64_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToUInt64_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	uint64_t        output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUInt64 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUInt64 method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_uint64 (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a uint64_t onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT64, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_DoubleToStr_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	double          input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a double from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_DOUBLE) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to DoubleToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to DoubleToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_double_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToDouble_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	double          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToDouble method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToDouble method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_double (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a double onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_DOUBLE, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_ObjectPathToStr_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ObjectPathToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ObjectPathToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_object_path_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToObjectPath_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToObjectPath method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToObjectPath method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_object_path (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_SignatureToStr_method (NihDBusObject * object,
                                                NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_SIGNATURE) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SignatureToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SignatureToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_signature_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToSignature_method (NihDBusObject * object,
                                                NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToSignature method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToSignature method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_signature (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_SIGNATURE, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StructToStr_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter         iter;
	DBusMessage *           reply;
	MyTestStructToStrInput *input;
	DBusMessageIter         input_iter;
	const char *            input_item0_dbus;
	char *                  input_item0;
	uint32_t                input_item1;
	char *                  output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a structure from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRUCT) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &input_iter);

	input = nih_new (message, MyTestStructToStrInput);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_STRING) {
		nih_free (input);
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&input_iter, &input_item0_dbus);

	input_item0 = nih_strdup (input, input_item0_dbus);
	if (! input_item0) {
		nih_free (input);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&input_iter);

	input->item0 = input_item0;

	/* Demarshal a uint32_t from the message */
	if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_UINT32) {
		nih_free (input);
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&input_iter, &input_item1);

	dbus_message_iter_next (&input_iter);

	input->item1 = input_item1;

	if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INVALID) {
		nih_free (input);
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_struct_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToStruct_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter          iter;
	DBusMessage *            reply;
	char *                   input;
	const char *             input_dbus;
	MyTestStrToStructOutput *output;
	DBusMessageIter          output_iter;
	const char *             output_item0;
	uint32_t                 output_item1;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToStruct method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToStruct method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_struct (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a structure onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_STRUCT, NULL, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		output_item0 = output->item0;

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&output_iter, DBUS_TYPE_STRING, &output_item0)) {
			dbus_message_iter_abandon_container (&iter, &output_iter);
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		output_item1 = output->item1;

		/* Marshal a uint32_t onto the message */
		if (! dbus_message_iter_append_basic (&output_iter, DBUS_TYPE_UINT32, &output_item1)) {
			dbus_message_iter_abandon_container (&iter, &output_iter);
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (! dbus_message_iter_close_container (&iter, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_Int32ArrayToStr_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int32_t *       input;
	size_t          input_len;
	DBusMessageIter input_iter;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int32ArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &input_iter);

	input_len = 0;
	input = NULL;

	while (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INVALID) {
		int32_t *input_tmp;
		int32_t  input_element;

		/* Demarshal a int32_t from the message */
		if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INT32) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to Int32ArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&input_iter, &input_element);

		dbus_message_iter_next (&input_iter);

		if (input_len + 1 > SIZE_MAX / sizeof (int32_t)) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to Int32ArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		input_tmp = nih_realloc (input, message, sizeof (int32_t) * (input_len + 1));
		if (! input_tmp) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		input = input_tmp;
		input[input_len] = input_element;

		input_len++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int32ArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_int32_array_to_str (object->data, message, input, input_len, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToInt32Array_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int32_t *       output;
	size_t          output_len;
	DBusMessageIter output_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt32Array method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt32Array method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_int32_array (object->data, message, input, &output, &output_len) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "i", &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		for (size_t output_i = 0; output_i < output_len; output_i++) {
			int32_t output_element;

			output_element = output[output_i];

			/* Marshal a int32_t onto the message */
			if (! dbus_message_iter_append_basic (&output_iter, DBUS_TYPE_INT32, &output_element)) {
				dbus_message_iter_abandon_container (&iter, &output_iter);
				dbus_message_unref (reply);
				reply = NULL;
				goto enomem;
			}
		}

		if (! dbus_message_iter_close_container (&iter, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrArrayToStr_method (NihDBusObject * object,
                                               NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         input;
	DBusMessageIter input_iter;
	size_t          input_size;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &input_iter);

	input_size = 0;
	input = NULL;

	input = nih_alloc (message, sizeof (char *));
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	input[input_size] = NULL;

	while (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INVALID) {
		const char *input_element_dbus;
		char **     input_tmp;
		char *      input_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_STRING) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StrArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&input_iter, &input_element_dbus);

		input_element = nih_strdup (input, input_element_dbus);
		if (! input_element) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&input_iter);

		if (input_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StrArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		input_tmp = nih_realloc (input, message, sizeof (char *) * (input_size + 2));
		if (! input_tmp) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		input = input_tmp;
		input[input_size] = input_element;
		input[input_size + 1] = NULL;

		input_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_array_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToStrArray_method (NihDBusObject * object,
                                               NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	char **         output;
	DBusMessageIter output_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToStrArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToStrArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_str_array (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (output) {
			for (size_t output_i = 0; output[output_i]; output_i++) {
				const char *output_element;

				output_element = output[output_i];

				/* Marshal a char * onto the message */
				if (! dbus_message_iter_append_basic (&output_iter, DBUS_TYPE_STRING, &output_element)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_Int32ArrayArrayToStr_method (NihDBusObject * object,
                                                      NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int32_t **      input;
	size_t *        input_len;
	DBusMessageIter input_iter;
	size_t          input_size;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int32ArrayArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &input_iter);

	input_size = 0;
	input = NULL;
	input_len = NULL;

	input = nih_alloc (message, sizeof (int32_t *));
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	input[input_size] = NULL;

	while (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter input_element_iter;
		int32_t **      input_tmp;
		int32_t *       input_element;
		size_t *        input_len_tmp;
		size_t          input_element_len;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_ARRAY) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to Int32ArrayArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_recurse (&input_iter, &input_element_iter);

		input_element_len = 0;
		input_element = NULL;

		while (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_INVALID) {
			int32_t *input_element_tmp;
			int32_t  input_element_element;

			/* Demarshal a int32_t from the message */
			if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_INT32) {
				if (input_element)
					nih_free (input_element);
				if (input)
					nih_free (input);
				reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
				                                "Invalid arguments to Int32ArrayArrayToStr method");
				if (! reply)
					return DBUS_HANDLER_RESULT_NEED_MEMORY;

				if (! dbus_connection_send (message->connection, reply, NULL)) {
					dbus_message_unref (reply);
					return DBUS_HANDLER_RESULT_NEED_MEMORY;
				}

				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_HANDLED;
			}

			dbus_message_iter_get_basic (&input_element_iter, &input_element_element);

			dbus_message_iter_next (&input_element_iter);

			if (input_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (input_element)
					nih_free (input_element);
				if (input)
					nih_free (input);
				reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
				                                "Invalid arguments to Int32ArrayArrayToStr method");
				if (! reply)
					return DBUS_HANDLER_RESULT_NEED_MEMORY;

				if (! dbus_connection_send (message->connection, reply, NULL)) {
					dbus_message_unref (reply);
					return DBUS_HANDLER_RESULT_NEED_MEMORY;
				}

				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_HANDLED;
			}

			input_element_tmp = nih_realloc (input_element, input, sizeof (int32_t) * (input_element_len + 1));
			if (! input_element_tmp) {
				if (input_element)
					nih_free (input_element);
				if (input)
					nih_free (input);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			input_element = input_element_tmp;
			input_element[input_element_len] = input_element_element;

			input_element_len++;
		}

		dbus_message_iter_next (&input_iter);

		if (input_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to Int32ArrayArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		input_tmp = nih_realloc (input, message, sizeof (int32_t *) * (input_size + 2));
		if (! input_tmp) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		input = input_tmp;
		input[input_size] = input_element;
		input[input_size + 1] = NULL;

		if (input_size + 1 > SIZE_MAX / sizeof (size_t)) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to Int32ArrayArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		input_len_tmp = nih_realloc (input_len, input, sizeof (size_t) * (input_size + 1));
		if (! input_len_tmp) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		input_len = input_len_tmp;
		input_len[input_size] = input_element_len;

		input_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Int32ArrayArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_int32_array_array_to_str (object->data, message, input, input_len, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToInt32ArrayArray_method (NihDBusObject * object,
                                                      NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int32_t **      output;
	size_t *        output_len;
	DBusMessageIter output_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt32ArrayArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToInt32ArrayArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_int32_array_array (object->data, message, input, &output, &output_len) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "ai", &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (output) {
			for (size_t output_i = 0; output[output_i]; output_i++) {
				DBusMessageIter output_element_iter;
				const int32_t * output_element;
				size_t          output_element_len;

				output_element = output[output_i];
				output_element_len = output_len[output_i];

				/* Marshal an array onto the message */
				if (! dbus_message_iter_open_container (&output_iter, DBUS_TYPE_ARRAY, "i", &output_element_iter)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				for (size_t output_element_i = 0; output_element_i < output_element_len; output_element_i++) {
					int32_t output_element_element;

					output_element_element = output_element[output_element_i];

					/* Marshal a int32_t onto the message */
					if (! dbus_message_iter_append_basic (&output_element_iter, DBUS_TYPE_INT32, &output_element_element)) {
						dbus_message_iter_abandon_container (&output_iter, &output_element_iter);
						dbus_message_iter_abandon_container (&iter, &output_iter);
						dbus_message_unref (reply);
						reply = NULL;
						goto enomem;
					}
				}

				if (! dbus_message_iter_close_container (&output_iter, &output_element_iter)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StructArrayToStr_method (NihDBusObject * object,
                                                  NihDBusMessage *message)
{
	DBusMessageIter                      iter;
	DBusMessage *                        reply;
	MyTestStructArrayToStrInputElement **input;
	DBusMessageIter                      input_iter;
	size_t                               input_size;
	char *                               output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &input_iter);

	input_size = 0;
	input = NULL;

	input = nih_alloc (message, sizeof (MyTestStructArrayToStrInputElement *));
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	input[input_size] = NULL;

	while (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter                      input_element_iter;
		const char *                         input_element_item0_dbus;
		char *                               input_element_item0;
		uint32_t                             input_element_item1;
		MyTestStructArrayToStrInputElement **input_tmp;
		MyTestStructArrayToStrInputElement * input_element;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_STRUCT) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StructArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_recurse (&input_iter, &input_element_iter);

		input_element = nih_new (input, MyTestStructArrayToStrInputElement);
		if (! input_element) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_STRING) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StructArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&input_element_iter, &input_element_item0_dbus);

		input_element_item0 = nih_strdup (input_element, input_element_item0_dbus);
		if (! input_element_item0) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&input_element_iter);

		input_element->item0 = input_element_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_UINT32) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StructArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&input_element_iter, &input_element_item1);

		dbus_message_iter_next (&input_element_iter);

		input_element->item1 = input_element_item1;

		if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_INVALID) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StructArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_next (&input_iter);

		if (input_size + 2 > SIZE_MAX / sizeof (MyTestStructArrayToStrInputElement *)) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to StructArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		input_tmp = nih_realloc (input, message, sizeof (MyTestStructArrayToStrInputElement *) * (input_size + 2));
		if (! input_tmp) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		input = input_tmp;
		input[input_size] = input_element;
		input[input_size + 1] = NULL;

		input_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StructArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_struct_array_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToStructArray_method (NihDBusObject * object,
                                                  NihDBusMessage *message)
{
	DBusMessageIter                       iter;
	DBusMessage *                         reply;
	char *                                input;
	const char *                          input_dbus;
	MyTestStrToStructArrayOutputElement **output;
	DBusMessageIter                       output_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToStructArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToStructArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_struct_array (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "(su)", &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (output) {
			for (size_t output_i = 0; output[output_i]; output_i++) {
				DBusMessageIter                            output_element_iter;
				const char *                               output_element_item0;
				uint32_t                                   output_element_item1;
				const MyTestStrToStructArrayOutputElement *output_element;

				output_element = output[output_i];

				/* Marshal a structure onto the message */
				if (! dbus_message_iter_open_container (&output_iter, DBUS_TYPE_STRUCT, NULL, &output_element_iter)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				output_element_item0 = output_element->item0;

				/* Marshal a char * onto the message */
				if (! dbus_message_iter_append_basic (&output_element_iter, DBUS_TYPE_STRING, &output_element_item0)) {
					dbus_message_iter_abandon_container (&output_iter, &output_element_iter);
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				output_element_item1 = output_element->item1;

				/* Marshal a uint32_t onto the message */
				if (! dbus_message_iter_append_basic (&output_element_iter, DBUS_TYPE_UINT32, &output_element_item1)) {
					dbus_message_iter_abandon_container (&output_iter, &output_element_iter);
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				if (! dbus_message_iter_close_container (&output_iter, &output_element_iter)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_DictEntryArrayToStr_method (NihDBusObject * object,
                                                     NihDBusMessage *message)
{
	DBusMessageIter                         iter;
	DBusMessage *                           reply;
	MyTestDictEntryArrayToStrInputElement **input;
	DBusMessageIter                         input_iter;
	size_t                                  input_size;
	char *                                  output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to DictEntryArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &input_iter);

	input_size = 0;
	input = NULL;

	input = nih_alloc (message, sizeof (MyTestDictEntryArrayToStrInputElement *));
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	input[input_size] = NULL;

	while (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter                         input_element_iter;
		const char *                            input_element_item0_dbus;
		char *                                  input_element_item0;
		uint32_t                                input_element_item1;
		MyTestDictEntryArrayToStrInputElement **input_tmp;
		MyTestDictEntryArrayToStrInputElement * input_element;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&input_iter) != DBUS_TYPE_DICT_ENTRY) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to DictEntryArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_recurse (&input_iter, &input_element_iter);

		input_element = nih_new (input, MyTestDictEntryArrayToStrInputElement);
		if (! input_element) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_STRING) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to DictEntryArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&input_element_iter, &input_element_item0_dbus);

		input_element_item0 = nih_strdup (input_element, input_element_item0_dbus);
		if (! input_element_item0) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&input_element_iter);

		input_element->item0 = input_element_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_UINT32) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to DictEntryArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&input_element_iter, &input_element_item1);

		dbus_message_iter_next (&input_element_iter);

		input_element->item1 = input_element_item1;

		if (dbus_message_iter_get_arg_type (&input_element_iter) != DBUS_TYPE_INVALID) {
			nih_free (input_element);
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to DictEntryArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_next (&input_iter);

		if (input_size + 2 > SIZE_MAX / sizeof (MyTestDictEntryArrayToStrInputElement *)) {
			if (input)
				nih_free (input);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to DictEntryArrayToStr method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		input_tmp = nih_realloc (input, message, sizeof (MyTestDictEntryArrayToStrInputElement *) * (input_size + 2));
		if (! input_tmp) {
			if (input)
				nih_free (input);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		input = input_tmp;
		input[input_size] = input_element;
		input[input_size + 1] = NULL;

		input_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to DictEntryArrayToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_dict_entry_array_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToDictEntryArray_method (NihDBusObject * object,
                                                     NihDBusMessage *message)
{
	DBusMessageIter                          iter;
	DBusMessage *                            reply;
	char *                                   input;
	const char *                             input_dbus;
	MyTestStrToDictEntryArrayOutputElement **output;
	DBusMessageIter                          output_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToDictEntryArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToDictEntryArray method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_dict_entry_array (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "{su}", &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (output) {
			for (size_t output_i = 0; output[output_i]; output_i++) {
				DBusMessageIter                               output_element_iter;
				const char *                                  output_element_item0;
				uint32_t                                      output_element_item1;
				const MyTestStrToDictEntryArrayOutputElement *output_element;

				output_element = output[output_i];

				/* Marshal a structure onto the message */
				if (! dbus_message_iter_open_container (&output_iter, DBUS_TYPE_DICT_ENTRY, NULL, &output_element_iter)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				output_element_item0 = output_element->item0;

				/* Marshal a char * onto the message */
				if (! dbus_message_iter_append_basic (&output_element_iter, DBUS_TYPE_STRING, &output_element_item0)) {
					dbus_message_iter_abandon_container (&output_iter, &output_element_iter);
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				output_element_item1 = output_element->item1;

				/* Marshal a uint32_t onto the message */
				if (! dbus_message_iter_append_basic (&output_element_iter, DBUS_TYPE_UINT32, &output_element_item1)) {
					dbus_message_iter_abandon_container (&output_iter, &output_element_iter);
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}

				if (! dbus_message_iter_close_container (&output_iter, &output_element_iter)) {
					dbus_message_iter_abandon_container (&iter, &output_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &output_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_UnixFdToStr_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int             input;
	char *          output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UNIX_FD) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnixFdToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnixFdToStr method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_unix_fd_to_str (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
my_com_netsplit_Nih_Test_StrToUnixFd_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          input;
	const char *    input_dbus;
	int             output;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUnixFd method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &input_dbus);

	input = nih_strdup (message, input_dbus);
	if (! input) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to StrToUnixFd method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (my_test_str_to_unix_fd (object->data, message, input, &output) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a int onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UNIX_FD, &output)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


int
my_test_emit_new_byte (DBusConnection *connection,
                       const char *    origin_path,
                       uint8_t         value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewByte");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a uint8_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BYTE, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_boolean (DBusConnection *connection,
                          const char *    origin_path,
                          int             value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewBoolean");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_int16 (DBusConnection *connection,
                        const char *    origin_path,
                        int16_t         value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewInt16");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a int16_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT16, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_uint16 (DBusConnection *connection,
                         const char *    origin_path,
                         uint16_t        value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewUInt16");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a uint16_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT16, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_int32 (DBusConnection *connection,
                        const char *    origin_path,
                        int32_t         value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewInt32");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_uint32 (DBusConnection *connection,
                         const char *    origin_path,
                         uint32_t        value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewUInt32");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT32, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_int64 (DBusConnection *connection,
                        const char *    origin_path,
                        int64_t         value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewInt64");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a int64_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT64, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_uint64 (DBusConnection *connection,
                         const char *    origin_path,
                         uint64_t        value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewUInt64");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a uint64_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT64, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_double (DBusConnection *connection,
                         const char *    origin_path,
                         double          value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewDouble");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a double onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_DOUBLE, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_string (DBusConnection *connection,
                         const char *    origin_path,
                         const char *    value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewString");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_object_path (DBusConnection *connection,
                              const char *    origin_path,
                              const char *    value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewObjectPath");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_signature (DBusConnection *connection,
                            const char *    origin_path,
                            const char *    value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewSignature");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_SIGNATURE, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_struct (DBusConnection *            connection,
                         const char *                origin_path,
                         const MyTestNewStructValue *value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter value_iter;
	const char *    value_item0;
	uint32_t        value_item1;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewStruct");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a structure onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_STRUCT, NULL, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	value_item0 = value->item0;

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_item0)) {
		dbus_message_iter_abandon_container (&iter, &value_iter);
		dbus_message_unref (signal);
		return -1;
	}

	value_item1 = value->item1;

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_UINT32, &value_item1)) {
		dbus_message_iter_abandon_container (&iter, &value_iter);
		dbus_message_unref (signal);
		return -1;
	}

	if (! dbus_message_iter_close_container (&iter, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_int32_array (DBusConnection *connection,
                              const char *    origin_path,
                              const int32_t * value,
                              size_t          value_len)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter value_iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert ((value_len == 0) || (value != NULL));

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewInt32Array");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "i", &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	for (size_t value_i = 0; value_i < value_len; value_i++) {
		int32_t value_element;

		value_element = value[value_i];

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_INT32, &value_element)) {
			dbus_message_iter_abandon_container (&iter, &value_iter);
			dbus_message_unref (signal);
			return -1;
		}
	}

	if (! dbus_message_iter_close_container (&iter, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_str_array (DBusConnection *connection,
                            const char *    origin_path,
                            char * const *  value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter value_iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewStrArray");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			const char *value_element;

			value_element = value[value_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_element)) {
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_int32_array_array (DBusConnection * connection,
                                    const char *     origin_path,
                                    int32_t * const *value,
                                    const size_t *   value_len)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter value_iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);
	nih_assert ((*value == NULL) || (value_len != NULL));

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewInt32ArrayArray");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "ai", &value_iter)) {
		dbus_message_unref (signal);
		return -1;
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
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			for (size_t value_element_i = 0; value_element_i < value_element_len; value_element_i++) {
				int32_t value_element_element;

				value_element_element = value_element[value_element_i];

				/* Marshal a int32_t onto the message */
				if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_INT32, &value_element_element)) {
					dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
					dbus_message_iter_abandon_container (&iter, &value_iter);
					dbus_message_unref (signal);
					return -1;
				}
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_struct_array (DBusConnection *                          connection,
                               const char *                              origin_path,
                               MyTestNewStructArrayValueElement * const *value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter value_iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewStructArray");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "(su)", &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                         value_element_iter;
			const char *                            value_element_item0;
			uint32_t                                value_element_item1;
			const MyTestNewStructArrayValueElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_STRUCT, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_dict_entry_array (DBusConnection *                             connection,
                                   const char *                                 origin_path,
                                   MyTestNewDictEntryArrayValueElement * const *value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter value_iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (value != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewDictEntryArray");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "{su}", &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                            value_element_iter;
			const char *                               value_element_item0;
			uint32_t                                   value_element_item1;
			const MyTestNewDictEntryArrayValueElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_DICT_ENTRY, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&iter, &value_iter);
				dbus_message_unref (signal);
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &value_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
my_test_emit_new_unix_fd (DBusConnection *connection,
                          const char *    origin_path,
                          int             value)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.netsplit.Nih.Test", "NewUnixFd");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_UNIX_FD, &value)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


static int
my_com_netsplit_Nih_Test_byte_get (NihDBusObject *  object,
                                   NihDBusMessage * message,
                                   DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint8_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_byte (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "y", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a uint8_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_BYTE, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_byte_set (NihDBusObject *  object,
                                   NihDBusMessage * message,
                                   DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint8_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to byte property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a uint8_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BYTE) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to byte property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to byte property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_byte (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_boolean_get (NihDBusObject *  object,
                                      NihDBusMessage * message,
                                      DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int             value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_boolean (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "b", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_BOOLEAN, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_boolean_set (NihDBusObject *  object,
                                      NihDBusMessage * message,
                                      DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int             value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to boolean property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_BOOLEAN) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to boolean property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to boolean property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_boolean (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_int16_get (NihDBusObject *  object,
                                    NihDBusMessage * message,
                                    DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int16_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_int16 (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "n", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a int16_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT16, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_int16_set (NihDBusObject *  object,
                                    NihDBusMessage * message,
                                    DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int16_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int16 property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a int16_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT16) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int16 property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int16 property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_int16 (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_uint16_get (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint16_t        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_uint16 (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "q", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a uint16_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT16, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_uint16_set (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint16_t        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint16 property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a uint16_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT16) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint16 property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint16 property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_uint16 (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_int32_get (NihDBusObject *  object,
                                    NihDBusMessage * message,
                                    DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int32_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_int32 (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "i", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT32, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_int32_set (NihDBusObject *  object,
                                    NihDBusMessage * message,
                                    DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int32_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32 property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a int32_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT32) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32 property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32 property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_int32 (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_uint32_get (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint32_t        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_uint32 (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "u", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT32, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_uint32_set (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint32_t        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint32 property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a uint32_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT32) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint32 property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint32 property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_uint32 (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_int64_get (NihDBusObject *  object,
                                    NihDBusMessage * message,
                                    DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int64_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_int64 (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "x", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a int64_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_INT64, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_int64_set (NihDBusObject *  object,
                                    NihDBusMessage * message,
                                    DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int64_t         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int64 property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a int64_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_INT64) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int64 property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int64 property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_int64 (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_uint64_get (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint64_t        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_uint64 (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "t", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a uint64_t onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UINT64, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_uint64_set (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	uint64_t        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint64 property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a uint64_t from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UINT64) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint64 property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to uint64 property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_uint64 (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_double_get (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	double          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_dubble (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "d", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a double onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_DOUBLE, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_double_set (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	double          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to double property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a double from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_DOUBLE) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to double property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to double property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_dubble (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_string_get (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_string (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "s", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_STRING, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_string_set (NihDBusObject *  object,
                                     NihDBusMessage * message,
                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	const char *    value_dbus;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to string property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to string property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to string property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_string (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_object_path_get (NihDBusObject *  object,
                                          NihDBusMessage * message,
                                          DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_object_path (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "o", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_OBJECT_PATH, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_object_path_set (NihDBusObject *  object,
                                          NihDBusMessage * message,
                                          DBusMessageIter *iter)
{
	DBusMessageIter variter;
	const char *    value_dbus;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to object_path property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_OBJECT_PATH) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to object_path property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to object_path property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_object_path (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_signature_get (NihDBusObject *  object,
                                        NihDBusMessage * message,
                                        DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_signature (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "g", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_SIGNATURE, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_signature_set (NihDBusObject *  object,
                                        NihDBusMessage * message,
                                        DBusMessageIter *iter)
{
	DBusMessageIter variter;
	const char *    value_dbus;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to signature property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_SIGNATURE) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to signature property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to signature property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_signature (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_structure_get (NihDBusObject *  object,
                                        NihDBusMessage * message,
                                        DBusMessageIter *iter)
{
	DBusMessageIter  variter;
	DBusMessageIter  value_iter;
	const char *     value_item0;
	uint32_t         value_item1;
	MyTestStructure *value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_structure (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "(su)", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a structure onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_STRUCT, NULL, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	value_item0 = value->item0;

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_item0)) {
		dbus_message_iter_abandon_container (&variter, &value_iter);
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	value_item1 = value->item1;

	/* Marshal a uint32_t onto the message */
	if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_UINT32, &value_item1)) {
		dbus_message_iter_abandon_container (&variter, &value_iter);
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_structure_set (NihDBusObject *  object,
                                        NihDBusMessage * message,
                                        DBusMessageIter *iter)
{
	DBusMessageIter  variter;
	DBusMessageIter  value_iter;
	const char *     value_item0_dbus;
	char *           value_item0;
	uint32_t         value_item1;
	MyTestStructure *value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to structure property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a structure from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRUCT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to structure property");
		return -1;
	}

	dbus_message_iter_recurse (&variter, &value_iter);

	value = nih_new (message, MyTestStructure);
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRING) {
		nih_free (value);
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to structure property");
		return -1;
	}

	dbus_message_iter_get_basic (&value_iter, &value_item0_dbus);

	value_item0 = nih_strdup (value, value_item0_dbus);
	if (! value_item0) {
		nih_free (value);
		nih_error_raise_no_memory ();
		return -1;
	}

	dbus_message_iter_next (&value_iter);

	value->item0 = value_item0;

	/* Demarshal a uint32_t from the message */
	if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_UINT32) {
		nih_free (value);
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to structure property");
		return -1;
	}

	dbus_message_iter_get_basic (&value_iter, &value_item1);

	dbus_message_iter_next (&value_iter);

	value->item1 = value_item1;

	if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		nih_free (value);
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to structure property");
		return -1;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to structure property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_structure (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_int32_array_get (NihDBusObject *  object,
                                          NihDBusMessage * message,
                                          DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	int32_t *       value;
	size_t          value_len;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_int32_array (object->data, message, &value, &value_len) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "ai", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "i", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	for (size_t value_i = 0; value_i < value_len; value_i++) {
		int32_t value_element;

		value_element = value[value_i];

		/* Marshal a int32_t onto the message */
		if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_INT32, &value_element)) {
			dbus_message_iter_abandon_container (&variter, &value_iter);
			dbus_message_iter_abandon_container (iter, &variter);
			nih_error_raise_no_memory ();
			return -1;
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_int32_array_set (NihDBusObject *  object,
                                          NihDBusMessage * message,
                                          DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	int32_t *       value;
	size_t          value_len;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32_array property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32_array property");
		return -1;
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
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to int32_array property");
			return -1;
		}

		dbus_message_iter_get_basic (&value_iter, &value_element);

		dbus_message_iter_next (&value_iter);

		if (value_len + 1 > SIZE_MAX / sizeof (int32_t)) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to int32_array property");
			return -1;
		}

		value_tmp = nih_realloc (value, message, sizeof (int32_t) * (value_len + 1));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		value = value_tmp;
		value[value_len] = value_element;

		value_len++;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32_array property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_int32_array (object->data, message, value, value_len) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_str_array_get (NihDBusObject *  object,
                                        NihDBusMessage * message,
                                        DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	char **         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_str_array (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "as", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "s", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			const char *value_element;

			value_element = value[value_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_element)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_str_array_set (NihDBusObject *  object,
                                        NihDBusMessage * message,
                                        DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	size_t          value_size;
	char **         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to str_array property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to str_array property");
		return -1;
	}

	dbus_message_iter_recurse (&variter, &value_iter);

	value_size = 0;
	value = NULL;

	value = nih_alloc (message, sizeof (char *));
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
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
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to str_array property");
			return -1;
		}

		dbus_message_iter_get_basic (&value_iter, &value_element_dbus);

		value_element = nih_strdup (value, value_element_dbus);
		if (! value_element) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to str_array property");
			return -1;
		}

		value_tmp = nih_realloc (value, message, sizeof (char *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		value_size++;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to str_array property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_str_array (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_int32_array_array_get (NihDBusObject *  object,
                                                NihDBusMessage * message,
                                                DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	int32_t **      value;
	size_t *        value_len;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_int32_array_array (object->data, message, &value, &value_len) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "aai", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "ai", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
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
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			for (size_t value_element_i = 0; value_element_i < value_element_len; value_element_i++) {
				int32_t value_element_element;

				value_element_element = value_element[value_element_i];

				/* Marshal a int32_t onto the message */
				if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_INT32, &value_element_element)) {
					dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
					dbus_message_iter_abandon_container (&variter, &value_iter);
					dbus_message_iter_abandon_container (iter, &variter);
					nih_error_raise_no_memory ();
					return -1;
				}
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_int32_array_array_set (NihDBusObject *  object,
                                                NihDBusMessage * message,
                                                DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	size_t          value_size;
	int32_t **      value;
	size_t *        value_len;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32_array_array property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32_array_array property");
		return -1;
	}

	dbus_message_iter_recurse (&variter, &value_iter);

	value_size = 0;
	value = NULL;
	value_len = NULL;

	value = nih_alloc (message, sizeof (int32_t *));
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
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
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to int32_array_array property");
			return -1;
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
				nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
				                             "Invalid arguments to int32_array_array property");
				return -1;
			}

			dbus_message_iter_get_basic (&value_element_iter, &value_element_element);

			dbus_message_iter_next (&value_element_iter);

			if (value_element_len + 1 > SIZE_MAX / sizeof (int32_t)) {
				if (value_element)
					nih_free (value_element);
				if (value)
					nih_free (value);
				nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
				                             "Invalid arguments to int32_array_array property");
				return -1;
			}

			value_element_tmp = nih_realloc (value_element, value, sizeof (int32_t) * (value_element_len + 1));
			if (! value_element_tmp) {
				if (value_element)
					nih_free (value_element);
				if (value)
					nih_free (value);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element = value_element_tmp;
			value_element[value_element_len] = value_element_element;

			value_element_len++;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (int32_t *)) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to int32_array_array property");
			return -1;
		}

		value_tmp = nih_realloc (value, message, sizeof (int32_t *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		if (value_size + 1 > SIZE_MAX / sizeof (size_t)) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to int32_array_array property");
			return -1;
		}

		value_len_tmp = nih_realloc (value_len, value, sizeof (size_t) * (value_size + 1));
		if (! value_len_tmp) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		value_len = value_len_tmp;
		value_len[value_size] = value_element_len;

		value_size++;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to int32_array_array property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_int32_array_array (object->data, message, value, value_len) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_struct_array_get (NihDBusObject *  object,
                                           NihDBusMessage * message,
                                           DBusMessageIter *iter)
{
	DBusMessageIter            variter;
	DBusMessageIter            value_iter;
	MyTestStructArrayElement **value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_struct_array (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "a(su)", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "(su)", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                 value_element_iter;
			const char *                    value_element_item0;
			uint32_t                        value_element_item1;
			const MyTestStructArrayElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_STRUCT, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_struct_array_set (NihDBusObject *  object,
                                           NihDBusMessage * message,
                                           DBusMessageIter *iter)
{
	DBusMessageIter            variter;
	DBusMessageIter            value_iter;
	size_t                     value_size;
	MyTestStructArrayElement **value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to struct_array property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to struct_array property");
		return -1;
	}

	dbus_message_iter_recurse (&variter, &value_iter);

	value_size = 0;
	value = NULL;

	value = nih_alloc (message, sizeof (MyTestStructArrayElement *));
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	value[value_size] = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter            value_element_iter;
		const char *               value_element_item0_dbus;
		char *                     value_element_item0;
		uint32_t                   value_element_item1;
		MyTestStructArrayElement **value_tmp;
		MyTestStructArrayElement * value_element;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRUCT) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to struct_array property");
			return -1;
		}

		dbus_message_iter_recurse (&value_iter, &value_element_iter);

		value_element = nih_new (value, MyTestStructArrayElement);
		if (! value_element) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to struct_array property");
			return -1;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item0_dbus);

		value_element_item0 = nih_strdup (value_element, value_element_item0_dbus);
		if (! value_element_item0) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		dbus_message_iter_next (&value_element_iter);

		value_element->item0 = value_element_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_UINT32) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to struct_array property");
			return -1;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item1);

		dbus_message_iter_next (&value_element_iter);

		value_element->item1 = value_element_item1;

		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to struct_array property");
			return -1;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (MyTestStructArrayElement *)) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to struct_array property");
			return -1;
		}

		value_tmp = nih_realloc (value, message, sizeof (MyTestStructArrayElement *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		value_size++;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to struct_array property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_struct_array (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_dict_entry_array_get (NihDBusObject *  object,
                                               NihDBusMessage * message,
                                               DBusMessageIter *iter)
{
	DBusMessageIter               variter;
	DBusMessageIter               value_iter;
	MyTestDictEntryArrayElement **value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_dict_entry_array (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "a{su}", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "{su}", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter                    value_element_iter;
			const char *                       value_element_item0;
			uint32_t                           value_element_item1;
			const MyTestDictEntryArrayElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_DICT_ENTRY, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element_item1 = value_element->item1;

			/* Marshal a uint32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_UINT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_dict_entry_array_set (NihDBusObject *  object,
                                               NihDBusMessage * message,
                                               DBusMessageIter *iter)
{
	DBusMessageIter               variter;
	DBusMessageIter               value_iter;
	size_t                        value_size;
	MyTestDictEntryArrayElement **value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to dict_entry_array property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to dict_entry_array property");
		return -1;
	}

	dbus_message_iter_recurse (&variter, &value_iter);

	value_size = 0;
	value = NULL;

	value = nih_alloc (message, sizeof (MyTestDictEntryArrayElement *));
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	value[value_size] = NULL;

	while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
		DBusMessageIter               value_element_iter;
		const char *                  value_element_item0_dbus;
		char *                        value_element_item0;
		uint32_t                      value_element_item1;
		MyTestDictEntryArrayElement **value_tmp;
		MyTestDictEntryArrayElement * value_element;

		/* Demarshal a structure from the message */
		if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_DICT_ENTRY) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to dict_entry_array property");
			return -1;
		}

		dbus_message_iter_recurse (&value_iter, &value_element_iter);

		value_element = nih_new (value, MyTestDictEntryArrayElement);
		if (! value_element) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to dict_entry_array property");
			return -1;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item0_dbus);

		value_element_item0 = nih_strdup (value_element, value_element_item0_dbus);
		if (! value_element_item0) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		dbus_message_iter_next (&value_element_iter);

		value_element->item0 = value_element_item0;

		/* Demarshal a uint32_t from the message */
		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_UINT32) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to dict_entry_array property");
			return -1;
		}

		dbus_message_iter_get_basic (&value_element_iter, &value_element_item1);

		dbus_message_iter_next (&value_element_iter);

		value_element->item1 = value_element_item1;

		if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
			nih_free (value_element);
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to dict_entry_array property");
			return -1;
		}

		dbus_message_iter_next (&value_iter);

		if (value_size + 2 > SIZE_MAX / sizeof (MyTestDictEntryArrayElement *)) {
			if (value)
				nih_free (value);
			nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
			                             "Invalid arguments to dict_entry_array property");
			return -1;
		}

		value_tmp = nih_realloc (value, message, sizeof (MyTestDictEntryArrayElement *) * (value_size + 2));
		if (! value_tmp) {
			if (value)
				nih_free (value);
			nih_error_raise_no_memory ();
			return -1;
		}

		value = value_tmp;
		value[value_size] = value_element;
		value[value_size + 1] = NULL;

		value_size++;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to dict_entry_array property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_dict_entry_array (object->data, message, value) < 0)
		return -1;

	return 0;
}


static int
my_com_netsplit_Nih_Test_unix_fd_get (NihDBusObject *  object,
                                      NihDBusMessage * message,
                                      DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int             value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (my_test_get_unix_fd (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "h", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_UNIX_FD, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}

static int
my_com_netsplit_Nih_Test_unix_fd_set (NihDBusObject *  object,
                                      NihDBusMessage * message,
                                      DBusMessageIter *iter)
{
	DBusMessageIter variter;
	int             value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to unix_fd property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_UNIX_FD) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to unix_fd property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value);

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to unix_fd property");
		return -1;
	}

	/* Call the handler function */
	if (my_test_set_unix_fd (object->data, message, value) < 0)
		return -1;

	return 0;
}
