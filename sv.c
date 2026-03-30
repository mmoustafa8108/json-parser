#include <string.h>
#include <ctype.h>
#include "sv.h"

String_View sv(const char* cstr) {
    if (!cstr) return (String_View) {.data = NULL, .count = 0};
    return (String_View) {
	    .data = cstr,
	    .count = strlen(cstr),
        };
}

void sv_chop_left(String_View* sv, size_t n) {
    if (n > sv->count) n = sv->count;
    sv->count -= n;
    sv->data += n;
}

void sv_chop_right(String_View* sv, size_t n) {
    if (n > sv->count) n = sv->count;
    sv->count -= n;
}

void sv_trim_right(String_View* sv) {
    while (sv->count > 0 && isspace(sv->data[sv->count-1])) {
        sv_chop_right(sv, 1);
    }
}

void sv_trim_left(String_View* sv) {
    while (sv->count > 0 && isspace(*sv->data)) {
        sv_chop_left(sv, 1);
    }
}

String_View sv_chop_by_delim(String_View* sv, char delim) {
    size_t i = 0;
    while (i < sv->count && sv->data[i] != delim) i++;

    if (i == sv->count) {
        String_View result = *sv;
	    sv_chop_left(sv, sv->count);
	    return result;
    } else {
	String_View result = {.data = sv->data, .count = i};
	sv_chop_left(sv, i + 1);
	return result;
    }
}

String_View sv_chop_by_type(String_View* sv, int(*istype)(int c)) {
    size_t i = 0;
    while (i < sv->count && !istype(sv->data[i])) i++;

    if (i == sv->count) {
        String_View result = *sv;
	    sv_chop_left(sv, sv->count);
	    return result;
    } else {
	String_View result = {.data = sv->data, .count = i};
	sv_chop_left(sv, i + 1);
	return result;
    } 
}
