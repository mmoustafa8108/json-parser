#include <stdio.h>
#include "sv.h"


int main() {
    String_View s = sv("       Hello, World         ");
    printf("|"SvFmt"|\n", SvArg(s));
    sv_trim_right(&s);
    printf("|"SvFmt"|\n", SvArg(s));
    sv_trim_left(&s);
    printf("|"SvFmt"|\n", SvArg(s));
    return 0;
}

