#include "../include/syscalls.h"

void syscallDispatcher(uint64_t id, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4){
    switch(id){
        case SYS_WRITE:
            sys_write((char *) param1, (int) param2, (int) param3, (int) param4);
            break;
        case SYS_READ:
            sys_read((char *) param1, (int) param2);
            break;
        case SYS_CLEAR:
            sys_clear();
            break;
        case SYS_TIME:
            sys_time((date) param1);
            break;
        case SYS_HOLDER:
            sys_holder((int) param1);
            break;
        case SYS_BEEP:
            sys_beep((uint32_t) param1);
            break;
        case SYS_INFO_REG:
            sys_info_reg();
            break;
        case SYS_DRAW:
            sys_draw((int) param1, (int) param2, (int) param3);
            break;
        case SYS_ALLOC:
            sys_alloc((uint64_t) param1);
            break;
        case SYS_DESTROY_PIPE:
            sys_destroy_pipe((unsigned int) param1);
            break;
        case SYS_PIPE_INFO:
            sys_pipe_info((pipesInfo *) param1);
            break;
        case SYS_READ_PIPE:
            sys_read_pipe((unsigned int) param1, (char *) param2, (unsigned int) param3);
            break;
        case SYS_REGISTER_PIPE_AVAILABLE:
            sys_register_pipe_available();
            break;
        case SYS_WRITE_PIPE:
            sys_write_pipe((unsigned int) param1, (char *) param2, (unsigned int) param3);
            break;
        case SYS_WAIT_SEM:
            sys_wait_sem((unsigned int) param1);
            break;
        case SYS_SIGNAL_SEM:
            sys_signal_sem((unsigned int) param1);
            break;
        case SYS_DESTROY_SEM:
            sys_destroy_sem((unsigned int) param1);
            break;
        case SYS_REGISTER_SEM:
            sys_register_sem((unsigned int) param1, (unsigned int) param2);
            break;
        case SYS_REGISTER_SEM_AVAILABLE:
            sys_register_sem_available();
            break;
        case SYS_REGISTER_CHILD_PROCESS:
            sys_register_child_process((unsigned int) param1);
            break;
        case SYS_WAIT_CHILDREN:
            sys_wait_children();
            break;
        case SYS_GET_PID:
            sys_get_pid();
            break;  
    }
}