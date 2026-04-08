#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "sv.h"

static String_View read_file(const char* path) {
    String_View str_view = {.data = NULL, .count = 0};
    
    FILE* file = fopen(path, "rb");
    
    if (!file) return str_view;
    
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char* data = malloc(size);
    size_t bytes_read = fread(data, 1, size, file);
    if (bytes_read < size) return str_view;
    
    return sv(data);
}


bool init_json_lexer(json_lexer_t* lexer, const char* file_path) {
    String_View str_view = read_file(file_path);
    
    if (str_view.count > 0) {
        lexer->content = str_view;
        lexer->position = 0;
        lexer->line = 0;
        lexer->current_char = lexer->content.data[0];
        return true;
    }

    return false;
}

static char peek(json_lexer_t* lexer) {
    if (lexer->position == lexer->content.count) return EOF;
    
    while (isspace(lexer->content.data[0])) {
        if (lexer->content.data[0] == '\n') lexer->line++;
        sv_chop_left(&lexer->content, 1);
    }

    return lexer->content.data[0];
}

static bool consume(json_lexer_t* lexer, char c) {
    if (lexer->content.data[0] == c) {
        sv_chop_left(&lexer->content, 1);
        if (c == '\n') lexer->line++;
        return true;
    }
    return false;
}

String_View lex_str(json_lexer_t* lexer) {
    consume(lexer, '"');
    
    size_t size  = 0;
    const char* data = lexer->content.data;
    while (!consume(lexer, '"') && lexer->content.count > 0) size++;
    
    consume(lexer, '"');
    return (String_View) {.data = data, .count = size};
}

String_View lex_array(json_lexer_t* lexer) {
    consume(lexer, '[');
    
    size_t size  = 0;
    const char* data = lexer->content.data;
    while (!consume(lexer, ']') && lexer->content.count > 0) size++;
    
    consume(lexer, ']');
    return (String_View) {.data = data, .count = size};
}


token_t lex_element(json_lexer_t* lexer) {
    switch (peek(lexer)) {
        case '"': return (token_t){.type = TOKEN_STRING, lex_str(lexer), .line = lexer->line};
        case '[': return  (token_t){.type = TOKEN_ARRAY, lex_array(lexer), .line = lexer->line};
    }
}


token_t get_next_token(json_lexer_t* lexer) {
    switch (peek(lexer)) {
        case '{': 
            consume(lexer, '{');
            return (token_t){.type = TOKEN_LBRACE, (String_View){.data = lexer->content.data, .count = 1}, .line = lexer->line};
        case '}':
            consume(lexer, '}');
            return (token_t){.type = TOKEN_RBRACE, (String_View){.data = lexer->content.data, .count = 1}, .line = lexer->line};
        case '"':
            consume(lexer, '"');
            return (token_t)(.type = TOKEN_STRING, parse_str(lexer), .line = lexer->line);
            break;
        case ':':
            consume(lexer , ':');
            return (token_t){.type = TOKEN_COLUMN, (String_View){.data = lexer->content.data, .count = 1}, .line = lexer->line};
        case '[':
            consume(lexer, '[');
            return (token_t){.type = TOKEN_LBRACKET, (String_View){.data = lexer->content.data, .count - 1}, .line = lexer->line};
        case ']':
            consume(lexer, ']');
            return (token_t){.type = TOKEN_RBRACKET, (String_View){.data = lexer->content.data, .count - 1}, .line = lexer->line};
        default: return (token_t){.type = TOKEN_INVALID, EMPTY_SV(), .line = lexer->line};
    }
}