#include "../include/syscalls.h"

void write(char *string, int row, int col, int color){
    _syscall(SYS_WRITE, string, row, col, color);
}

void read(char *buffer, int length){
    _syscall(SYS_READ, buffer, length);
}

void clearScreen(){
    _syscall(SYS_CLEAR);
}

void getTime(date currentDate){
    _syscall(SYS_TIME, currentDate);
}

void hold(int time){
    _syscall(SYS_HOLDER, time);
}

void beep(uint32_t beepTime){
    _syscall(SYS_BEEP, beepTime);
}

void getRegisters(){
    _syscall(SYS_INFO_REG);
}

void putPixel(int row, int col, int color){
    _syscall(SYS_DRAW, row, col, color);
}

uint64_t alloc(int len){
    return _syscall(SYS_ALLOC,len);
}

void destroy_pipe( int pipe_id){
    _syscall(SYS_DESTROY_PIPE,pipe_id);
}

uint64_t pipe_info(pipes_info * info){
    return _syscall(SYS_PIPE_INFO,info);
}

uint64_t read_pipe(int pipe_id, char * dest, int count){
    return _syscall(SYS_READ_PIPE,pipe_id,dest,count);
}

uint64_t register_pipe_available(){
    return _syscall(SYS_REGISTER_PIPE_AVAILABLE);
}

uint64_t write_pipe(int pipe_id, const char * src, int count){
    return _syscall(SYS_WRITE_PIPE,pipe_id,src,count);
}
