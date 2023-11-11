#include "../include/syscalls.h"

void write(char *buffer, int row, int col, int color){
    _syscall(SYS_WRITE, buffer, row, col, color);
}

void read(int fd,char *buffer, int length){
    _syscall(SYS_READ, fd, buffer, length);
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

void destroyPipe( int pipeID){
    _syscall(SYS_DESTROY_PIPE, pipeID);
}

uint64_t pipeInfo(pipesInfo * info){
    return _syscall(SYS_PIPE_INFO, info);
}

uint64_t readPipe(int pipeID, char * dest, int count){
    return _syscall(SYS_READ_PIPE, pipeID, dest, count);
}

uint64_t registerPipeAvailable(){
    return _syscall(SYS_REGISTER_PIPE_AVAILABLE);
}

uint64_t writePipe(int pipeID, const char * src, int count){
    return _syscall(SYS_WRITE_PIPE, pipeID, src, count);
}

uint64_t waitSemaphore(uint64_t semID){
    return _syscall(SYS_WAIT_SEM, semID);
}

uint64_t signalSemaphore(uint64_t semID){
    return _syscall(SYS_SIGNAL_SEM, semID);
}

uint64_t destroySemaphore(uint64_t semID){
    return _syscall(SYS_DESTROY_SEM, semID);
}

uint64_t registerSemaphore(uint64_t semID, unsigned int value){
    return _syscall(SYS_REGISTER_SEM, semID, value);
}

uint64_t registerSemaphoreAvailable(unsigned int value){
    return _syscall(SYS_REGISTER_SEM_AVAILABLE, value);
}

uint64_t registerChildProcess(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0){
    return _syscall(SYS_REGISTER_CHILD_PROCESS, entryPoint, input, output, arg0);
}

uint64_t waitChildren(){
    return _syscall(SYS_WAIT_CHILDREN);
}

uint64_t getPID(){
    return _syscall(SYS_GET_PID);
}

uint64_t pauseProcess(unsigned int pid){
    return _syscall(SYS_PAUSE_PROCESS,(uint64_t) pid,NULL,NULL, NULL );
}

uint64_t killProcess(unsigned int pid){
    return _syscall(SYS_KILL_PROCESS,(uint64_t) pid, NULL,NULL, NULL );
}