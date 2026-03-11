#include "cask/format.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_STR(expected, actual, msg)                              \
    if (strcmp(expected, actual) != 0) {                               \
        printf("FAILED: %s\nExpected:\n%s\nGot:\n%s\n", msg, expected, \
               actual);                                                \
        return 1;                                                      \
    } else {                                                           \
        printf("PASSED: %s\n", msg);                                   \
    }

int test_json_basic() {
    const char *input = "{\"a\":1,\"b\":[1,2]}";
    const char *expected = "{\n  \"a\": 1,\n  \"b\": [\n    1,\n    2\n  ]\n}";

    char *result = format_json(input, 2, 5);
    ASSERT_STR(expected, result, "Basic JSON formatting");

    free(result);
    return 0;
}

int test_xml_basic() {
    const char *input = "<?xml "
                        "version=\"1.0\"?><root><user><name>John</name><id>1</"
                        "id></user></root>";

    const char *expected = "<?xml version=\"1.0\"?>\n"
                           "<root>\n"
                           "  <user>\n"
                           "    <name>John</name>\n"
                           "    <id>1</id>\n"
                           "  </user>\n"
                           "</root>";

    char *result = format_xml(input, 2, 5);
    ASSERT_STR(expected, result, "XML Basic Indentation");

    free(result);
    return 0;
}

int main() {
    int failed = 0;

    printf("Running Format Tests...\n---\n");
    failed += test_json_basic();

    if (failed == 0) {
        printf("---\nALL TESTS PASSED!\n");
    } else {
        printf("---\nSOME TESTS FAILED: %d\n", failed);
    }

    printf("Starting Cask Library Tests...\n");
    printf("----------------------------------\n");

    failed += test_xml_basic();

    if (failed == 0) {
        printf("----------------------------------\n");
        printf("\033[0;32mResult: SUCCESS\033[0m\n");
    } else {
        printf("----------------------------------\n");
        printf("\033[0;31mResult: %d TEST(S) FAILED\033[0m\n", failed);
    }

    return failed;
}
