#include <testSync.h>

void slowInc(int64_t *p, int64_t inc) {
  int aux;
  aux = *p;
  aux += inc;
  for(int i = 0; i < 30000 ; i++) 
    ;
  *p = aux;
}

uint64_t myProcessInc(uint64_t argc, char *argv[]) {
  int inc = 1;

  int i;
  for (i = 0; i < MAX; i++) {
    if (argv[1][0] == 's') {
      waitSemaphore(SEM_ID);
    }
    slowInc(&global, inc);
    if (argv[1][0] == 's') {
      signalSemaphore(SEM_ID);
    }
  }
}

uint64_t testSync(uint64_t argc, char *argv[]) { //{n, use_sem, 0}
 int semUse = satoi(argv[1]);
  if(semUse) {
    destroySemaphore(SEM_ID);
    if (registerSemaphore(SEM_ID, 1) != 0) {
      printf("test_sync: ERROR opening semaphore\n");
      return -1;
    }
  }

  char *args[] = {"sem", NULL, NULL};

  global = 0;

  if(semUse) {
    args[1] = "s";
  }

  int i;
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    int error = registerChildProcess((uint64_t)&myProcessInc, STDIN, BACKGROUND, (uint64_t) args);
    if (error <= 0 ) {
      printf("Error creating children");
    }
  }

  waitChildren();

  if(semUse) {
    destroySemaphore(SEM_ID);
  }

  printf("Global expected value: %d. Global final value: %d\n", MAX * TOTAL_PAIR_PROCESSES, global);
  char * expectedValue = int64ToString(MAX * TOTAL_PAIR_PROCESSES);
  printf(expectedValue + '\n');
  printf("Global final value:");
  char * finalValue = int64ToString(global);
  printf(finalValue + '\n');

  return 0;
}