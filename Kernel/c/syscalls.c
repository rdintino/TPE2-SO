#include "../include/syscalls.h"
#include "../include/multitasking.h"
#include "../include/memoryManager.h"
#include "../include/pipes.h"
#include "../include/semaphore.h"

void sys_write(char * string, int row, int col, int color){
    if(row == -1 || col == -1){
        print(string, color);
    }
    else{
        printIn(string, row, col, color);
    }
}

void sys_read(char *buffer, int length){
    readKeyboard(buffer, length);
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

uint64_t sysAlloc(uint64_t len) {
	return (uint64_t) mm_malloc(len);
}

uint64_t sysNais(uint8_t pid, int delta){
	return change_priority(pid, delta);
}

uint64_t sysDestroyPipe(unsigned int pipe_id){
	destroy_pipe(pipe_id);
	return 1;
}

uint64_t sysDestroySem(unsigned int sem_id){
	destroy_sem(sem_id);
	return 1;
}

uint64_t sysFree(void * ptr) {
	mm_free(ptr);
	return 1;	
}

uint64_t sysGetPid(){
	return get_current_pid();
}

uint64_t sysKillProcess(unsigned int pid) {
	return removeTask(pid);
}

uint64_t sysMmStatus(uint64_t * buffer){
	printMemStatus(buffer);
	return 1;
}

uint64_t sysPauseProcess(unsigned int pid) {
	return pauseOrUnpauseProcess(pid);
}

uint64_t sysPipeInfo(pipes_info * info){
	return get_pipe_info(info);
}

uint64_t sysProcessAlive(unsigned int pid){
	return findTask(pid) != NO_TASK_FOUND;
}

uint64_t sysProcessInfo(process_info * info){
	return get_process_info(info);
}

uint64_t sysReadPipe(unsigned int pipe_id, char * dest, unsigned int count){
	return read_from_pipe(pipe_id, dest, count);
}

uint64_t sysRegisterChildProcess(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0){
	return add_child_task(entryPoint, input, output, arg0);
}

uint64_t sysRegisterPipeAvailable(){
	return create_pipe_available();
}

uint64_t sysRegisterProcess(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0){
	return add_task(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL, arg0);
}

uint64_t sysRegisterSem(unsigned int sem_id, unsigned int value){
	return create_sem(sem_id, value);
}

uint64_t sysRegisterSemAvailable(unsigned int value){
	return create_sem_available(value);
}

uint64_t sysRenounceCpu(){
	forceChangeTask();
	return 1;
}

uint64_t sysSemaphoreInfo(semaphore_info * info){
	return get_semaphore_info(info);
}

uint64_t sysSignalSem(unsigned int sem_id){
	return signal_sem(sem_id);
}

uint64_t sysWaitForChildren(){
	wait_for_children();
	return 1;
}

uint64_t sysWaitSem(unsigned int sem_id){
	return wait_sem(sem_id);
}

uint64_t sysWritePipe(unsigned int pipe_id, const char * src, unsigned int count){
	return write_to_pipe(pipe_id, src, count);
}