#include "../include/pipes.h"
#include "../include/types.h"

#define MAX_PIPES 20
#define PIPE_SIZE 1024

static pipe_record pipe_info[MAX_PIPES];
static unsigned int num_pipes = 0;

int create_pipe(unsigned int pipe_id){
	if(pipe_id == 0)				
		return INVALID_PIPE_ID;
	if(num_pipes == MAX_PIPES)
		return -1;

	int freePos = -1;
	for(int i=0; i<MAX_PIPES && freePos==-1; i++){
		if(freePos == -1 && pipe_info[i].pipe_id == 0){
			freePos = i;
		}
		if(pipe_info[i].pipe_id == pipe_id){
			return -1;
		}
	}

	pipe_info[freePos].pipe = mm_malloc(PIPE_SIZE);
	if(pipe_info[freePos].pipe == NULL){
		return -1;
	}
	pipe_info[freePos].pipe_id = pipe_id;
	pipe_info[freePos].read_sem_id  = 0;//semaphore
	pipe_info[freePos].write_sem_id  = 0; //semaphore
	pipe_info[freePos].write_pos = 0;
	pipe_info[freePos].read_pos = 0;
	pipe_info[freePos].amount = 0;
	pipe_info[freePos].eof = 0;

	num_pipes++;
	return 1;
}

uint64_t get_pipe_info(pipes_info * info){
	int j = 0;
	for(int i=0; i<MAX_PIPES; i++){
		if(pipe_info[i].pipe_id != 0){
			info[j].id = pipe_info[i].pipe_id;
			info[j].usage = pipe_info[i].amount;
			j++;
		}
	}
	return j;
}

int find_pipe(unsigned int pipe_id){
	for(int i=0; i<MAX_PIPES; i++){
		if(pipe_info[i].pipe_id == pipe_id){
			return i;
		}
	}
	return -1;
}

int find_available_pipe_id(){
	if(num_pipes == MAX_PIPES)
		return -1;

	uint8_t found = false;
	int pipe_id = 0;

	while(!found){
		found = true;
		for(int i=0; i<MAX_PIPES; i++){
			if(pipe_info[i].pipe_id == pipe_id){
				found = false;
				pipe_id++;
				break;
			}
		}
	}
	return pipe_id;
}

int create_pipe_available(){
	int id = find_available_pipe_id();

	if(id == -1){
		return -1;
	}

	if( create_pipe(id) != 1){
		return -1;
	}
	return id;
}




