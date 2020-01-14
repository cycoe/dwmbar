#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <regex.h>
#include <malloc.h>

#include "util.h"

static char* UNIT[] = {"B", "KB", "MB", "GB", "TB"};
static char* UNIT_[] = {"B", "kB", "mB", "gB", "tB"};

int readCmd(char* ret, int len, char* command) {
    FILE* pipe = popen(command, "r");
    if (!pipe)
        return -1;

    fgets(ret, len, pipe);
    pclose(pipe);

    for (int i = 0; i < sizeof(ret); i++)
        if (ret[i] == '\n') {
            ret[i] = '\0';
            break;
        }
    return 0;
}

void stringJoin(char* ret, int len, char** strings, int size) {
    char* tmp = NULL;
    int i = 0;
    int j = 0;
    int loop = 0;
    for (loop = 0; loop < size; loop++) {
        tmp = strings[loop];
        if (j) {
            ret[j++] = '|';
        }

        i = 0;
        while (tmp[i] != '\0') {
            ret[j++] = tmp[i++];
            if (j >= len - 1)
                break;
        }
    }
    ret[j] = '\0';
}

int min(int a,  int b) {
    return a > b? b: a;
}

unsigned power(unsigned long x, int p) {
    unsigned long ret = 1;
    while (p-- > 0) {
        ret *= x;
    }
    return ret;
}

float antiHuman(float num, char* unit) {
    int i = 0;
    for (; i < sizeof(UNIT_) / 8; i++) {
        if (strcmp(unit, UNIT_[i]))
            num *= 0x400;
        else
            break;
    }

    return num;
}

char* human(char* ret, float num) {
    int i = 0;
    for (; num >= 0x400; i++) {
        num /= 0x400;
    }

    sprintf(ret, "%.1f%s", num, UNIT[i]);
    return ret;
}

int match(char *_string, char *_pattern) {
    /* return: 1, match; 0, not; -1, error */
    int rv = 0;
    regex_t *p_re = NULL;
    char buf[256] = {0};

    p_re = calloc(1, sizeof(regex_t));
    if (p_re == NULL)
    {
        //printf("error: calloc: %d\n", errno);
        rv = -1;
        goto _end;
    }

    rv = regcomp(p_re, _pattern, REG_EXTENDED|REG_NOSUB);
    if (rv != 0)
    {
        (void)regerror(rv, p_re, buf, sizeof buf);
        printf("error: regcomp: %s\n",buf);
        goto _end;
    }

    rv = regexec(p_re, _string, (size_t)0, NULL, 0);
    regfree(p_re);
    if (rv != 0)
    {
        (void)regerror(rv, p_re, buf, sizeof buf);
        printf("regexec: %s, [%d],[%s]\n", buf, rv, _pattern);
        goto _end;
    }

    rv = 1;

_end:
    if (p_re != NULL)
    {
        free(p_re);
    }

    return rv;
}
