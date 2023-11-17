
#include "../include/syscalls.h"
#include "../include/testUtils.h"
#include "../include/shell.h"

enum State { RUNNING,
             BLOCKED,
             KILLED };

typedef struct P_rq {
  int32_t pid;
  enum State state;
} p_rq;

void testProcesses(char *argv[]){
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t maxProcesses;
  char * auxArgs[] = {0};

  maxProcesses = satoi(argv[1]);
  if ( maxProcesses <= 0){
    return;
  }

  p_rq p_rqs[maxProcesses];
printf("testProcesses: Creating ");
println(int64ToString(maxProcesses));

  while (1) {

    // Create processes
    for (rq = 0; rq < maxProcesses; rq++) {
        p_rqs[rq].pid = registerChildProcess((uint64_t)&endlessLoop, 1, 1, (uint64_t) auxArgs);

      if (p_rqs[rq].pid == -1) {
        printf("testProcesses: Error creating process\n");
        return;
      } else {
        p_rqs[rq].state = RUNNING;
        alive++;
      }
    }

    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0) {

      for (rq = 0; rq < maxProcesses; rq++) {
        action = getUniform(100) % 2;
        switch (action) {
          case 0:
            if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == BLOCKED) {
              if (killProcess(p_rqs[rq].pid) == -1) {
                printf("test_processes: Error killing process\n");
                return;
              } 
              p_rqs[rq].state = KILLED;
              alive--;
            }
            break;

          case 1:
            if (p_rqs[rq].state == RUNNING) {
              if (pauseProcess(p_rqs[rq].pid) == -1) {
                printf("test_processes: Error blocking process\n");
                return;
              } 
              p_rqs[rq].state = BLOCKED;
            }
            break;
        }
      }

      // Randomly unblocks processes
      for (rq = 0; rq < maxProcesses; rq++)
        if (p_rqs[rq].state == BLOCKED && getUniform(100) % 2) {
          if (pauseProcess(p_rqs[rq].pid) == -1) {
            printf("test_processes: Error unblocking process\n");
            return;
          }
          p_rqs[rq].state = RUNNING;
        }
    }
  }
}