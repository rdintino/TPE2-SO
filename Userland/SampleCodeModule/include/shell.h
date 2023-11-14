#ifndef SHELL_H
#define SHELL_H

#include <libIO.h>
#include <colors.h>
#include <date.h>
#include <string.h>
#include <pong.h>

#define BUFFER_SIZE 25
#define STDIN 1
#define STDOUT 1
#define MODULES 19
#define HALF_SECOND 500000000
#define ACTIVE_PROCESS 1
#define PAUSED_PROCESS 2
#define MM_INFO 3

typedef struct{
    char * name;
    char * description;
    uint64_t function;
    int args;
    int pipe;

} modules;

extern void invalidOperationCode();

void * memset(void * destiny, int32_t c, uint64_t length);
unsigned int check_valid_program(char * string);
char ** make_params(char ** words, unsigned int len);
int piped_process_handle(char ** words, unsigned int amount_of_words);
void single_process_handle(char ** words, unsigned int amount_of_words);


int parseCommand(char ** command, char readBuf[BUFFER_SIZE]);

void initShell();
void callModule(char *buffer);
void help();
void divZero();
void invOpCode();
void time();
void pong();
void infoReg();
void clear();
void testMm();
void testProcesses(uint64_t argc, char *argv[]);
void testPriorities();

void ps();
void loop();
void kill();
void nice();
void block();

void cat();
void wc();
void filter();
void phylo();
void nice(char ** args);
void block(char ** args);
void mem_status();

#endif