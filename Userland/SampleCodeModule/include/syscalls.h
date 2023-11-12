#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <date.h>
#include <types.h>
#include <stddef.h>

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

extern uint64_t _syscall(uint64_t syscall, ...);

void write(char *buffer, int row, int col, int color);
void read(int fd, char *buffer, int length);
void clearScreen();
void getTime(date currentDate);
void hold(int time);
void beep(uint32_t beepTime);
void getRegisters();
void putPixel(int row, int col, int color);
uint64_t freeMem(void * ptr);
uint64_t alloc(int len);
void destroyPipe( int pipeID);
uint64_t pipeInfo(pipesInfo * info);
uint64_t readPipe(int pipeID, char * dest, int count);
uint64_t registerPipeAvailable();
uint64_t writePipe(int pipeID, const char * src, int count);
uint64_t waitSemaphore(uint64_t semID);
uint64_t signalSemaphore(uint64_t semID);
uint64_t destroySemaphore(uint64_t semID);
uint64_t registerSemaphore(uint64_t semID, unsigned int value);
uint64_t registerSemaphoreAvailable(unsigned int value);
uint64_t registerChildProcess(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0);
uint64_t waitChildren();
uint64_t getPID();
uint64_t killProcess(unsigned int pid);
uint64_t pauseProcess(unsigned int pid);
uint64_t niceProcess(uint8_t pid, int delta);
#endif