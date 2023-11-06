#ifndef _PIPES_H_
#define _PIPES_H_

#include "../include/memoryManager.h"
#include <stdint.h>
#include <stdbool.h>

#define INVALID_PIPE_ID -1
#define EOF -1


typedef struct pipe_record{
	unsigned int pipe_id;

	int read_sem_id;
	int write_sem_id;

	unsigned int write_pos;
	unsigned int read_pos;
	uint8_t * pipe;
	unsigned int amount;

	uint8_t eof;
}pipe_record;

uint64_t get_pipe_info(pipes_info * info);

int create_pipe_available();
int create_pipe(unsigned int pipe_id);

void destroy_pipe(unsigned int pipe_id);
int read_from_pipe(unsigned int pipe_id, char * dest, unsigned int count);
int write_to_pipe(unsigned int pipe_id, const char * src, unsigned int count);



#endif