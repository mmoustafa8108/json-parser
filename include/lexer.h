#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include "sv.h"

#define EMPTY_SV() (String_View){.data = NULL, .count = 0}

typedef enum {
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COLUMN,
    TOKEN_COMMA,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_EOF,
} TokenType;


typedef struct {
    TokenType type;
    String_View data;
    int line;
} token_t;

typedef struct {
    String_View content;
    size_t position;
    char current_char;
    int line;
} json_lexer_t;

bool init_json_lexer(json_lexer_t* lexer, const char* file_path);
token_t get_next_token(json_lexer_t* lexer);

#endif