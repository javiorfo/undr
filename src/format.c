#include "undr/format.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool ends_with(const char *str, size_t len, const char *suffix) {
    size_t suffix_len = strlen(suffix);
    if (suffix_len > len) return false;
    return strncmp(str + len - suffix_len, suffix, suffix_len) == 0;
}

bool contains(const char *str, size_t len, const char *sub) {
    if (len == 0) return false;
    char *tmp = malloc(len + 1);
    if (!tmp) return false;
    memcpy(tmp, str, len);
    tmp[len] = '\0';
    bool result = strstr(tmp, sub) != NULL;
    free(tmp);
    return result;
}

void add_spaces_xml(size_t *spaces, size_t tab, const char *last,
                    size_t last_len, const char *current, size_t current_len) {
    if (starts_with(last, "<?xml")) return;

    bool last_is_closing =
        contains(last, last_len, "</") || ends_with(last, last_len, "/>");
    bool current_is_closing = starts_with(current, "</");

    if (last_is_closing && current_is_closing) {
        if (*spaces >= tab) *spaces -= tab;
    } else if (!last_is_closing) {
        *spaces += tab;
    }
}

void add_spaces_json(size_t indent, size_t tab_space, char *pretty_json,
                     size_t *index) {
    for (size_t i = 0; i < indent; i++) {
        for (size_t j = 0; j < tab_space; j++) {
            pretty_json[(*index)++] = ' ';
        }
    }
}

char *get_item_with_tab(size_t spaces, const char *item, size_t item_len) {
    char *result = malloc(spaces + item_len + 1);
    if (!result) return NULL;
    memset(result, ' ', spaces);
    memcpy(result + spaces, item, item_len);
    result[spaces + item_len] = '\0';
    return result;
}

char *format_json(const char *json_string, size_t tab_space,
                  size_t multiply_max_length) {
    size_t input_len = strlen(json_string);
    size_t max_pretty_length = input_len * multiply_max_length;

    char *pretty_json = malloc(max_pretty_length);
    if (!pretty_json) return NULL;

    size_t indent = 0;
    bool in_string = false;
    size_t index = 0;

    for (size_t i = 0; i < input_len; i++) {
        char c = json_string[i];

        switch (c) {
        case '\"':
            in_string = !in_string;
            pretty_json[index++] = c;
            break;

        case '{':
        case '[':
            pretty_json[index++] = c;
            if (!in_string) {
                pretty_json[index++] = '\n';
                indent++;
                add_spaces_json(indent, tab_space, pretty_json, &index);
            }
            break;

        case '}':
        case ']':
            if (!in_string) {
                pretty_json[index++] = '\n';
                if (indent > 0) indent--;
                add_spaces_json(indent, tab_space, pretty_json, &index);
            }
            pretty_json[index++] = c;
            break;

        case ',':
            pretty_json[index++] = c;
            if (!in_string) {
                pretty_json[index++] = '\n';
                add_spaces_json(indent, tab_space, pretty_json, &index);
            }
            break;

        case ' ':
        case '\t':
        case '\n':
        case '\r':
            if (in_string) { pretty_json[index++] = c; }
            break;

        case ':':
            pretty_json[index++] = c;
            if (!in_string) { pretty_json[index++] = ' '; }
            break;

        default:
            pretty_json[index++] = c;
            break;
        }
    }

    pretty_json[index] = '\0';

    char *result = strdup(pretty_json);
    free(pretty_json);
    return result;
}

char *format_xml(const char *xml_string, size_t tab_space,
                 size_t multiply_max_length) {
    size_t input_len = strlen(xml_string);
    char *tags = malloc(input_len * multiply_max_length);
    if (!tags) return NULL;

    bool in_tag = false;
    size_t index = 0;
    size_t last_index = 0;
    size_t spaces = 0;

    char **list = malloc(input_len * sizeof(char *));
    size_t list_count = 0;

    for (size_t i = 0; i < input_len; i++) {
        char c = xml_string[i];
        if (c == '<') {
            if (in_tag) {
                tags[index++] = c;
            } else {
                if (index > 0 && tags[index - 1] == '>') {
                    size_t current_len = index - last_index;
                    const char *current_ptr = &tags[last_index];

                    if (list_count > 0) {
                        add_spaces_xml(&spaces, tab_space, list[list_count - 1],
                                       strlen(list[list_count - 1]),
                                       current_ptr, current_len);
                        list[list_count++] =
                            get_item_with_tab(spaces, current_ptr, current_len);
                    } else {
                        char *first_item = malloc(current_len + 1);
                        memcpy(first_item, current_ptr, current_len);
                        first_item[current_len] = '\0';
                        list[list_count++] = first_item;
                    }
                    last_index = index;
                }
                in_tag = true;
                tags[index++] = c;
            }
        } else if (c == '>') {
            in_tag = false;
            tags[index++] = c;
        } else {
            tags[index++] = c;
        }
    }

    size_t final_len = index - last_index;
    char *final_item = malloc(final_len + 1);
    memcpy(final_item, &tags[last_index], final_len);
    final_item[final_len] = '\0';
    list[list_count++] = final_item;

    size_t total_out_len = 0;
    for (size_t i = 0; i < list_count; i++)
        total_out_len += strlen(list[i]) + 1;

    char *final_output = malloc(total_out_len + 1);
    char *ptr = final_output;
    for (size_t i = 0; i < list_count; i++) {
        size_t l = strlen(list[i]);
        memcpy(ptr, list[i], l);
        ptr += l;
        if (i < list_count - 1) *ptr++ = '\n';
        free(list[i]);
    }
    *ptr = '\0';

    free(list);
    free(tags);
    return final_output;
}
