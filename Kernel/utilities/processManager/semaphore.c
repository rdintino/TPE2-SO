#include "./include/semaphore.h"

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
	int ID = INITIAL_ID;  

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