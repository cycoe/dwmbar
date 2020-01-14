#include <time.h>
#include <stdio.h>

#define STRSIZE 30

static char* MONTH[] = {
    "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
    "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
};
static char* WEEKDAY[] = {
    "Sun.", "Mon.", "Tue.", "Wed.", "Thur.", "Fri.", "Sat."
};

void getTimeStr(char *status, unsigned maxlen) {
  time_t t;
  struct tm *lt;
  time(&t);           //获取Unix时间戳。
  lt = localtime(&t); //转为时间结构。

  sprintf(status, "%s %d (%s) %02d:%02d:%02d", MONTH[lt->tm_mon], lt->tm_mday,
          WEEKDAY[lt->tm_wday], lt->tm_hour, lt->tm_min, lt->tm_sec);
}
