#include <syscalls.h>

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

uint64_t sysDestroyPipe(unsigned int pipe_id){
	destroy_pipe(pipe_id);
	return 1;
}

uint64_t sysPipeInfo(pipes_info * info){
	return get_pipe_info(info);
}

uint64_t sysReadPipe(unsigned int pipe_id, char * dest, unsigned int count){
	return read_from_pipe(pipe_id, dest, count);
}

uint64_t sysRegisterPipeAvailable(){
	return create_pipe_available();
}

uint64_t sysRegisterPipe(unsigned int pipe_id){
	return create_pipe(pipe_id);
}

uint64_t sysWritePipe(unsigned int pipe_id, const char * src, unsigned int count){
	return write_to_pipe(pipe_id, src, count);
}



