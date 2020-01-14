#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define STRSIZE 10
#define PAMIXER "pamixer --get-volume-human"

static char* icon = "墳";

void getVolStr(char *status, unsigned maxlen) {
  char command[7];
  readCmd(command, 7, PAMIXER);

  if (!strcmp(command, "muted")) {
    sprintf(status, "%s %s", icon, "MUTE");
  } else {
    unsigned int vol;
    sscanf(command, "%u", &vol);
    sprintf(status, "%s %u%%", icon, vol);
  }
}
