#include <shell.h>

modules module[] = {
    {"help", "          -    Displays the module list", help},
    {"divzero", "       -    Throws Divide by Zero exception", divZero},
    {"invopcode", "     -    Throws Invalid Operation Code exception", invOpCode},
    {"time", "          -    Displays the systems current time", time},
    {"pong", "          -    Loads Pong game", pong},
    {"inforeg", "       -    Displays the registers state", infoReg},
    {"clear", "         -    Clears the screen", clear},
    {"testMm","         -    Test memory manager", testMm},
    {"testProcesses","  -    Test process management",testProcesses},
    {"testPriorities"," -    Test priorities",testPriorities},
    {"cat","            -    Writes in console what has been read", cat},
    {"loop","           -    Loops while printing the process id every half a second",loop},
    {"wc","             -    Counts the lines in what has been written in screen",wc},
    {"filter","         -    Filters what has been written and only shows consonants",filter}
};

static char *starter = "$> ";
int firstInit = 1;

void initShell(){
    if(firstInit){
        println("Welcome! Enter help to display module list");
        firstInit = 0;
    }
    char buffer[BUFFER_SIZE] = {0};
    while(1){
        printColored(starter, GREEN);
        scanf(buffer, BUFFER_SIZE);
        callModule(buffer);
        memset(buffer, 0, BUFFER_SIZE);
    } 
}

void callModule(char *buffer){
    println("");
    for(int i = 0; i < MODULES; i++){
        if(strcmp(buffer, module[i].name) == 0){
            module[i].function();
            return;
        }
    }
    printf(buffer);
    println(": command not found, please enter 'help' for module list");
}

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
  printf(buffer);
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
  printf(int64ToString(counter));
  return;
}


