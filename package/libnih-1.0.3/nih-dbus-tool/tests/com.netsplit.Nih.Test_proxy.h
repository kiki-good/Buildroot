/* libnih
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifndef LIBNIH_TESTS_COM_NETSPLIT_NIH_TEST_PROXY_H
#define LIBNIH_TESTS_COM_NETSPLIT_NIH_TEST_PROXY_H

#include <dbus/dbus.h>

#include <stdint.h>

#include <nih/macros.h>

#include <nih-dbus/dbus_interface.h>
#include <nih-dbus/dbus_message.h>
#include <nih-dbus/dbus_pending_data.h>
#include <nih-dbus/dbus_proxy.h>


typedef struct proxy_test_struct_to_str_input {
	char *   item0;
	uint32_t item1;
} ProxyTestStructToStrInput;

typedef struct proxy_test_str_to_struct_output {
	char *   item0;
	uint32_t item1;
} ProxyTestStrToStructOutput;

typedef struct proxy_test_struct_array_to_str_input_element {
	char *   item0;
	uint32_t item1;
} ProxyTestStructArrayToStrInputElement;

typedef struct proxy_test_str_to_struct_array_output_element {
	char *   item0;
	uint32_t item1;
} ProxyTestStrToStructArrayOutputElement;

typedef struct proxy_test_dict_entry_array_to_str_input_element {
	char *   item0;
	uint32_t item1;
} ProxyTestDictEntryArrayToStrInputElement;

typedef struct proxy_test_str_to_dict_entry_array_output_element {
	char *   item0;
	uint32_t item1;
} ProxyTestStrToDictEntryArrayOutputElement;

typedef struct proxy_test_new_struct_value {
	char *   item0;
	uint32_t item1;
} ProxyTestNewStructValue;

typedef struct proxy_test_new_struct_array_value_element {
	char *   item0;
	uint32_t item1;
} ProxyTestNewStructArrayValueElement;

typedef struct proxy_test_new_dict_entry_array_value_element {
	char *   item0;
	uint32_t item1;
} ProxyTestNewDictEntryArrayValueElement;

typedef struct proxy_test_structure {
	char *   item0;
	uint32_t item1;
} ProxyTestStructure;

typedef struct proxy_test_struct_array_element {
	char *   item0;
	uint32_t item1;
} ProxyTestStructArrayElement;

typedef struct proxy_test_dict_entry_array_element {
	char *   item0;
	uint32_t item1;
} ProxyTestDictEntryArrayElement;

typedef struct proxy_test_properties {
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
	char *                           object_path;
	char *                           signature;
	ProxyTestStructure *             structure;
	int32_t *                        int32_array;
	size_t                           int32_array_len;
	char **                          str_array;
	int32_t **                       int32_array_array;
	size_t *                         int32_array_array_len;
	ProxyTestStructArrayElement **   struct_array;
	ProxyTestDictEntryArrayElement **dict_entry_array;
	int                              unix_fd;
} ProxyTestProperties;


typedef void (*ProxyTestOrdinaryMethodReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestNamelessMethodReply) (void *data, NihDBusMessage *message, const char *arg2);

typedef void (*ProxyTestAsyncMethodReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestByteToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToByteReply) (void *data, NihDBusMessage *message, uint8_t output);

typedef void (*ProxyTestBooleanToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToBooleanReply) (void *data, NihDBusMessage *message, int output);

typedef void (*ProxyTestInt16ToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToInt16Reply) (void *data, NihDBusMessage *message, int16_t output);

typedef void (*ProxyTestUint16ToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToUint16Reply) (void *data, NihDBusMessage *message, uint16_t output);

typedef void (*ProxyTestInt32ToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToInt32Reply) (void *data, NihDBusMessage *message, int32_t output);

typedef void (*ProxyTestUint32ToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToUint32Reply) (void *data, NihDBusMessage *message, uint32_t output);

typedef void (*ProxyTestInt64ToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToInt64Reply) (void *data, NihDBusMessage *message, int64_t output);

typedef void (*ProxyTestUint64ToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToUint64Reply) (void *data, NihDBusMessage *message, uint64_t output);

typedef void (*ProxyTestDoubleToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToDoubleReply) (void *data, NihDBusMessage *message, double output);

typedef void (*ProxyTestObjectPathToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToObjectPathReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestSignatureToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToSignatureReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStructToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToStructReply) (void *data, NihDBusMessage *message, const ProxyTestStrToStructOutput *output);

typedef void (*ProxyTestInt32ArrayToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToInt32ArrayReply) (void *data, NihDBusMessage *message, const int32_t *output, size_t output_len);

typedef void (*ProxyTestStrArrayToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToStrArrayReply) (void *data, NihDBusMessage *message, char * const *output);

typedef void (*ProxyTestInt32ArrayArrayToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToInt32ArrayArrayReply) (void *data, NihDBusMessage *message, int32_t * const *output, const size_t *output_len);

typedef void (*ProxyTestStructArrayToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToStructArrayReply) (void *data, NihDBusMessage *message, ProxyTestStrToStructArrayOutputElement * const *output);

typedef void (*ProxyTestDictEntryArrayToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToDictEntryArrayReply) (void *data, NihDBusMessage *message, ProxyTestStrToDictEntryArrayOutputElement * const *output);

typedef void (*ProxyTestUnixFdToStrReply) (void *data, NihDBusMessage *message, const char *output);

typedef void (*ProxyTestStrToUnixFdReply) (void *data, NihDBusMessage *message, int output);

typedef void (*ProxyTestNewByteHandler) (void *data, NihDBusMessage *message, uint8_t value);

typedef void (*ProxyTestNewBooleanHandler) (void *data, NihDBusMessage *message, int value);

typedef void (*ProxyTestNewInt16Handler) (void *data, NihDBusMessage *message, int16_t value);

typedef void (*ProxyTestNewUint16Handler) (void *data, NihDBusMessage *message, uint16_t value);

typedef void (*ProxyTestNewInt32Handler) (void *data, NihDBusMessage *message, int32_t value);

typedef void (*ProxyTestNewUint32Handler) (void *data, NihDBusMessage *message, uint32_t value);

typedef void (*ProxyTestNewInt64Handler) (void *data, NihDBusMessage *message, int64_t value);

typedef void (*ProxyTestNewUint64Handler) (void *data, NihDBusMessage *message, uint64_t value);

typedef void (*ProxyTestNewDoubleHandler) (void *data, NihDBusMessage *message, double value);

typedef void (*ProxyTestNewStringHandler) (void *data, NihDBusMessage *message, const char *value);

typedef void (*ProxyTestNewObjectPathHandler) (void *data, NihDBusMessage *message, const char *value);

typedef void (*ProxyTestNewSignatureHandler) (void *data, NihDBusMessage *message, const char *value);

typedef void (*ProxyTestNewStructHandler) (void *data, NihDBusMessage *message, const ProxyTestNewStructValue *value);

typedef void (*ProxyTestNewInt32ArrayHandler) (void *data, NihDBusMessage *message, const int32_t *value, size_t value_len);

typedef void (*ProxyTestNewStrArrayHandler) (void *data, NihDBusMessage *message, char * const *value);

typedef void (*ProxyTestNewInt32ArrayArrayHandler) (void *data, NihDBusMessage *message, int32_t * const *value, const size_t *value_len);

typedef void (*ProxyTestNewStructArrayHandler) (void *data, NihDBusMessage *message, ProxyTestNewStructArrayValueElement * const *value);

typedef void (*ProxyTestNewDictEntryArrayHandler) (void *data, NihDBusMessage *message, ProxyTestNewDictEntryArrayValueElement * const *value);

typedef void (*ProxyTestNewUnixFdHandler) (void *data, NihDBusMessage *message, int value);

typedef void (*ProxyTestGetByteReply) (void *data, NihDBusMessage *message, uint8_t value);

typedef void (*ProxyTestSetByteReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetBooleanReply) (void *data, NihDBusMessage *message, int value);

typedef void (*ProxyTestSetBooleanReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetInt16Reply) (void *data, NihDBusMessage *message, int16_t value);

typedef void (*ProxyTestSetInt16Reply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetUint16Reply) (void *data, NihDBusMessage *message, uint16_t value);

typedef void (*ProxyTestSetUint16Reply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetInt32Reply) (void *data, NihDBusMessage *message, int32_t value);

typedef void (*ProxyTestSetInt32Reply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetUint32Reply) (void *data, NihDBusMessage *message, uint32_t value);

typedef void (*ProxyTestSetUint32Reply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetInt64Reply) (void *data, NihDBusMessage *message, int64_t value);

typedef void (*ProxyTestSetInt64Reply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetUint64Reply) (void *data, NihDBusMessage *message, uint64_t value);

typedef void (*ProxyTestSetUint64Reply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetDubbleReply) (void *data, NihDBusMessage *message, double value);

typedef void (*ProxyTestSetDubbleReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetStringReply) (void *data, NihDBusMessage *message, const char *value);

typedef void (*ProxyTestSetStringReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetObjectPathReply) (void *data, NihDBusMessage *message, const char *value);

typedef void (*ProxyTestSetObjectPathReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetSignatureReply) (void *data, NihDBusMessage *message, const char *value);

typedef void (*ProxyTestSetSignatureReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetStructureReply) (void *data, NihDBusMessage *message, const ProxyTestStructure *value);

typedef void (*ProxyTestSetStructureReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetInt32ArrayReply) (void *data, NihDBusMessage *message, const int32_t *value, size_t value_len);

typedef void (*ProxyTestSetInt32ArrayReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetStrArrayReply) (void *data, NihDBusMessage *message, char * const *value);

typedef void (*ProxyTestSetStrArrayReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetInt32ArrayArrayReply) (void *data, NihDBusMessage *message, int32_t * const *value, const size_t *value_len);

typedef void (*ProxyTestSetInt32ArrayArrayReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetStructArrayReply) (void *data, NihDBusMessage *message, ProxyTestStructArrayElement * const *value);

typedef void (*ProxyTestSetStructArrayReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetDictEntryArrayReply) (void *data, NihDBusMessage *message, ProxyTestDictEntryArrayElement * const *value);

typedef void (*ProxyTestSetDictEntryArrayReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetUnixFdReply) (void *data, NihDBusMessage *message, int value);

typedef void (*ProxyTestSetUnixFdReply) (void *data, NihDBusMessage *message);

typedef void (*ProxyTestGetAllReply) (void *data, NihDBusMessage *message, const ProxyTestProperties *properties);


NIH_BEGIN_EXTERN

extern const NihDBusInterface  proxy_com_netsplit_Nih_Test;
extern const NihDBusInterface *proxy_interfaces[];


DBusPendingCall *proxy_test_ordinary_method               (NihDBusProxy *proxy, const char *input, ProxyTestOrdinaryMethodReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_ordinary_method_sync          (const void *parent, NihDBusProxy *proxy, const char *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_nameless_method               (NihDBusProxy *proxy, const char *arg1, ProxyTestNamelessMethodReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_nameless_method_sync          (const void *parent, NihDBusProxy *proxy, const char *arg1, char **arg2)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_async_method                  (NihDBusProxy *proxy, const char *input, ProxyTestAsyncMethodReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_async_method_sync             (const void *parent, NihDBusProxy *proxy, const char *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_byte_to_str                   (NihDBusProxy *proxy, uint8_t input, ProxyTestByteToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_byte_to_str_sync              (const void *parent, NihDBusProxy *proxy, uint8_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_byte                   (NihDBusProxy *proxy, const char *input, ProxyTestStrToByteReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_byte_sync              (const void *parent, NihDBusProxy *proxy, const char *input, uint8_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_boolean_to_str                (NihDBusProxy *proxy, int input, ProxyTestBooleanToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_boolean_to_str_sync           (const void *parent, NihDBusProxy *proxy, int input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_boolean                (NihDBusProxy *proxy, const char *input, ProxyTestStrToBooleanReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_boolean_sync           (const void *parent, NihDBusProxy *proxy, const char *input, int *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_int16_to_str                  (NihDBusProxy *proxy, int16_t input, ProxyTestInt16ToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_int16_to_str_sync             (const void *parent, NihDBusProxy *proxy, int16_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_int16                  (NihDBusProxy *proxy, const char *input, ProxyTestStrToInt16Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_int16_sync             (const void *parent, NihDBusProxy *proxy, const char *input, int16_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_uint16_to_str                 (NihDBusProxy *proxy, uint16_t input, ProxyTestUint16ToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_uint16_to_str_sync            (const void *parent, NihDBusProxy *proxy, uint16_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_uint16                 (NihDBusProxy *proxy, const char *input, ProxyTestStrToUint16Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_uint16_sync            (const void *parent, NihDBusProxy *proxy, const char *input, uint16_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_int32_to_str                  (NihDBusProxy *proxy, int32_t input, ProxyTestInt32ToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_int32_to_str_sync             (const void *parent, NihDBusProxy *proxy, int32_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_int32                  (NihDBusProxy *proxy, const char *input, ProxyTestStrToInt32Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_int32_sync             (const void *parent, NihDBusProxy *proxy, const char *input, int32_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_uint32_to_str                 (NihDBusProxy *proxy, uint32_t input, ProxyTestUint32ToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_uint32_to_str_sync            (const void *parent, NihDBusProxy *proxy, uint32_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_uint32                 (NihDBusProxy *proxy, const char *input, ProxyTestStrToUint32Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_uint32_sync            (const void *parent, NihDBusProxy *proxy, const char *input, uint32_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_int64_to_str                  (NihDBusProxy *proxy, int64_t input, ProxyTestInt64ToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_int64_to_str_sync             (const void *parent, NihDBusProxy *proxy, int64_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_int64                  (NihDBusProxy *proxy, const char *input, ProxyTestStrToInt64Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_int64_sync             (const void *parent, NihDBusProxy *proxy, const char *input, int64_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_uint64_to_str                 (NihDBusProxy *proxy, uint64_t input, ProxyTestUint64ToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_uint64_to_str_sync            (const void *parent, NihDBusProxy *proxy, uint64_t input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_uint64                 (NihDBusProxy *proxy, const char *input, ProxyTestStrToUint64Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_uint64_sync            (const void *parent, NihDBusProxy *proxy, const char *input, uint64_t *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_double_to_str                 (NihDBusProxy *proxy, double input, ProxyTestDoubleToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_double_to_str_sync            (const void *parent, NihDBusProxy *proxy, double input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_double                 (NihDBusProxy *proxy, const char *input, ProxyTestStrToDoubleReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_double_sync            (const void *parent, NihDBusProxy *proxy, const char *input, double *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_object_path_to_str            (NihDBusProxy *proxy, const char *input, ProxyTestObjectPathToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_object_path_to_str_sync       (const void *parent, NihDBusProxy *proxy, const char *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_object_path            (NihDBusProxy *proxy, const char *input, ProxyTestStrToObjectPathReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_object_path_sync       (const void *parent, NihDBusProxy *proxy, const char *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_signature_to_str              (NihDBusProxy *proxy, const char *input, ProxyTestSignatureToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_signature_to_str_sync         (const void *parent, NihDBusProxy *proxy, const char *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_signature              (NihDBusProxy *proxy, const char *input, ProxyTestStrToSignatureReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_signature_sync         (const void *parent, NihDBusProxy *proxy, const char *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_struct_to_str                 (NihDBusProxy *proxy, const ProxyTestStructToStrInput *input, ProxyTestStructToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_struct_to_str_sync            (const void *parent, NihDBusProxy *proxy, const ProxyTestStructToStrInput *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_struct                 (NihDBusProxy *proxy, const char *input, ProxyTestStrToStructReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_struct_sync            (const void *parent, NihDBusProxy *proxy, const char *input, ProxyTestStrToStructOutput **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_int32_array_to_str            (NihDBusProxy *proxy, const int32_t *input, size_t input_len, ProxyTestInt32ArrayToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_int32_array_to_str_sync       (const void *parent, NihDBusProxy *proxy, const int32_t *input, size_t input_len, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_int32_array            (NihDBusProxy *proxy, const char *input, ProxyTestStrToInt32ArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_int32_array_sync       (const void *parent, NihDBusProxy *proxy, const char *input, int32_t **output, size_t *output_len)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_array_to_str              (NihDBusProxy *proxy, char * const *input, ProxyTestStrArrayToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_array_to_str_sync         (const void *parent, NihDBusProxy *proxy, char * const *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_str_array              (NihDBusProxy *proxy, const char *input, ProxyTestStrToStrArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_str_array_sync         (const void *parent, NihDBusProxy *proxy, const char *input, char ***output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_int32_array_array_to_str      (NihDBusProxy *proxy, int32_t * const *input, const size_t *input_len, ProxyTestInt32ArrayArrayToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_int32_array_array_to_str_sync (const void *parent, NihDBusProxy *proxy, int32_t * const *input, const size_t *input_len, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_int32_array_array      (NihDBusProxy *proxy, const char *input, ProxyTestStrToInt32ArrayArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_int32_array_array_sync (const void *parent, NihDBusProxy *proxy, const char *input, int32_t ***output, size_t **output_len)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_struct_array_to_str           (NihDBusProxy *proxy, ProxyTestStructArrayToStrInputElement * const *input, ProxyTestStructArrayToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_struct_array_to_str_sync      (const void *parent, NihDBusProxy *proxy, ProxyTestStructArrayToStrInputElement * const *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_struct_array           (NihDBusProxy *proxy, const char *input, ProxyTestStrToStructArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_struct_array_sync      (const void *parent, NihDBusProxy *proxy, const char *input, ProxyTestStrToStructArrayOutputElement ***output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_dict_entry_array_to_str       (NihDBusProxy *proxy, ProxyTestDictEntryArrayToStrInputElement * const *input, ProxyTestDictEntryArrayToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_dict_entry_array_to_str_sync  (const void *parent, NihDBusProxy *proxy, ProxyTestDictEntryArrayToStrInputElement * const *input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_dict_entry_array       (NihDBusProxy *proxy, const char *input, ProxyTestStrToDictEntryArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_dict_entry_array_sync  (const void *parent, NihDBusProxy *proxy, const char *input, ProxyTestStrToDictEntryArrayOutputElement ***output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_unix_fd_to_str                (NihDBusProxy *proxy, int input, ProxyTestUnixFdToStrReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_unix_fd_to_str_sync           (const void *parent, NihDBusProxy *proxy, int input, char **output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_str_to_unix_fd                (NihDBusProxy *proxy, const char *input, ProxyTestStrToUnixFdReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_str_to_unix_fd_sync           (const void *parent, NihDBusProxy *proxy, const char *input, int *output)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_byte                      (NihDBusProxy *proxy, ProxyTestGetByteReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_byte_sync                 (const void *parent, NihDBusProxy *proxy, uint8_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_byte                      (NihDBusProxy *proxy, uint8_t value, ProxyTestSetByteReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_byte_sync                 (const void *parent, NihDBusProxy *proxy, uint8_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_boolean                   (NihDBusProxy *proxy, ProxyTestGetBooleanReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_boolean_sync              (const void *parent, NihDBusProxy *proxy, int *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_boolean                   (NihDBusProxy *proxy, int value, ProxyTestSetBooleanReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_boolean_sync              (const void *parent, NihDBusProxy *proxy, int value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_int16                     (NihDBusProxy *proxy, ProxyTestGetInt16Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_int16_sync                (const void *parent, NihDBusProxy *proxy, int16_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_int16                     (NihDBusProxy *proxy, int16_t value, ProxyTestSetInt16Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_int16_sync                (const void *parent, NihDBusProxy *proxy, int16_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_uint16                    (NihDBusProxy *proxy, ProxyTestGetUint16Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_uint16_sync               (const void *parent, NihDBusProxy *proxy, uint16_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_uint16                    (NihDBusProxy *proxy, uint16_t value, ProxyTestSetUint16Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_uint16_sync               (const void *parent, NihDBusProxy *proxy, uint16_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_int32                     (NihDBusProxy *proxy, ProxyTestGetInt32Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_int32_sync                (const void *parent, NihDBusProxy *proxy, int32_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_int32                     (NihDBusProxy *proxy, int32_t value, ProxyTestSetInt32Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_int32_sync                (const void *parent, NihDBusProxy *proxy, int32_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_uint32                    (NihDBusProxy *proxy, ProxyTestGetUint32Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_uint32_sync               (const void *parent, NihDBusProxy *proxy, uint32_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_uint32                    (NihDBusProxy *proxy, uint32_t value, ProxyTestSetUint32Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_uint32_sync               (const void *parent, NihDBusProxy *proxy, uint32_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_int64                     (NihDBusProxy *proxy, ProxyTestGetInt64Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_int64_sync                (const void *parent, NihDBusProxy *proxy, int64_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_int64                     (NihDBusProxy *proxy, int64_t value, ProxyTestSetInt64Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_int64_sync                (const void *parent, NihDBusProxy *proxy, int64_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_uint64                    (NihDBusProxy *proxy, ProxyTestGetUint64Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_uint64_sync               (const void *parent, NihDBusProxy *proxy, uint64_t *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_uint64                    (NihDBusProxy *proxy, uint64_t value, ProxyTestSetUint64Reply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_uint64_sync               (const void *parent, NihDBusProxy *proxy, uint64_t value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_dubble                    (NihDBusProxy *proxy, ProxyTestGetDubbleReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_dubble_sync               (const void *parent, NihDBusProxy *proxy, double *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_dubble                    (NihDBusProxy *proxy, double value, ProxyTestSetDubbleReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_dubble_sync               (const void *parent, NihDBusProxy *proxy, double value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_string                    (NihDBusProxy *proxy, ProxyTestGetStringReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_string_sync               (const void *parent, NihDBusProxy *proxy, char **value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_string                    (NihDBusProxy *proxy, const char *value, ProxyTestSetStringReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_string_sync               (const void *parent, NihDBusProxy *proxy, const char *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_object_path               (NihDBusProxy *proxy, ProxyTestGetObjectPathReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_object_path_sync          (const void *parent, NihDBusProxy *proxy, char **value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_object_path               (NihDBusProxy *proxy, const char *value, ProxyTestSetObjectPathReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_object_path_sync          (const void *parent, NihDBusProxy *proxy, const char *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_signature                 (NihDBusProxy *proxy, ProxyTestGetSignatureReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_signature_sync            (const void *parent, NihDBusProxy *proxy, char **value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_signature                 (NihDBusProxy *proxy, const char *value, ProxyTestSetSignatureReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_signature_sync            (const void *parent, NihDBusProxy *proxy, const char *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_structure                 (NihDBusProxy *proxy, ProxyTestGetStructureReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_structure_sync            (const void *parent, NihDBusProxy *proxy, ProxyTestStructure **value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_structure                 (NihDBusProxy *proxy, const ProxyTestStructure *value, ProxyTestSetStructureReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_structure_sync            (const void *parent, NihDBusProxy *proxy, const ProxyTestStructure *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_int32_array               (NihDBusProxy *proxy, ProxyTestGetInt32ArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_int32_array_sync          (const void *parent, NihDBusProxy *proxy, int32_t **value, size_t *value_len)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_int32_array               (NihDBusProxy *proxy, const int32_t *value, size_t value_len, ProxyTestSetInt32ArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_int32_array_sync          (const void *parent, NihDBusProxy *proxy, const int32_t *value, size_t value_len)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_str_array                 (NihDBusProxy *proxy, ProxyTestGetStrArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_str_array_sync            (const void *parent, NihDBusProxy *proxy, char ***value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_str_array                 (NihDBusProxy *proxy, char * const *value, ProxyTestSetStrArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_str_array_sync            (const void *parent, NihDBusProxy *proxy, char * const *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_int32_array_array         (NihDBusProxy *proxy, ProxyTestGetInt32ArrayArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_int32_array_array_sync    (const void *parent, NihDBusProxy *proxy, int32_t ***value, size_t **value_len)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_int32_array_array         (NihDBusProxy *proxy, int32_t * const *value, const size_t *value_len, ProxyTestSetInt32ArrayArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_int32_array_array_sync    (const void *parent, NihDBusProxy *proxy, int32_t * const *value, const size_t *value_len)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_struct_array              (NihDBusProxy *proxy, ProxyTestGetStructArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_struct_array_sync         (const void *parent, NihDBusProxy *proxy, ProxyTestStructArrayElement ***value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_struct_array              (NihDBusProxy *proxy, ProxyTestStructArrayElement * const *value, ProxyTestSetStructArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_struct_array_sync         (const void *parent, NihDBusProxy *proxy, ProxyTestStructArrayElement * const *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_dict_entry_array          (NihDBusProxy *proxy, ProxyTestGetDictEntryArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_dict_entry_array_sync     (const void *parent, NihDBusProxy *proxy, ProxyTestDictEntryArrayElement ***value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_dict_entry_array          (NihDBusProxy *proxy, ProxyTestDictEntryArrayElement * const *value, ProxyTestSetDictEntryArrayReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_dict_entry_array_sync     (const void *parent, NihDBusProxy *proxy, ProxyTestDictEntryArrayElement * const *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_unix_fd                   (NihDBusProxy *proxy, ProxyTestGetUnixFdReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_unix_fd_sync              (const void *parent, NihDBusProxy *proxy, int *value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_set_unix_fd                   (NihDBusProxy *proxy, int value, ProxyTestSetUnixFdReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_set_unix_fd_sync              (const void *parent, NihDBusProxy *proxy, int value)
	__attribute__ ((warn_unused_result));
DBusPendingCall *proxy_test_get_all                       (NihDBusProxy *proxy, ProxyTestGetAllReply handler, NihDBusErrorHandler error_handler, void *data, int timeout)
	__attribute__ ((warn_unused_result));
int              proxy_test_get_all_sync                  (const void *parent, NihDBusProxy *proxy, ProxyTestProperties **properties)
	__attribute__ ((warn_unused_result));

NIH_END_EXTERN

#endif /* LIBNIH_TESTS_COM_NETSPLIT_NIH_TEST_PROXY_H */
