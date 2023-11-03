#include "../include/multitasking.h"

void idleTask(){
	while(true)
		_hlt();
}

void enableMultiTasking(){

	idleTaskPid = add_task((uint64_t)&idleTask, STDIN, BACKGROUND, DEFAULT_PRIORITY, IMMORTAL,idleArg);
	
	alter_process_state(idleTaskPid, PAUSED_PROCESS);		// pause until it's required

	forceCurrentTask();
}


unsigned int get_current_pid(){
	return tasks[currentTask].pid;
}
uint64_t getRSP(){
	return tasks[currentTask].stackPointer;
}
uint64_t getSS(){
	return tasks[currentTask].stackSegment;
}
uint8_t get_current_output(){
	return tasks[currentTask].output;
}
uint8_t get_current_input(){
	return tasks[currentTask].input;
}

uint8_t get_state(unsigned int pid){
	int pos = findTask(pid);
	if(pos==NO_TASK_FOUND)
		return NO_TASK_FOUND;
	
	return tasks[pos].state;
}

int findTask(unsigned int pid){
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].pid == pid && tasks[i].state != DEAD_PROCESS)
			return i;
	}	
	return NO_TASK_FOUND;			// no task with that pid found
}


uint64_t build_stack(uint64_t entrypoint, char ** arg0, uint64_t stackEnd){
	uint64_t stackStart = stackEnd + STACK_SIZE;
	stackStart -= stackStart % ALINGMENT;

	*(STACK_POS(RDI_POS)) = (uint64_t) arg0;

	for(int i=7 ; i<21 ; i++){
		if(i!=12)
			*(STACK_POS(i * 8)) = 0;
	}

	*(STACK_POS(IP_POS)) = entrypoint;	
	*(STACK_POS(CS_POS)) = CS_VALUE;				
	
	*(STACK_POS(FLAGS_POS)) = FLAG_VALUES;
	
	*(STACK_POS(SP_POS)) = stackStart - RET_POS;
	*(STACK_POS(SS_POS)) = SS_VALUE;
	
	*(STACK_POS(RET_POS)) = (uint64_t) &removeCurrentTask;	

	return stackStart;
}

int add_task(uint64_t entrypoint, uint8_t input, uint8_t output, uint8_t priority, uint8_t immortal, char ** arg0){
	if(currentDimTasks>=TOTAL_TASKS){
		return ERROR_NO_SPACE_FOR_TASK;
	}
	currentDimTasks++;

	int pos;
	for(pos=0; tasks[pos].state!=DEAD_PROCESS ;pos++);	// find free space

	uint8_t * stackEnd = mm_malloc(STACK_SIZE);

	if(stackEnd == NULL)
		return ERROR_NO_SPACE_FOR_TASK;

	uint8_t * stackStart = (uint8_t *) build_stack(entrypoint, arg0, (uint64_t) stackEnd);

	// Task initialization
	tasks[pos].stackPointer = (uint64_t) stackStart - STACK_POINT_OF_ENTRY; 
	tasks[pos].stackSegment = SS_VALUE;							

	tasks[pos].pid = newPidValue++;
	tasks[pos].state = ACTIVE_PROCESS;
	tasks[pos].priority = priority;
	tasks[pos].immortal = immortal;

	tasks[pos].stackStart = stackStart;
	tasks[pos].stackEnd = stackEnd;

	tasks[pos].params = arg0;
	tasks[pos].ticks = 1;

	tasks[pos].input = input;
	tasks[pos].output = output;

	return tasks[pos].pid;
}

void free_params(char ** params){
	if(params==NULL)
		return;

	for(int i=0; params[i]!=NULL; i++){
		mm_free(params[i]);
	}
	mm_free(params);
}


void destroy_process(unsigned int pos){
	signal_process_finished(tasks[pos].pid);
	free_params(tasks[pos].params);
	tasks[pos].state = DEAD_PROCESS;
	currentDimTasks--;
	mm_free(tasks[pos].stackEnd);
}

void removeCurrentTask(){
	_cli();

	destroy_process(currentTask);
	
	uint8_t out = tasks[currentTask].output;
	if(out != STDOUT){
		signal_eof(out);
	}

	forceChangeTask();

}

void forceChangeTask(){
	currentRemainingTicks = tasks[currentTask].priority + 1;
	forceTimerTick();
}

void alter_process_state(unsigned int pid, uint8_t new_state){
	int pos = findTask(pid);
	if(pos == NO_TASK_FOUND)
		return;

	tasks[pos].state = new_state;
}

int removeTask(unsigned int pid){
	int pos = findTask(pid);
	if(pos < 0)					// no task with that pid found
		return NO_TASK_FOUND;

	if(tasks[pos].immortal)
		return TASK_NOT_ALTERED;

	destroy_process(pos);

	if(pos == currentTask){
		forceChangeTask();
	}

	return TASK_ALTERED;
}

unsigned int change_priority(unsigned int pid, int delta){
	int pos = findTask(pid);
	if(pos < 0)
		return NO_TASK_FOUND;

	if(delta > MAX_PRIORITY)
		tasks[pos].priority = MAX_PRIORITY;
	else if(delta < 1)
		tasks[pos].priority = DEFAULT_PRIORITY;
	else 	
		tasks[pos].priority = delta;

	return true;
}

uint8_t has_or_decrease_time(){
	if(currentRemainingTicks < tasks[currentTask].priority - 1){
		tasks[currentTask].ticks++;
		currentRemainingTicks++;
		return true;
	}
	return false;

}

uint64_t next_task(uint64_t stackPointer, uint64_t stackSegment){

	tasks[currentTask].stackPointer = stackPointer;			
	tasks[currentTask].stackSegment = stackSegment;
	
	char found=0;
	unsigned int counter = 0;
	while( !found && counter < currentDimTasks ){			
		
		currentTask = (currentTask +  1) % TOTAL_TASKS;

		if(tasks[currentTask].state != DEAD_PROCESS)		 
			counter++;

		if(tasks[currentTask].state == ACTIVE_PROCESS){
			found = 1;
			tasks[currentTask].ticks++;
		}
	}

	if(counter == currentDimTasks){				// if all tasks are paused -> unpause idle task
		currentTask = findTask(idleTaskPid);
		alter_process_state(idleTaskPid, ACTIVE_PROCESS);
	}
	else if(tasks[currentTask].pid != idleTaskPid){			// if idle task is not paused -> pause it
		alter_process_state(idleTaskPid, PAUSED_PROCESS);
	}

	currentRemainingTicks = 0;			// reset ticks counter

	return tasks[currentTask].stackPointer;
}


int get_process_info(process_info * info){
	int j=0;
	for(int i=0; i<TOTAL_TASKS; i++){
		if(tasks[i].state != DEAD_PROCESS){

			if(tasks[i].params !=NULL){
				info[j].name = tasks[i].params[0];		
			}
			info[j].id = tasks[i].pid;
			info[j].state = tasks[i].state;
			info[j].priority = tasks[i].priority;
			info[j].stack = (uint64_t) tasks[i].stackStart;
			info[j].rsp = tasks[i].stackPointer;
			info[j].pickd = tasks[i].ticks;
			info[j].screen = tasks[i].output;

			j++;
		}
	}
	return j;
}


