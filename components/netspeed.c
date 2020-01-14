#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "util.h"

#define STRSIZE 15
#define NET "/proc/net/dev"

static char* icon = "";

float getBytes() {
    float bytes;
    char dev[20];
    char tmp[1024];
    FILE* fp = fopen(NET, "r");
    fgets(tmp, sizeof(tmp), fp);
    fgets(tmp, sizeof(tmp), fp);
    fgets(tmp, sizeof(tmp), fp);

    while (!match(tmp, "")) {
        if (match(tmp, "wlp110s0"))
            break;
        fgets(tmp, sizeof(tmp), fp);
    }
    fclose(fp);

    int i = 0;
    int spaceCount = 0;
    while (tmp[i] != '\0') {
        if (tmp[i] == ' ') {
            if (spaceCount == 1) {
                tmp[i] = '\0';
                break;
            }
            else {
                spaceCount++;
            }
        }
        i++;
    }

    sscanf(tmp, "%s %f", dev, &bytes);
    return bytes;
}

void getSpeedStr(char *status, unsigned maxlen) {
  float bytes1 = getBytes();
  sleep(2);
  float bytes2 = getBytes();
  char bytesStr[15];
  human(bytesStr, (bytes2 - bytes1));

  sprintf(status, "%s %s/s", icon, bytesStr);
}
