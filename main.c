#include <stdio.h>
#include "sv.h"


int main() {
    String_View s = sv("Hello, World");
    printf(SvFmt"\n", SvArg(s));
    return 0;
}

