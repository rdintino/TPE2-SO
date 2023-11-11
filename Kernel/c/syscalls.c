#include "../include/syscalls.h"

void sys_write_to_screen(char *buffer, int row, int col, int color){
    sys_write(1,buffer,row,col,color);
}

void sys_write(int fd, char *buffer, int row, int col, int color){
    switch (fd){
        case BACKGROUND:
        break;
        case STDERR:
            if(row == -1 || col == -1){
                print(buffer, RED);
            }else{
                printIn(buffer, row, col, RED);
            }
        break;
        case STDOUT:
            if(row == -1 || col == -1){
                print(buffer, color);
            }else{
                printIn(buffer, row, col, color);
            }
        break;
        default:
        writeToPipe(fd, buffer, strlen(buffer));
    }
}

void sys_read(int fd,char *buffer, int length){
    if(fd==STDIN){
        readKeyboard(buffer, length);
    }
    readFromPipe(fd,buffer,length);
}

void sys_clear(){
    clearScreen();
}

void sys_time(date currentDate){
    getDate(currentDate);
}

void sys_holder(int time){
    holder(time);
}

void sys_beep(uint32_t beepTime){
    beep(beepTime);
}

void sys_info_reg(){
    getRegistersState();
}

void sys_draw(int row, int col, int color){
    putPixel(row, col, color);
}

void sys_alloc(uint64_t len) {
	(uint64_t) mm_malloc(len);
}

void sys_destroy_pipe(unsigned int pipeID){
	destroyPipe(pipeID);
}

void sys_pipe_info(pipesInfo * info){
	getPipeInfo(info);
}

void sys_read_pipe(unsigned int pipeID, char * dest, unsigned int count){
	readFromPipe(pipeID, dest, count);
}

void sys_register_pipe_available(){
	createAvailablePipe();
}

void sys_register_pipe(unsigned int pipeID){
	createPipe(pipeID);
}

void sys_write_pipe(unsigned int pipeID, const char * src, unsigned int count){
	writeToPipe(pipeID, src, count);
}

void sys_wait_sem(unsigned int ID){
    waitSemaphore(ID);
}

void sys_signal_sem(unsigned int ID){
    signalSemaphore(ID);
}

void sys_destroy_sem(unsigned int ID){
    destroySemaphore(ID);
}

void sys_register_sem(unsigned int ID, unsigned int value){
    createSemaphore(ID, value);
}

void sys_register_sem_available(unsigned int value){
    makeSemaphoreAvailable(value);
}

void sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0){
    addChildTask(entryPoint, input, output, arg0);
}

void sys_wait_children(){
    waitChildren();
}

void sys_get_pid(){
    getCurrentPID();
}

void sys_pause_process(unsigned int pid){
    pauseOrUnpauseProcess(pid);
}

void sys_kill_process(unsigned int pid){
    removeTask(pid);
}