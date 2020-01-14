#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>

#define STRSIZE 10
#define THERMAL "/sys/class/thermal/thermal_zone0/temp"

static char* icon = "﨎";

unsigned int getThermal() {
    unsigned int thermal;
    FILE* fp = fopen(THERMAL, "r");
    fscanf(fp, "%u", &thermal);
    fclose(fp);
    return thermal;
}

char* getTherStr() {
    char* ret = (char*) calloc(STRSIZE, sizeof(char));
    sprintf(ret, "%s %uC", icon, getThermal() / 1000);
    return ret;
}
