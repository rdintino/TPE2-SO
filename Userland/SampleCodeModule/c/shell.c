#include <shell.h>

#define PARAMETERS_ERROR "Parameters are not needed for this command, try without them.\n"
#define PIPE_ERROR "The program does not work with pipes, try without them.\n"
#define MISSING_MULTIPLE_PARAMS "The program needs %d parameters.\n"
#define MISSING_SINGLE_PARAM "The program needs a parameter.\n"
#define INVALID_PROGRAM "The program does not exist. Use the command help for help\n"
#define MALLOC_ERROR "Error allocating space for args!"
#define INVALID_COMMAND_MSG "-Invalid command. Check available commands with help.\n"
#define INVALID_PID_MSG "Invalid PID: No such process is running.\n"
#define ERROR_PID -1
#define BACKGROUND 0
#define FOREGROUND 1

#define PIPE "|"
#define MAX_COMMAND_WORDS 10
#define MIN(a,b) ((a) <= (b) ? (a) : (b))

modules module[] = {
    {"help", "          -    Displays the module list", (uint64_t)&help,0,1},
    {"divzero", "       -    Throws Divide by Zero exception",(uint64_t) &divZero,0,0},
    {"invopcode", "     -    Throws Invalid Operation Code exception",(uint64_t) &invOpCode,0,0},
    {"time", "          -    Displays the systems current time",(uint64_t) &time,0,1},
    {"pong", "          -    Loads Pong game",(uint64_t) &pong,0,0},
    {"inforeg", "       -    Displays the registers state",(uint64_t) &infoReg,0,0},
    {"clear", "         -    Clears the screen",(uint64_t) &clear,0,0},
    {"testMm","         -    Test memory manager",(uint64_t) &testMm,0,0},
    {"testProcesses","  -    Test process management",(uint64_t) &testProcesses,1,0},
    {"testPriorities"," -    Test priorities",(uint64_t) &testPriorities,0,0},
    {"cat","            -    Writes in console what has been read",(uint64_t) &cat,0,1},
    {"loop","           -    Loops while printing the process id every half a second",(uint64_t) &loop,0,0},
    {"wc","             -    Counts the lines in what has been written in screen",(uint64_t) &wc,0,1},
    {"filter","         -    Filters what has been written and only shows consonants",(uint64_t) &filter,0,1},
    {"kill","           -    Kills a process given its id",(uint64_t) &kill,1,0},
    {"ps","             -    Shows every running process and its data",(uint64_t) &ps,0,0}
};

static char *starter = "$> ";
int firstInit = 1;

int parseCommand(char ** command, char buffer[BUFFER_SIZE]) {
	int i = 0, commandWords = 0;
	
	for(int postSpace = 1; commandWords < MAX_COMMAND_WORDS && buffer[i] != '\n' && buffer[i] != 0; i++) {
        if(buffer[i]==-1){
            buffer[i]=0;//1help 0help
            return commandWords;
        }
        if(buffer[i] == ' ') {
          postSpace = 1;
          buffer[i] = 0;
        } else if(postSpace) {
          command[commandWords++] = buffer + i; 
          postSpace = 0;
        }
	}

  buffer[i] = 0;
  return commandWords;
}

unsigned int check_valid_program(char * string){
    for(int i = 0; i < MODULES; i++){
        if(strcmp(string, module[i].name)==0){
            return i;
        }
    }
    return -1;
}

char ** make_params(char ** words, unsigned int len){
    void * ptr = (void*) alloc((2 + len) * sizeof(char *)); // + 1 for name, + 1 por null termination

    if(ptr == NULL){
        printf(MALLOC_ERROR);   
        return NULL;
    }

    char ** params = (char **) ptr;

    void * param;
    int paramLen;

    int i=0;
    for(; i<len + 1; i++){
        paramLen = strlen(words[i]) + 1;
        param = (void*) alloc(paramLen);

         if(param == NULL){
            printf(MALLOC_ERROR);     
            return NULL;
        }

        char * param2 = (char *) param;

        strncpy(param2, words[i], paramLen);
        params[i] = param2;
    }
    params[i] = NULL;

    return params;
}

int piped_process_handle(char ** words, unsigned int amount_of_words){
    if(amount_of_words != 3 || strcmp(PIPE, words[1]) != 0)
        return 0;
    unsigned int p1 = check_valid_program(words[0]);
    unsigned int p2 = check_valid_program(words[2]);
    if(p1 == -1 || p2 == -1){
        printf(INVALID_COMMAND_MSG);
        return 1;
    }
    if(!module[p1].pipe){
        printf(PIPE_ERROR);
        return 1;
    }
    int pipe_id = registerPipeAvailable();
    

    if(pipe_id <= 0){
        printf("Error creating pipe!");
        return 1;
    }

    registerChildProcess(module[p1].function, STDIN, pipe_id, make_params(words, 0)); 
    registerChildProcess(module[p2].function, pipe_id, FOREGROUND,  make_params(words, 0)); 

    waitChildren();

    destroyPipe(pipe_id);

    return 2;
}

void single_process_handle(char ** words, unsigned int amount_of_words){
    unsigned int program_pos = check_valid_program(words[0]);

    if(program_pos == -1){
        printf(INVALID_COMMAND_MSG);
        return;
    }
    if(amount_of_words - 1 < module[program_pos].args){
        printf(module[program_pos].args > 1 ? MISSING_MULTIPLE_PARAMS : MISSING_SINGLE_PARAM);
        return;
    }

    int i;
    for(i=module[program_pos].args + 1; i < amount_of_words; i++){
        if(strcmp("&", words[i]) == 0){ 
            registerChildProcess(module[program_pos].function, STDIN, BACKGROUND, make_params(words, MIN(i-1,module[program_pos].args))); //Run on Background
            return; 
        }
    }
    registerChildProcess(module[program_pos].function, STDIN, FOREGROUND, make_params(words, MIN(amount_of_words-1, module[program_pos].args))); 
    waitChildren();
    
}


void initShell(){
    if(firstInit){
        println("Welcome! Enter help to display module list");
        firstInit = 0;
    }
    char * command[MAX_COMMAND_WORDS] = {0};
    char buffer[BUFFER_SIZE] = {0};
    while(1){
        printColored(starter, GREEN);
        scanf(buffer, BUFFER_SIZE);
        int commandWords = parseCommand(command, buffer);
        println("");
        if(commandWords == 0)
          continue;
    
        if(piped_process_handle(command,commandWords) == 0){
          single_process_handle(command,commandWords);
        }
        memset(buffer, 0, BUFFER_SIZE);
    } 
}

//void callModule(char *buffer){
//    println("");
//    for(int i = 0; i < MODULES; i++){
//        if(strcmp(buffer, module[i].name) == 0){
//            module[i].function();
//            return;
//        }
//    }
//    printf(buffer);
//    println(": command not found, please enter 'help' for module list");
//}

void help(){
    for(int i = 0; i < MODULES; i++){
        printf("             ");
        printColored(module[i].name, GREY);
        printlnColored(module[i].description, GREY);
    }
}

void divZero(){
    int a = 1 /0 ;
}

void invOpCode(){
    invalidOperationCode();
}

void time(){
    dateData currentDate;
    getTime(&currentDate);
    printTime(&currentDate);
}

void pong(){
    menuPong();
    clearScreen();
}

void infoReg(){
    getRegisters();
}

void clear(){
    clearScreen();
}

void cat(){
  int c;
  char buffer[BUFFER_SIZE] = {0};
  scanf(buffer, BUFFER_SIZE);
  println(buffer);
}

void loop(){
	int pid = getPID();
	char *buffer = "  Process ID:";
	while(1){
		for(int i = 0; i < HALF_SECOND ; i++)
			;
		printf(" Process ID:");
        println(int64ToString(pid));

	}	
}

void filter(){
  char c;
  int i,j=0;
  char buffer[BUFFER_SIZE] = {0};
  char outBuffer[BUFFER_SIZE] ={0};
  outBuffer[j++] = '\n';
  scanf(buffer,BUFFER_SIZE);
  for(i=0;i<BUFFER_SIZE || buffer[i]==0;i++){
    c = buffer[i];
    if(c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
        outBuffer[j++] = c;
  }
  println(outBuffer);
}

void wc(){
  int counter = 0; 
  char c;
  while ((c = getChar()) != -1){
    if (c == '\n'){
      counter++;
    }
    putChar(c);
  }
  printf("Total new lines: ");
  println(int64ToString(counter));
  return;
}

void ps(){

	processInfo * info = (void *)alloc(20 * sizeof(processInfo)); 

	if(info == NULL) {
		printf("No more space\n");
		return;
	}

	uint64_t amount = getProcessInfo(info);

	for(int i = 0; i < amount; i++){
		printf("Name: ");
        printf(info[i].name);
        printf("\t| ");
        printf("PID: ");
        printf(int64ToString(info[i].ID));
        printf("\t| ");
        printf("State: ");
        switch(info[i].state){
            case ACTIVE_PROCESS: 
                printf("Active\t| ");
                break;
            case PAUSED_PROCESS:
                printf("Paused\t| ");
                break;
            default:
                printf("Blocked\t| ");
                break;
        }
        printf("Priority: ");
        printf(int64ToString(info[i].priority));
        printf("\t| ");
        printf("Stack: ");
        printf(int64ToString(info[i].stack));
        printf("\t| ");
        printf("RSP: ");
        printf(int64ToString(info[i].rsp));
        printf("\t| ");
        printf("Screen: ");
        switch(info[i].screen) {
        case BACKGROUND:
            printf("Background\n");
            break;
        case STDOUT:
            printf("STDOUT\n");
            break;
        default:
            printf("Pipe\n");
            break;
        }
	}

	freeMem((void*)info);
}


void kill(char ** args){
  if(!isNum(args[1])) { 
    printf("Kill's argument must be number (process id).\n");
    return;
  }
  uint64_t pid = atoi(args[1]);
  if (killProcess(pid) == ERROR_PID){
    printf(INVALID_PID_MSG);
  }
  return;
}

