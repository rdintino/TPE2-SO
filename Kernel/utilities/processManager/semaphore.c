#include "../include/semaphore.h"

int createSemaphore(unsigned int ID, unsigned int value){
	if(ID == 0){
		return INVALID_SEM_ID_ERROR;
	}
	if(activeSem == MAX_SEM){
		return NO_SPACE_ERROR;
	}

	int freePos = -1;
	for(int i = 0; i < MAX_SEM; i++){
		if(freePos == -1 && semaphoreList[i].ID == 0){
			freePos = i;
		}
		if(semaphoreList[i].ID == ID){
			return INVALID_SEM_ID_ERROR;
		}
	}
	createQueue(&(semaphoreList[freePos].queue), MAX_PROCESS);
	semaphoreList[freePos].ID = ID;
	semaphoreList[freePos].value = value;
	activeSem++;

	return DONE;
}

void destroySemaphore(unsigned int ID){
	int pos = findSemaphore(ID);
	if(pos != INVALID_SEM_ID_ERROR){
		lock(&(semaphoreList[pos].lock));
		semaphoreList[pos].ID = 0;
		semaphoreList[pos].value = 0;
		unlock(&(semaphoreList[pos].lock));
		destroyQueue(&(semaphoreList[pos].queue));
	}
	return;
}

int findSemaphore(unsigned int ID){
	for(int i = 0; i < MAX_SEM; i++){
		if(semaphoreList[i].ID == ID){
			return i;
		}
	}
	return INVALID_SEM_ID_ERROR;
}

unsigned int waitSemaphore(unsigned int ID){
	int pos = findSemaphore(ID);
	if(pos == INVALID_SEM_ID_ERROR){
		return INVALID_SEM_ID_ERROR;
	}
	lock(&(semaphoreList[pos].lock));
	if(semaphoreList[pos].value > 0){
		semaphoreList[pos].value--;
	}
	else{
		int PID = getCurrentPID();
		changeState(PID, WAITING_FOR_SEM);
		enqueue(&(semaphoreList[pos].queue), PID);
		unlock(&(semaphoreList[pos].lock));
		forceChangeTask();
		return true;
	}
	unlock(&(semaphoreList[pos].lock));

	return true;
}

int getAvailableSemaphore(){
	if(activeSem == MAX_SEM)
		return NO_SPACE_ERROR;

	uint8_t found = 0;
	int ID = 10;  

	while(!found){
		found = 1;
		for(int i = 0 ; i < MAX_SEM; i++){
			if(semaphoreList[i].ID == ID){
				found = 0;
				ID++;
				break;
			}
		}
	}
	return ID;
}

int makeSemaphoreAvailable(unsigned int value){
	int ID = getAvailableSemaphore();

	if(ID == NO_SPACE_ERROR){
		return NO_SPACE_ERROR;
	}

	int result = createSemaphore(ID, value);
	if(result == NO_SPACE_ERROR){
		return NO_SPACE_ERROR;
	}
	if(result == INVALID_SEM_ID_ERROR){
		return INVALID_SEM_ID_ERROR;
	}
	return ID;
}

unsigned int signalSemaphore(unsigned int ID){
	int pos = findSemaphore(ID);
	if(pos == INVALID_SEM_ID_ERROR){
		return INVALID_SEM_ID_ERROR;
	}

	lock(&(semaphoreList[pos].lock));
	if(getQueueSize(&(semaphoreList[pos].queue)) > 0){
		unsigned int blockedPID = dequeue(&(semaphoreList[pos].queue));
		changeState(blockedPID, ACTIVE_PROCESS);
	} else{
		semaphoreList[pos].value++;
	}
	unlock(&(semaphoreList[pos].lock));
	return true;
}

unsigned int getSemaphoreBlockedProcess(unsigned int pos, unsigned int * blockedPIDS){
	if(pos >= MAX_SEM){
		return 0;
	}

	if(getQueueSize(&(semaphoreList[pos].queue)) > 0){
		unsigned int pos;
		queueIterator(&(semaphoreList[pos].queue), &pos);
		int j = 0;
		for( ;queueHasNext(&(semaphoreList[pos].queue), &pos); j++ ){
			blockedPIDS[j] = (unsigned int) queueNext(&(semaphoreList[pos].queue), &pos);
		}
		return j;
	}
	return 0;
}

uint64_t getSemaphoreInfo(semaphoreInfo * info){
	int j = 0;
	for(int i = 0; i < MAX_SEM; i++){
		if(semaphoreList[i].ID != 0){
			info[j].ID = semaphoreList[i].ID;
			info[j].value = semaphoreList[i].value;
			info[j].numBlocked = getSemaphoreBlockedProcess(i, info[j].blockedPIDS);
			j++;
		}
	}
	return j;
}

unsigned int getSemaphoreBlockedProcessByID(unsigned int semaphoreID, unsigned int * blockedPIDS){
	int pos = findSemaphore(semaphoreID);
	if(pos == INVALID_SEM_ID_ERROR)
		return INVALID_SEM_ID_ERROR;

	return getSemaphoreBlockedProcess((unsigned int)pos, blockedPIDS);
}