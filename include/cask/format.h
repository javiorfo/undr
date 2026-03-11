#ifndef CASK_FORMAT_H
#define CASK_FORMAT_H
#include <stdlib.h>

// Format XML (or HTML) 
// xml_string: unformatted string
// tab_space: number of spaces to indent
// multiply_max_length: number to multiply the output string size
char* format_xml(const char* xml_string, size_t tab_space, size_t multiply_max_length);

// Format JSON 
// json_string: unformatted string
// tab_space: number of spaces to indent
// multiply_max_length: number to multiply the output string size
char* format_json(const char* json_string, size_t tab_space, size_t multiply_max_length);

#endif
