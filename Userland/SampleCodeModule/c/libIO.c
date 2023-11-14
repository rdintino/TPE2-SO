#include <libIO.h>

void printIn(char *buffer, int row, int col, int color){
    write(buffer, row, col, color);
}

void printf(char *string){
    printIn(string, -1, -1, DEFAULT_COLOR);
}

void println(char *string){
    printf(string);
    printf("\n");
}

void printColored(char *string, int color){
    printIn(string, -1, -1, color);
}

void printlnColored(char * string, int color){
    printColored(string, color);
    printf("\n");
}

char getChar(){
	char c;
    read(STDIN,&c, 1);
	return c;
}

void putChar(char c) {
    char buffer[2];
    buffer[0] = c;
    buffer[1] = '\0';
    printf(buffer);
}

void deleteChar(){
    printf("\b");
}

void scanf(char *buffer, int bufferSize) {
    char c;
    int bufferDim = 0;
    while(((c = getChar()) != '\n' && c!=-1) && bufferDim < bufferSize){
        if(c != 0){
            if(c == '\b'){
                if(bufferDim > 0){
                    buffer[--bufferDim] = 0;
                    deleteChar();
                }
            }else{
                buffer[bufferDim++] = c;
                putChar(c);
            }
        }
    }
    buffer[bufferDim] = '\0';
}

void printTime(date currentDate){
    printColored("Local time & date: ", PINK);
    char buffer[3] = {0};

    printf(dateConverter(currentDate->hour, buffer));
    printf(":");
    printf(dateConverter(currentDate->minutes, buffer));
    printf(":");
    printf(dateConverter(currentDate->seconds, buffer));
    printf(" ");
    printf(dateConverter(currentDate->day, buffer));
    printf("/");
    printf(dateConverter(currentDate->month, buffer));
    printf("/");
    println(dateConverter(currentDate->year, buffer));
}

static unsigned int seed = 12345; // Semilla inicial

int getRandomSign() {
    seed = (seed * 1103515245 + 12345) % 2147483648;     // Generación del número pseudoaleatorio
    return (seed % 2 == 0) ? 1 : -1;    // Devuelve 1 si es par, -1 si es impar
}


char* int64ToString(int64_t num) {
    char* buffer = (char*)alloc(21); // 20 digits for the number, 1 for null-terminator
    if (buffer == NULL) {
        return NULL;
    }
    if(num==0) {
        buffer[0] = '0';
        buffer[1] = 0;
        return buffer;
    }
    int i = 0;
    while(num > 0) {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    }
    reverseString(buffer, i);
    buffer[i] = 0;
    return buffer;
}

uint64_t _atoi( char * string) {
    uint64_t result = 0;

    for(int i = 0 ; string[i] ; i++) {
        result = result*10 + string[i] - '0';
    }

    return result;
}

int strlength(const char * str) {
    int ans = 0;
    for (int i = 0; str[i] != 0; i++) {
        ans++;
    }
    return ans;
}

int isNum(char * str) {
    int i = 0;
    while (str[i] != 0) {
        if (str[i] <= '0' || str[i] >= '9') {
            return 0; 
        }
        i++;
    }
    return 1;
}

void reverseString(char * string, int length) {
    char aux;
    for(int i = 0, j = length - 1; i < j ; i++, j--) {
        aux = string[i];
        string[i] = string[j];
        string[j] = aux;
    }
}

int _strncpy(char * dest, const char * src, unsigned int n){
    int i=0;
    for(; src[i]!=0 && i<n; i++){
        dest[i] = src[i];
    }
    dest[i] = 0;
    return i;
}