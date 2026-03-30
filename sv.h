#ifndef STR_VIEW_H
#define STR_VIEW_H

#define SvFmt "%.*s"
#define SvArg(s) (s).count, (s).data

typedef struct {
    const char* data;
    size_t count;
} String_View;

String_View sv(const char* cstr);
void sv_chop_left(String_View* sv, size_t n);
void sv_chop_right(String_View* sv, size_t n);
void sv_trim_right(String_View* sv);
void sv_trim_left(String_View* sv);
void sv_trim(String_View* sv);
String_View sv_chop_by_delim(String_View* sv, char delim);
String_View sv_chop_by_type(String_View* sv, int (*istype)(int c));

#endif
