#include <string.h>
#include <stdio.h>

#include "util.h"

#define STRSIZE 10
#define BAT "BAT0"
#define BAT_PERC "/sys/class/power_supply/BAT0/capacity"
#define BAT_STAT "/sys/class/power_supply/BAT0/status"

static char* chargeIcons[] = {"", "", "", "", "", "", ""};
static char* dischargeIcons[] = {"", "", "", "", "", "", "", "", "", ""};

unsigned int getBatPerc() {
    unsigned int ret;
    FILE* fp = fopen(BAT_PERC, "r");
    fscanf(fp, "%u", &ret);
    fclose(fp);
    return ret;
}

unsigned int getBatStat() {
    char status[15];
    FILE* fp = fopen(BAT_STAT, "r");
    fscanf(fp, "%s", status);
    fclose(fp);
    return (unsigned int) strcmp(status, "Charging");
}

void getBatStr(char *status, unsigned maxlen) {
  unsigned int batPerc = getBatPerc();
  unsigned int batStat = getBatStat();
  char *icon = batStat ? dischargeIcons[batPerc * 10 / 101]
                       : chargeIcons[batPerc * 7 / 101];

  sprintf(status, "%s %u%%", icon, batPerc);
}
