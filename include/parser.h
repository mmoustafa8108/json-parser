#ifndef JSON_H
#define JSON_H

#include <stdbool.h>
#include "sv.h"

typedef struct json_element_t json_element_t;
typedef struct json_value_t json_value_t;
typedef struct json_array_t json_array_t;

typedef enum {
    JSON_VALUE_NUM,
    JSON_VALUE_STR,
    JSON_VALUE_BOOL,
    JSON_VALUE_NULL,
    JSON_VALUE_ARRAY,
    JSON_VALUE_OBJECT,
} JsonValueType;

struct json_array_t {
    json_value_t* members;
    size_t count, capacity;
};

struct json_value_t {
    JsonValueType type;
    union {
        struct json_array_t array;
        String_View str;
        json_element_t* object;
        void* null;
        double number;
        bool boolean;
    } value;
};

struct json_element_t {
    String_View key;
    json_value_t value;
};


double parse_number(String_View str_view);

#endif