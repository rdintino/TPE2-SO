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
#include <memoryManager.h>
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
#define SYS_MM_STATUS 10
#define SYS_PRINT_MEM 11

#define SYS_REGISTER_PIPE 12
#define SYS_REGISTER_PIPE_AVAILABLE 13
#define SYS_READ_PIPE 14
#define SYS_WRITE_PIPE 15
#define SYS_PIPE_INFO 16
#define SYS_DESTROY_PIPE 17

#define SYS_REGISTER_SEM 18
#define SYS_REGISTER_SEM_AVAILABLE 19
#define SYS_WAIT_SEM 20
#define SYS_SIGNAL_SEM 21
#define SYS_SEMAPHORE_INFO 22
#define SYS_DESTROY_SEM 23

#define SYS_REGISTER_CHILD_PROCESS 24
#define SYS_WAIT_CHILDREN 25
#define SYS_GET_PID 26

#define SYS_REGISTER_PROCESS 27
#define SYS_PROCESS_ALIVE 28
#define SYS_PAUSE_PROCESS 29
#define SYS_PROCESS_INFO 30
#define SYS_KILL_PROCESS 31

#define SYS_NICE 32
#define SYS_RENOUNCE_CPU 33

#define MAX_MEM_POS 0x7FFFFFFFF		
#define MIN_MEM_POS 0x400000
#define INVALID_MEM_POS -1
#define MAX_MEM_READ 16
#define BYTE_LENGTH 2

// void sys_write_to_screen(char *buffer, int row, int col, int color);
// void sys_write(int fd, char *buffer, int row, int col, int color);
// void sys_read(int fd, char *buffer, int length);
// void sys_clear();
// void sys_time();
// void sys_holder(int time);
// void sys_beep(uint32_t beepTime);
// void sys_info_reg();
// void sys_draw(int row, int col, int color);
// uint64_t sys_alloc(uint64_t len);
// void sys_free(void * ptr);
// void sys_destroy_pipe(unsigned int pipeID);
// uint64_t sys_pipe_info(pipesInfo * info);
// uint64_t sys_read_pipe(unsigned int pipeID, char * dest, unsigned int count);
// uint64_t sys_register_pipe_available();
// uint64_t sys_register_pipe(unsigned int pipeID);
// uint64_t sys_write_pipe(unsigned int pipeID, const char * src, unsigned int count);
// uint64_t sys_wait_sem(unsigned int ID);
// uint64_t sys_signal_sem(unsigned int ID);
// void sys_destroy_sem(unsigned int ID);
// uint64_t sys_register_sem(unsigned int ID, unsigned int value);
// uint64_t sys_register_sem_available(unsigned int value);
// uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0);
// void sys_wait_children();
// uint64_t sys_get_pid();
// uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0);
// uint64_t sys_pause_process(unsigned int pid);
// uint64_t sys_kill_process(unsigned int pid);
// uint64_t sys_nice(uint8_t pid, int delta);
void sys_write_to_screen(char *buffer, int row, int col, int color);
void sys_write(int fd, char *buffer, int row, int col, int color);
void sys_read(int fd,char *buffer, int length);
void sys_clear();
void sys_time(date currentDate);
void sys_holder(int time);
void sys_beep(uint32_t beepTime);
void sys_info_reg();
void sys_draw(int row, int col, int color);
uint64_t sys_alloc(uint64_t len);
void sys_free(void * ptr);
uint64_t sys_mm_status(uint64_t * buffer) ;
unsigned int sys_print_mem(uint64_t pos, char * buffer);
uint64_t sys_register_pipe(unsigned int pipeID);
uint64_t sys_register_pipe_available();
uint64_t sys_read_pipe(unsigned int pipeID, char * dest, unsigned int count);
uint64_t sys_write_pipe(unsigned int pipeID, const char * src, unsigned int count);
uint64_t sys_pipe_info(pipesInfo * info);
void sys_destroy_pipe(unsigned int pipeID);
uint64_t sys_register_sem(unsigned int ID, unsigned int value);
uint64_t sys_register_sem_available(unsigned int value);
uint64_t sys_wait_sem(unsigned int ID);
uint64_t sys_signal_sem(unsigned int ID);
uint64_t sys_semaphore_info(semaphoreInfo * info);
void sys_destroy_sem(unsigned int ID);
uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0);
void sys_wait_children();
uint64_t sys_get_pid();
uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0);
uint64_t sys_process_alive(unsigned int PID);
uint64_t sys_pause_process(unsigned int PID);
uint64_t sys_process_info(processInfo * info);
uint64_t sys_kill_process(unsigned int PID);
uint64_t sys_nice(uint8_t PID, int delta);
void sys_renounce_cpu();
#endif