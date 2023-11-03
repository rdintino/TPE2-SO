#include "../include/childProcess.h"

uint8_t hasChildren(unsigned int PID){
	for(int i = 0; i < MAX_WAIT_TASKS; i++){
		if(taskList[i].fatherPID == PID){
			return 1;
		}
	}
	return 0;
}

void signalFinished(unsigned int PID){

	for(int i = 0 ; i < MAX_WAIT_TASKS; i++){
		if( taskList[i].state == RUNNING && taskList[i].childPID == PID){
			taskList[i].state = FINISHED;
            // Wake up father process if all children have finished
			unsigned int father = taskList[i].fatherPID;
			if(childrenFinished(father)){
				removeChildren(father);
				changeState(father, ACTIVE_PROCESS);
			}

			return;
		}
	}
}

uint8_t childrenFinished(unsigned int PID){
	for(int i = 0; i < MAX_WAIT_TASKS; i++){
		if(taskList[i].state == RUNNING && taskList[i].fatherPID == PID){
			return 0;
		}	
	}

	return 1;
}

void removeChildren(unsigned int PID){
	for(int i = 0 ; i < MAX_WAIT_TASKS; i++){
		if(taskList[i].fatherPID == PID){
			taskList[i].fatherPID = 0;
			taskList[i].childPID = 0;
			taskList[i].state = NOT_TRACKING;
		}
	}
}

void addChild(unsigned int fatherPID, unsigned int childPID){
	for(int i = 0 ; i < MAX_WAIT_TASKS; i++){
		if(taskList[i].state == NOT_TRACKING){
			taskList[i].fatherPID = fatherPID;
			taskList[i].childPID = childPID;
			taskList[i].state = RUNNING;
			return;
		}
	}
}


void waitChildren(){
	int PID = getCurrentPID();
	if(!hasChildren(PID)){
		return;
	}
	changeState(PID, WAITING_FOR_CHILD);
	forceChangeTask();
}


unsigned int addChildTask(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0){
	unsigned int childPID = add_task(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL , arg0);
	addChild(get_current_pid(), childPID);
	return childPID;
}