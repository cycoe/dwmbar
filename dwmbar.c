#include <X11/Xlib.h>
#include <malloc.h>
#include <memory.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "components/util.h"
#include "components/dateTime.h"
#include "components/battery.h"
#include "components/volume.h"
#include "components/backlight.h"
#include "components/memory.h"
#include "components/netspeed.h"
#include "components/thermal.h"

// Some usable macros
#define NUL 0
#define SIGINT 2

// Global settings
#define LEN_ITEM 32
#define NUM_ITEM 7
#define LEN_STATUS 256
#define SLEEP 5

/* Global varibles
 */
Display *dpy;
Window window;
char string[LEN_STATUS] = {NUL};
char status[NUM_ITEM][LEN_ITEM] = {"Net",    "Thermal", "Memory", "Light",
                                   "Volume", "Battery", "Time"};
char *pstatus[NUM_ITEM] = {NULL};

// flush X store name
void flush(int signum) {
  stringJoin(string, 200, pstatus, 7);

  // Set X11 store name and flush
  XStoreName(dpy, window, string);
  XFlush(dpy);
}

void getSpeedStrWrap(void *argv) {
  getSpeedStr(status[0], LEN_ITEM);
  flush(2);
}

void update() {
  /* Use a child thread to process network speed monitor
   * The network speed monitor thread will block main thread
   */
  pthread_t tid;
  pthread_create(&tid, NULL, (void *)getSpeedStrWrap, NULL);

  while (1) {
    // Update status array
    getMemoStr(status[2], LEN_ITEM);
    getBLStr(status[3], LEN_ITEM);
    getVolStr(status[4], LEN_ITEM);
    getBatStr(status[5], LEN_ITEM);
    getTimeStr(status[6], LEN_ITEM);

    // flush X11 store name
    flush(SIGINT);
    // listen to the SIGINT signal from other process
    signal(2, flush);
    // loop sleep for cycle
    sleep(SLEEP);
  }
  pthread_join(tid, NULL);
}

int main(int argc, char *argv[]) {
  // Get X11 window
  if (!(dpy = XOpenDisplay(NULL)))
    fprintf(stderr, "[Error] Open display failed!\n");
  window = XDefaultRootWindow(dpy);

  // Bind status array to the status pointer array
  for (int i = 0; i < NUM_ITEM; i++) {
    pstatus[i] = status[i];
  }

  // Update status
  update();
  return 0;
}
