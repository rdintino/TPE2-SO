#include "../include/syscalls.h"

void sys_write_to_screen(char *buffer, int row, int col, int color){
    sys_write(getCurrentOutput(),buffer,row,col,color);
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

uint64_t sys_alloc(uint64_t len) {
	return (uint64_t) mm_malloc(len);
}

void sys_free(void * ptr) {
	mm_free(ptr);
}

uint64_t sys_mm_status(uint64_t * buffer) {
	printMemStatus(buffer);
	return 1;
}

unsigned int sys_print_mem(uint64_t pos, char * buffer) {
   	if( !(pos >= MIN_MEM_POS && pos < MAX_MEM_POS) ){
		return INVALID_MEM_POS;
    }
	uint64_t current;
	
	for(int i = 0, j = 0; i < MAX_MEM_READ; i++) {
		if(i != 0 && i % 4 == 0) {
			buffer[j++] = ' ';
    }
    current = *((uint8_t * ) pos + i);
    j += hexToString(current, buffer + j, BYTE_LENGTH);
	}
	return 0;
}

uint64_t sys_register_pipe(unsigned int pipeID){
	return createPipe(pipeID);
}

uint64_t sys_register_pipe_available(){
	return createAvailablePipe();
}

uint64_t sys_read_pipe(unsigned int pipeID, char * dest, unsigned int count){
	return readFromPipe(pipeID, dest, count);
}

uint64_t sys_write_pipe(unsigned int pipeID, const char * src, unsigned int count){
	return writeToPipe(pipeID, src, count);
}

uint64_t sys_pipe_info(pipesInfo * info){
	return getPipeInfo(info);
}

void sys_destroy_pipe(unsigned int pipeID){
	destroyPipe(pipeID);
}

uint64_t sys_register_sem(unsigned int ID, unsigned int value){
    return createSemaphore(ID, value);
}

uint64_t sys_register_sem_available(unsigned int value){
    return makeSemaphoreAvailable(value);
}

uint64_t sys_wait_sem(unsigned int ID){
    return waitSemaphore(ID);
}

uint64_t sys_signal_sem(unsigned int ID){
    return signalSemaphore(ID);
}

uint64_t sys_semaphore_info(semaphoreInfo * info){
    return getSemaphoreInfo(info);
}

void sys_destroy_sem(unsigned int ID){
    destroySemaphore(ID);
}

uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0){
    return addChildTask(entryPoint, input, output, arg0);
}

void sys_wait_children(){
    waitChildren();
}

uint64_t sys_get_pid(){
    return getCurrentPID();
}

uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0){
	return addTask(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL, arg0);
}

uint64_t sys_process_alive(unsigned int PID){
    return findTask(PID) != NO_TASK_FOUND;
}

uint64_t sys_pause_process(unsigned int PID){
    return pauseOrUnpauseProcess(PID);
}

uint64_t sys_process_info(processInfo * info){
    return getProcessInfo(info);
}

uint64_t sys_kill_process(unsigned int PID){
    return removeTask(PID);
}

 uint64_t sys_nice(uint8_t PID, int delta){
	return changePriority(PID, delta);
}

void sys_renounce_cpu(){
    forceChangeTask();
}


