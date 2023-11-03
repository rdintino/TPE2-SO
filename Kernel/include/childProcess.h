#ifndef CHILDPROCESS_H
#define CHILDPROCESS_H

#include <multitasking.h>
#include <interrupts.h>
#include <syscalls.h>

#define MAX_WAIT_TASKS 30

#define NOT_TRACKING 0	// space is empty and ready to use
#define RUNNING 1
#define FINISHED 2

typedef struct waitData{
	unsigned int fatherPID;
	unsigned int childPID;
	uint8_t state;
} waitData;


static waitData taskList[MAX_WAIT_TASKS] = {{0}};	

uint8_t hasChildren(unsigned int PID);
void signalFinished(unsigned int PID);
uint8_t childrenFinished(unsigned int PID);
void removeChildren(unsigned int PID);
void addChild(unsigned int fatherPID, unsigned int childPID);
void waitChildren();
unsigned int addChildTask(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0);

#endif