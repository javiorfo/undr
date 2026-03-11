#include "undr/arena.h"
#include "undr/format.h"
#include "undr/jwt.h"
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

int test_arena() {
    Arena *arena = arena_init(1024);

    int *numbers = arena_alloc(arena, 5 * sizeof(int));
    for (int i = 0; i < 5; i++)
        numbers[i] = i * 10;

    char *msg = arena_alloc(arena, 20);
    strcpy(msg, "Hello Arena!");

    ASSERT_STR("Hello Arena!", msg, "Arena allocation");

    arena_free(arena);

    return 0;
}

int test_jwt() {
    Arena *arena = arena_init(4096);

    const char *raw_jwt =
        "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MD"
        "IyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c";

    Jwt token = decode_jwt(arena, raw_jwt);

    if (token.header && token.payload) {
        ASSERT_STR("{\"alg\":\"HS256\",\"typ\":\"JWT\"}", token.header,
                   "JWT Header");
        ASSERT_STR(
            "{\"sub\":\"1234567890\",\"name\":\"John Doe\",\"iat\":1516239022}",
            token.payload, "JWT Payload");
    }

    arena_free(arena);

    return 0;
}

int main() {
    int failed = 0;

    printf("Running Tests...\n---\n");

    printf("Starting Format JSON Tests...\n");
    failed += test_json_basic();

    printf("----------------------------------\n");
    printf("Starting Format XML Tests...\n");

    failed += test_xml_basic();

    printf("----------------------------------\n");
    printf("Starting Arena Tests...\n");

    failed += test_arena();

    printf("----------------------------------\n");
    printf("Starting JWT Tests...\n");

    failed += test_jwt();

    if (failed == 0) {
        printf("----------------------------------\n");
        printf("\033[0;32mResult: SUCCESS\033[0m\n");
    } else {
        printf("----------------------------------\n");
        printf("\033[0;31mResult: %d TEST(S) FAILED\033[0m\n", failed);
    }

    printf("----------------------------------\n");

    return failed;
}
