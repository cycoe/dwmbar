#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define STRSIZE 10
#define BACKLIGHT "/sys/class/backlight/amdgpu_bl0/brightness"
#define BACKLIGHT_MAX "/sys/class/backlight/amdgpu_bl0/max_brightness"

static char* icon = "";

unsigned int getBacklight() {
    unsigned int ret;
    FILE* fp = fopen(BACKLIGHT, "r");
    fscanf(fp, "%u", &ret);
    fclose(fp);
    return ret;
}

unsigned int getBacklightMax() {
    unsigned int ret;
    FILE* fp = fopen(BACKLIGHT_MAX, "r");
    fscanf(fp, "%u", &ret);
    fclose(fp);
    return ret;
}

void getBLStr(char *status, unsigned maxlen) {
  int perc = getBacklight() * 100 / getBacklightMax();
  sprintf(status, "%s %d%%", icon, perc);
}
