#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timeDriver.h>
#include <registers.h>
#include <time.h>
#include <beeper.h>
#include <multitasking.h>
#include "memoryManager.h"
#include "pipes.h"
#include "semaphore.h"
#include <types.h>
#include <childProcess.h>

#define BACKGROUND 0
#define STDIN 1
#define STDOUT 1
#define STDERR 2

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_CLEAR 2
#define SYS_TIME 3
#define SYS_HOLDER 4
#define SYS_BEEP 5
#define SYS_INFO_REG 6
#define SYS_DRAW 7

#define SYS_ALLOC 8
#define SYS_FREE 9

#define SYS_DESTROY_PIPE 10
#define SYS_PIPE_INFO 11
#define SYS_READ_PIPE 12
#define SYS_REGISTER_PIPE_AVAILABLE 13
#define SYS_WRITE_PIPE 14

#define SYS_WAIT_SEM 15
#define SYS_SIGNAL_SEM 16
#define SYS_DESTROY_SEM 17
#define SYS_REGISTER_SEM 18
#define SYS_REGISTER_SEM_AVAILABLE 19

#define SYS_REGISTER_CHILD_PROCESS 20
#define SYS_WAIT_CHILDREN 21
#define SYS_GET_PID 22

#define SYS_REGISTER_PROCESS 23
#define SYS_PAUSE_PROCESS 24
#define SYS_KILL_PROCESS 25

#define SYS_NICE 26


void sys_write_to_screen(char *buffer, int row, int col, int color);
void sys_write(int fd, char *buffer, int row, int col, int color);
void sys_read(int fd, char *buffer, int length);
void sys_clear();
void sys_time();
void sys_holder(int time);
void sys_beep(uint32_t beepTime);
void sys_info_reg();
void sys_draw(int row, int col, int color);
void sys_alloc(uint64_t len);
void sys_free(void * ptr);
void sys_destroy_pipe(unsigned int pipeID);
void sys_pipe_info(pipesInfo * info);
void sys_read_pipe(unsigned int pipeID, char * dest, unsigned int count);
void sys_register_pipe_available();
void sys_register_pipe(unsigned int pipeID);
void sys_write_pipe(unsigned int pipeID, const char * src, unsigned int count);
void sys_wait_sem(unsigned int ID);
void sys_signal_sem(unsigned int ID);
void sys_destroy_sem(unsigned int ID);
void sys_register_sem(unsigned int ID, unsigned int value);
void sys_register_sem_available(unsigned int value);
void sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0);
void sys_wait_children();
void sys_get_pid();
void sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0);
void sys_pause_process(unsigned int pid);
void sys_kill_process(unsigned int pid);

#endif