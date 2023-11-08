#include <pipes.h>

int createPipe(unsigned int ID){
	if(ID == 0)				
		return INVALID_PIPE_ID;
	if(pipesQty == MAX_PIPES)
		return NO_SPACE_ERROR;

	int freePos = -1;
	for(int i = 0; i < MAX_PIPES; i++){
		if(freePos == -1 && pipeList[i].pipeID == 0){
			freePos = i;
		}
		if(pipeList[i].pipeID == ID){
			return INVALID_PIPE_ID;
		}
	}
	int semID1 = sem(0);
	int semID2 = makeSemaphoreAvailable(PIPE_SIZE);
	if(semID1 == INVALID_SEM_ID_ERROR || semID2 == INVALID_SEM_ID_ERROR){
		destroySemaphore(semID1);
		destroySemaphore(semID2);
		return NO_SPACE_ERROR;
	}

	pipeList[freePos].pipe = mm_malloc(PIPE_SIZE);
	if(pipeList[freePos].pipe == NULL){
		destroySemaphore(semID1);
		destroySemaphore(semID2);
		return NO_SPACE_ERROR;
	}
	pipeList[freePos].pipeID = ID;
	pipeList[freePos].readSemID  = semID1;
	pipeList[freePos].writeSemID  = semID2;
	pipeList[freePos].writePos = 0;
	pipeList[freePos].readPos = 0;
	pipeList[freePos].qty = 0;
	pipeList[freePos].eof = 0;

	pipesQty++;
	return DONE;
}

uint64_t getPipeInfo(pipesInfo * info){
	int j = 0;
	for(int i = 0; i < MAX_PIPES; i++){
		if(pipeList[i].pipeID != 0){
			info[j].ID = pipeList[i].pipeID;
			info[j].usage = pipeList[i].qty;
			j++;
		}
	}
	return j;
}

int findPipe(unsigned int ID){
	for(int i = 0; i < MAX_PIPES; i++){
		if(pipeList[i].pipeID == ID){
			return i;
		}
	}
	return INVALID_PIPE_ID;
}

int findAvailablePipe(){
	if(pipesQty == MAX_PIPES)
		return NO_SPACE_ERROR;

	uint8_t found = false;
	int pipeID = 0;

	while(!found){
		found = true;
		for(int i = 0; i < MAX_PIPES; i++){
			if(pipeList[i].pipeID == pipeID){
				found = false;
				pipeID++;
				break;
			}
		}
	}
	return pipeID;
}

int createAvailablePipe(){
	int ID = findAvailablePipe();

	if(ID == NO_SPACE_ERROR){
		return NO_SPACE_ERROR;
	}

	if( createPipe(ID) != DONE){
		return NO_SPACE_ERROR;
	}
	return ID;
}

void destroyPipe(unsigned int ID){
	int pos = findPipe(ID);
	if(pos == INVALID_PIPE_ID){
		return;
	}
	destroySemaphore(pipeList[pos].writeSemID);	
	destroySemaphore(pipeList[pos].readSemID);
	mm_free(pipeList[pos].pipe);

	pipeList[pos].readSemID  = 0;
	pipeList[pos].writeSemID  = 0;
	pipeList[pos].pipeID = 0;
	pipeList[pos].writePos = 0;
	pipeList[pos].readPos = 0;
	pipeList[pos].qty = 0;
	pipeList[pos].pipe = 0;

	pipesQty--;
}

void signalEOF(unsigned int ID){
	int pos = findPipe(ID);
	if(pos == INVALID_PIPE_ID){
		return;
	}

	pipeList[pos].eof = 1;
}

int readFromPipe(unsigned int ID, char * dest, unsigned int count){
	int pos = findPipe(ID);
	if(pos == INVALID_PIPE_ID){
		return INVALID_PIPE_ID;
	}
	if(pipeList[pos].eof && pipeList[pos].qty == 0){
		return EOF;
	}
	int i = 0;	
	for(; i < count && !(pipeList[pos].eof && pipeList[pos].qty == 0); i++){
		waitSemaphore(pipeList[pos].readSemID);

		dest[i] = pipeList[pos].pipe[pipeList[pos].readPos];
		INCREASE_MOD(pipeList[pos].readPos, PIPE_SIZE);
		pipeList[pos].qty--;

		signalSemaphore(pipeList[pos].writeSemID);
	}
	return i;
}

int writeToPipe(unsigned int ID, const char * src, unsigned int count){
	int pos = findPipe(ID);
	if(pos == INVALID_PIPE_ID)
		return INVALID_PIPE_ID;

	for(int i=0; i<count; i++){
		waitSemaphore(pipeList[pos].writeSemID);

		pipeList[pos].pipe[pipeList[pos].writePos] = src[i];
		INCREASE_MOD(pipeList[pos].writePos, PIPE_SIZE);
		pipeList[pos].qty++;

		signalSemaphore(pipeList[pos].readSemID);
	}
	return count;
}

uint64_t getPipeInfo(pipesInfo * info){
	int j = 0;
	for(int i = 0; i < MAX_PIPES; i++){
		if(pipeList[i].pipeID != 0){
			info[j].ID = pipeList[i].pipeID;
			info[j].usage = pipeList[i].qty;
			info[j].readNumBlocked = getSemaphoreBlockedProcessByID(pipeList[i].readSemID, info[j].readBlockedPIDS);
			info[j].writeNumBlocked = getSemaphoreBlockedProcessByID(pipeList[i].writeSemID, info[j].writeBlockedPIDS);
			j++;
		}
	}
	return j;
}