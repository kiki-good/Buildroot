#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "internal.h"
#include "virjson.h"
#include "testutils.h"

struct testInfo {
    const char *doc;
    const char *expect;
    bool pass;
};


static int
testJSONFromString(const void *data)
{
    const struct testInfo *info = data;
    virJSONValuePtr json;
    int ret = -1;

    json = virJSONValueFromString(info->doc);

    if (info->pass) {
        if (!json) {
            VIR_TEST_VERBOSE("Fail to parse %s\n", info->doc);
            ret = -1;
            goto cleanup;
        } else {
            VIR_TEST_DEBUG("Parsed %s\n", info->doc);
        }
    } else {
        if (json) {
            VIR_TEST_VERBOSE("Should not have parsed %s\n", info->doc);
            ret = -1;
            goto cleanup;
        } else {
            VIR_TEST_DEBUG("Fail to parse %s\n", info->doc);
        }
    }

    ret = 0;

 cleanup:
    virJSONValueFree(json);
    return ret;
}


static int
testJSONAddRemove(const void *data)
{
    const struct testInfo *info = data;
    virJSONValuePtr json;
    virJSONValuePtr name = NULL;
    char *result = NULL;
    int ret = -1;

    json = virJSONValueFromString(info->doc);
    if (!json) {
        VIR_TEST_VERBOSE("Fail to parse %s\n", info->doc);
        ret = -1;
        goto cleanup;
    }

    switch (virJSONValueObjectRemoveKey(json, "name", &name)) {
    case 1:
        if (!info->pass) {
            VIR_TEST_VERBOSE("should not remove from non-object %s\n",
                             info->doc);
            goto cleanup;
        }
        break;
    case -1:
        if (!info->pass)
            ret = 0;
        else
            VIR_TEST_VERBOSE("Fail to recognize non-object %s\n", info->doc);
        goto cleanup;
    default:
        VIR_TEST_VERBOSE("unexpected result when removing from %s\n",
                         info->doc);
        goto cleanup;
    }
    if (STRNEQ_NULLABLE(virJSONValueGetString(name), "sample")) {
        VIR_TEST_VERBOSE("unexpected value after removing name: %s\n",
                         NULLSTR(virJSONValueGetString(name)));
        goto cleanup;
    }
    if (virJSONValueObjectRemoveKey(json, "name", NULL)) {
        VIR_TEST_VERBOSE("%s",
                         "unexpected success when removing missing key\n");
        goto cleanup;
    }
    if (virJSONValueObjectAppendString(json, "newname", "foo") < 0) {
        VIR_TEST_VERBOSE("%s", "unexpected failure adding new key\n");
        goto cleanup;
    }
    if (!(result = virJSONValueToString(json, false))) {
        VIR_TEST_VERBOSE("%s", "failed to stringize result\n");
        goto cleanup;
    }
    if (STRNEQ(info->expect, result)) {
        virtTestDifference(stderr, info->expect, result);
        goto cleanup;
    }
    ret = 0;

 cleanup:
    virJSONValueFree(json);
    virJSONValueFree(name);
    VIR_FREE(result);
    return ret;
}


static int
testJSONLookup(const void *data)
{
    const struct testInfo *info = data;
    virJSONValuePtr json;
    virJSONValuePtr value = NULL;
    char *result = NULL;
    int rc;
    int number;
    const char *str;
    int ret = -1;

    json = virJSONValueFromString(info->doc);
    if (!json) {
        VIR_TEST_VERBOSE("Fail to parse %s\n", info->doc);
        ret = -1;
        goto cleanup;
    }

    value = virJSONValueObjectGetObject(json, "a");
    if (value) {
        if (!info->pass) {
            VIR_TEST_VERBOSE("lookup for 'a' in '%s' should have failed\n",
                             info->doc);
            goto cleanup;
        } else {
            result = virJSONValueToString(value, false);
            if (STRNEQ_NULLABLE(result, "{}")) {
                VIR_TEST_VERBOSE("lookup for 'a' in '%s' found '%s' but "
                                 "should have found '{}'\n",
                                 info->doc, NULLSTR(result));
                goto cleanup;
            }
            VIR_FREE(result);
        }
    } else if (info->pass) {
        VIR_TEST_VERBOSE("lookup for 'a' in '%s' should have succeeded\n",
                         info->doc);
        goto cleanup;
    }

    number = 2;
    rc = virJSONValueObjectGetNumberInt(json, "b", &number);
    if (rc == 0) {
        if (!info->pass) {
            VIR_TEST_VERBOSE("lookup for 'b' in '%s' should have failed\n",
                             info->doc);
            goto cleanup;
        } else if (number != 1) {
            VIR_TEST_VERBOSE("lookup for 'b' in '%s' found %d but "
                             "should have found 1\n",
                             info->doc, number);
            goto cleanup;
        }
    } else if (info->pass) {
        VIR_TEST_VERBOSE("lookup for 'b' in '%s' should have succeeded\n",
                         info->doc);
        goto cleanup;
    }

    str = virJSONValueObjectGetString(json, "c");
    if (str) {
        if (!info->pass) {
            VIR_TEST_VERBOSE("lookup for 'c' in '%s' should have failed\n",
                             info->doc);
            goto cleanup;
        } else if (STRNEQ(str, "str")) {
            VIR_TEST_VERBOSE("lookup for 'c' in '%s' found '%s' but "
                             "should have found 'str'\n", info->doc, str);
                goto cleanup;
        }
    } else if (info->pass) {
        VIR_TEST_VERBOSE("lookup for 'c' in '%s' should have succeeded\n",
                         info->doc);
        goto cleanup;
    }

    value = virJSONValueObjectGetArray(json, "d");
    if (value) {
        if (!info->pass) {
            VIR_TEST_VERBOSE("lookup for 'd' in '%s' should have failed\n",
                             info->doc);
            goto cleanup;
        } else {
            result = virJSONValueToString(value, false);
            if (STRNEQ_NULLABLE(result, "[]")) {
                VIR_TEST_VERBOSE("lookup for 'd' in '%s' found '%s' but "
                                 "should have found '[]'\n",
                                 info->doc, NULLSTR(result));
                goto cleanup;
            }
            VIR_FREE(result);
        }
    } else if (info->pass) {
        VIR_TEST_VERBOSE("lookup for 'd' in '%s' should have succeeded\n",
                         info->doc);
        goto cleanup;
    }

    ret = 0;

 cleanup:
    virJSONValueFree(json);
    VIR_FREE(result);
    return ret;
}


static int
testJSONCopy(const void *data)
{
    const struct testInfo *info = data;
    virJSONValuePtr json = NULL;
    virJSONValuePtr jsonCopy = NULL;
    char *result = NULL;
    char *resultCopy = NULL;
    int ret = -1;

    json = virJSONValueFromString(info->doc);
    if (!json) {
        if (virTestGetVerbose())
            fprintf(stderr, "Failed to parse %s\n", info->doc);
        ret = -1;
        goto cleanup;
    }

    jsonCopy = virJSONValueCopy(json);
    if (!jsonCopy) {
        if (virTestGetVerbose())
            fprintf(stderr, "Failed to copy JSON data\n");
        ret = -1;
        goto cleanup;
    }

    result = virJSONValueToString(json, false);
    if (!result) {
        if (virTestGetVerbose())
            fprintf(stderr, "Failed to format original JSON data\n");
        ret = -1;
        goto cleanup;
    }

    resultCopy = virJSONValueToString(json, false);
    if (!resultCopy) {
        if (virTestGetVerbose())
            fprintf(stderr, "Failed to format copied JSON data\n");
        ret = -1;
        goto cleanup;
    }

    if (STRNEQ(result, resultCopy)) {
        if (virTestGetVerbose())
            virtTestDifference(stderr, result, resultCopy);
        ret = -1;
        goto cleanup;
    }

    VIR_FREE(result);
    VIR_FREE(resultCopy);

    result = virJSONValueToString(json, true);
    if (!result) {
        if (virTestGetVerbose())
            fprintf(stderr, "Failed to format original JSON data\n");
        ret = -1;
        goto cleanup;
    }

    resultCopy = virJSONValueToString(json, true);
    if (!resultCopy) {
        if (virTestGetVerbose())
            fprintf(stderr, "Failed to format copied JSON data\n");
        ret = -1;
        goto cleanup;
    }

    if (STRNEQ(result, resultCopy)) {
        if (virTestGetVerbose())
            virtTestDifference(stderr, result, resultCopy);
        ret = -1;
        goto cleanup;
    }

    ret = 0;
 cleanup:
    VIR_FREE(result);
    VIR_FREE(resultCopy);
    virJSONValueFree(json);
    virJSONValueFree(jsonCopy);
    return ret;
}


static int
mymain(void)
{
    int ret = 0;

#define DO_TEST_FULL(name, cmd, doc, expect, pass)                  \
    do {                                                            \
        struct testInfo info = { doc, expect, pass };               \
        if (virtTestRun(name, testJSON ## cmd, &info) < 0)          \
            ret = -1;                                               \
    } while (0)

#define DO_TEST_PARSE(name, doc)                \
    DO_TEST_FULL(name, FromString, doc, NULL, true)

#define DO_TEST_PARSE_FAIL(name, doc)           \
    DO_TEST_FULL(name, FromString, doc, NULL, false)


    DO_TEST_PARSE("Simple", "{\"return\": {}, \"id\": \"libvirt-1\"}");
    DO_TEST_PARSE("NotSoSimple", "{\"QMP\": {\"version\": {\"qemu\":"
                  "{\"micro\": 91, \"minor\": 13, \"major\": 0},"
                  "\"package\": \" (qemu-kvm-devel)\"}, \"capabilities\": []}}");


    DO_TEST_PARSE("Harder", "{\"return\": [{\"filename\": "
                  "\"unix:/home/berrange/.libvirt/qemu/lib/tck.monitor,server\","
                  "\"label\": \"charmonitor\"}, {\"filename\": \"pty:/dev/pts/158\","
                  "\"label\": \"charserial0\"}], \"id\": \"libvirt-3\"}");

    DO_TEST_PARSE("VeryHard", "{\"return\": [{\"name\": \"quit\"}, {\"name\":"
                  "\"eject\"}, {\"name\": \"change\"}, {\"name\": \"screendump\"},"
                  "{\"name\": \"stop\"}, {\"name\": \"cont\"}, {\"name\": "
                  "\"system_reset\"}, {\"name\": \"system_powerdown\"}, "
                  "{\"name\": \"device_add\"}, {\"name\": \"device_del\"}, "
                  "{\"name\": \"cpu\"}, {\"name\": \"memsave\"}, {\"name\": "
                  "\"pmemsave\"}, {\"name\": \"migrate\"}, {\"name\": "
                  "\"migrate_cancel\"}, {\"name\": \"migrate_set_speed\"},"
                  "{\"name\": \"client_migrate_info\"}, {\"name\": "
                  "\"migrate_set_downtime\"}, {\"name\": \"netdev_add\"}, "
                  "{\"name\": \"netdev_del\"}, {\"name\": \"block_resize\"},"
                  "{\"name\": \"balloon\"}, {\"name\": \"set_link\"}, {\"name\":"
                  "\"getfd\"}, {\"name\": \"closefd\"}, {\"name\": \"block_passwd\"},"
                  "{\"name\": \"set_password\"}, {\"name\": \"expire_password\"},"
                  "{\"name\": \"qmp_capabilities\"}, {\"name\": "
                  "\"human-monitor-command\"}, {\"name\": \"query-version\"},"
                  "{\"name\": \"query-commands\"}, {\"name\": \"query-chardev\"},"
                  "{\"name\": \"query-block\"}, {\"name\": \"query-blockstats\"}, "
                  "{\"name\": \"query-cpus\"}, {\"name\": \"query-pci\"}, {\"name\":"
                  "\"query-kvm\"}, {\"name\": \"query-status\"}, {\"name\": "
                  "\"query-mice\"}, {\"name\": \"query-vnc\"}, {\"name\": "
                  "\"query-spice\"}, {\"name\": \"query-name\"}, {\"name\": "
                  "\"query-uuid\"}, {\"name\": \"query-migrate\"}, {\"name\": "
                  "\"query-balloon\"}], \"id\": \"libvirt-2\"}");

    DO_TEST_FULL("add and remove", AddRemove,
                 "{\"name\": \"sample\", \"value\": true}",
                 "{\"value\":true,\"newname\":\"foo\"}",
                 true);
    DO_TEST_FULL("add and remove", AddRemove,
                 "[ 1 ]", NULL, false);

    DO_TEST_FULL("copy and free", Copy,
                 "{\"return\": [{\"name\": \"quit\"}, {\"name\": \"eject\"},"
                 "{\"name\": \"change\"}, {\"name\": \"screendump\"},"
                 "{\"name\": \"stop\"}, {\"name\": \"cont\"}, {\"name\": "
                 "\"system_reset\"}, {\"name\": \"system_powerdown\"}, "
                 "{\"name\": \"device_add\"}, {\"name\": \"device_del\"}, "
                 "{\"name\": \"cpu\"}, {\"name\": \"memsave\"}, {\"name\": "
                 "\"pmemsave\"}, {\"name\": \"migrate\"}, {\"name\": "
                 "\"migrate_cancel\"}, {\"name\": \"migrate_set_speed\"},"
                 "{\"name\": \"client_migrate_info\"}, {\"name\": "
                 "\"migrate_set_downtime\"}, {\"name\": \"netdev_add\"}, "
                 "{\"name\": \"netdev_del\"}, {\"name\": \"block_resize\"},"
                 "{\"name\": \"balloon\"}, {\"name\": \"set_link\"}, {\"name\":"
                 "\"getfd\"}, {\"name\": \"closefd\"}, {\"name\": \"block_passwd\"},"
                 "{\"name\": \"set_password\"}, {\"name\": \"expire_password\"},"
                 "{\"name\": \"qmp_capabilities\"}, {\"name\": "
                 "\"human-monitor-command\"}, {\"name\": \"query-version\"},"
                 "{\"name\": \"query-commands\"}, {\"name\": \"query-chardev\"},"
                 "{\"name\": \"query-block\"}, {\"name\": \"query-blockstats\"}, "
                 "{\"name\": \"query-cpus\"}, {\"name\": \"query-pci\"}, {\"name\":"
                 "\"query-kvm\"}, {\"name\": \"query-status\"}, {\"name\": "
                 "\"query-mice\"}, {\"name\": \"query-vnc\"}, {\"name\": "
                 "\"query-spice\"}, {\"name\": \"query-name\"}, {\"name\": "
                 "\"query-uuid\"}, {\"name\": \"query-migrate\"}, {\"name\": "
                 "\"query-balloon\"}], \"id\": \"libvirt-2\"}", NULL, true);


    DO_TEST_PARSE("almost nothing", "[]");
    DO_TEST_PARSE_FAIL("nothing", "");

    DO_TEST_PARSE("number without garbage", "[ 234545 ]");
    DO_TEST_PARSE_FAIL("number with garbage", "[ 2345b45 ]");

    DO_TEST_PARSE("float without garbage", "[ 0.0314159e+100 ]");
    DO_TEST_PARSE_FAIL("float with garbage", "[ 0.0314159ee+100 ]");

    DO_TEST_PARSE("string", "[ \"The meaning of life\" ]");
    DO_TEST_PARSE_FAIL("unterminated string", "[ \"The meaning of lif ]");

    DO_TEST_PARSE("integer", "1");
    DO_TEST_PARSE("boolean", "true");
    DO_TEST_PARSE("null", "null");
    DO_TEST_PARSE_FAIL("incomplete keyword", "tr");
    DO_TEST_PARSE_FAIL("overdone keyword", "[ truest ]");
    DO_TEST_PARSE_FAIL("unknown keyword", "huh");
    DO_TEST_PARSE_FAIL("comments", "[ /* nope */\n1 // not this either\n]");
    DO_TEST_PARSE_FAIL("trailing garbage", "[] []");
    DO_TEST_PARSE_FAIL("list without array", "1, 1");
    DO_TEST_PARSE_FAIL("parser abuse", "1] [2");
    DO_TEST_PARSE_FAIL("invalid UTF-8", "\"\x80\"");

    DO_TEST_PARSE_FAIL("object with numeric keys", "{ 1:1, 2:1, 3:2 }");
    DO_TEST_PARSE_FAIL("unterminated object", "{ \"1\":1, \"2\":1, \"3\":2");
    DO_TEST_PARSE_FAIL("unterminated array of objects",
                       "[ {\"name\": \"John\"}, {\"name\": \"Paul\"}, ");
    DO_TEST_PARSE_FAIL("array of an object with an array as a key",
                       "[ {[\"key1\", \"key2\"]: \"value\"} ]");
    DO_TEST_PARSE_FAIL("object with unterminated key", "{ \"key:7 }");
    DO_TEST_PARSE_FAIL("duplicate key", "{ \"a\": 1, \"a\": 1 }");

    DO_TEST_FULL("lookup on array", Lookup,
                 "[ 1 ]", NULL, false);
    DO_TEST_FULL("lookup on string", Lookup,
                 "\"str\"", NULL, false);
    DO_TEST_FULL("lookup on integer", Lookup,
                 "1", NULL, false);
    DO_TEST_FULL("lookup with missing key", Lookup,
                 "{ }", NULL, false);
    DO_TEST_FULL("lookup with wrong type", Lookup,
                 "{ \"a\": 1, \"b\": \"str\", \"c\": [], \"d\": {} }",
                 NULL, false);
    DO_TEST_FULL("lookup with correct type", Lookup,
                 "{ \"a\": {}, \"b\": 1, \"c\": \"str\", \"d\": [] }",
                 NULL, true);

    return (ret == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

VIRT_TEST_MAIN(mymain)
