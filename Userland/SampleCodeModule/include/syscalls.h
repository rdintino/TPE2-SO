#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <date.h>
#include "data_types.h"

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_CLEAR 2
#define SYS_TIME 3
#define SYS_HOLDER 4
#define SYS_BEEP 5
#define SYS_INFO_REG 6
#define SYS_DRAW 7

#define SYS_ALLOC 8
#define SYS_DESTROY_PIPE 9
#define SYS_PIPE_INFO 10
#define SYS_READ_PIPE 11
#define SYS_REGISTER_PIPE_AVAILABLE 12
#define SYS_WRITE_PIPE 13

extern uint64_t _syscall(uint64_t syscall, ...);

void write(char *string, int row, int col, int color);
void read(char *buffer, int length);
void clearScreen();
void getTime(date currentDate);
void hold(int time);
void beep(uint32_t beepTime);
void getRegisters();
void putPixel(int row, int col, int color);

uint64_t alloc(int len);
void destroy_pipe( int pipe_id);
uint64_t pipe_info(pipes_info * info);
uint64_t read_pipe(int pipe_id, char * dest, int count);
uint64_t register_pipe_available();
uint64_t write_pipe(int pipe_id, const char * src, int count);

#endif