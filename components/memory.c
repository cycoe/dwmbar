#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define STRSIZE 12
#define MEMORY "/proc/meminfo"

static char* icon = "";

typedef struct //定义一个mem occupy的结构体
{
  float total;
  char totalUnit[4];
  float avail;
  char availUnit[4];
} MEM_STRUCT;


float getMemory(MEM_STRUCT* mem) {
    char buff[64];
    char tmp[20];
    FILE* fp = fopen(MEMORY, "r");
    fgets(buff, sizeof(buff), fp);
    // 此处使用 float 型是为防止数字太大溢出
    sscanf(buff, "%s %f %s", tmp, &mem->total, mem->totalUnit);
    // skip tow lines
    fgets(buff, sizeof(buff), fp);
    fgets(buff, sizeof(buff), fp);
    sscanf(buff, "%s %f %s", tmp, &mem->avail, mem->availUnit);
    fclose(fp);
    return antiHuman(mem->total, mem->totalUnit) - antiHuman(mem->avail, mem->availUnit);
}

void getMemoStr(char *string, unsigned maxlen) {
  MEM_STRUCT mem;
  char memString[10];
  human(memString, getMemory(&mem));

  sprintf(string, "%s %s", icon, memString);
}
