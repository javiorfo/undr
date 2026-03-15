#ifndef UNDR_FORMAT_H
#define UNDR_FORMAT_H

#include <stdlib.h>

/**
 * @brief Pretty-prints an XML or HTML string with custom indentation.
 * * @param xml_string    The raw, unformatted XML/HTML input.
 * @param tab_size      Number of spaces per indentation level.
 * @param max_out_size  The maximum allowed size for the formatted output buffer.
 * (Prevents buffer overflows if the input is malformed).
 * @return              A heap-allocated, null-terminated formatted string. 
 * Caller is responsible for free(). Returns NULL on failure.
 */
char* format_xml(const char* xml_string, size_t tab_size, size_t max_out_size);

/**
 * @brief Pretty-prints a JSON string with custom indentation.
 * * @param json_string   The minified or unformatted JSON input.
 * @param tab_size      Number of spaces per indentation level.
 * @param max_out_size  The maximum allowed size for the formatted output buffer.
 * @return              A heap-allocated, null-terminated formatted string.
 * Caller is responsible for free(). Returns NULL on failure.
 */
char* format_json(const char* json_string, size_t tab_size, size_t max_out_size);

#endif
