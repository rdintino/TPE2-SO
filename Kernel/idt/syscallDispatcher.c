#include "../include/syscalls.h"

uint64_t syscallDispatcher(uint64_t id, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4){
    switch(id){
        case SYS_WRITE:
            sys_write_to_screen((char *) param1, (int) param2, (int) param3, (int) param4);
            return 0;
        case SYS_READ:
            sys_read((int) param1,(char *) param2,(int) param3);
            return 0;
        case SYS_CLEAR:
            sys_clear();
            return 0;
        case SYS_TIME:
            sys_time((date) param1);
            return 0;
        case SYS_HOLDER:
            sys_holder((int) param1);
            return 0;
        case SYS_BEEP:
            sys_beep((uint32_t) param1);
            return 0;
        case SYS_INFO_REG:
            sys_info_reg();
            return 0;
        case SYS_DRAW:
            sys_draw((int) param1, (int) param2, (int) param3);
            return 0;
        case SYS_ALLOC:
            return sys_alloc((uint64_t) param1);
        case SYS_FREE:
            sys_free((void *) param1);
            return 0;
        case SYS_MM_STATUS:
            return sys_mm_status((char *) param1);
        case SYS_PRINT_MEM:
            return sys_print_mem((uint64_t) param1, (char *) param2);
        case SYS_REGISTER_PIPE:
            return sys_register_pipe((unsigned int) param1);
        case SYS_REGISTER_PIPE_AVAILABLE:
            return sys_register_pipe_available();
        case SYS_READ_PIPE:
            return sys_read_pipe((unsigned int) param1, (char *) param2, (unsigned int) param3);
        case SYS_WRITE_PIPE:
            return sys_write_pipe((unsigned int) param1, (char *) param2, (unsigned int) param3);
        case SYS_PIPE_INFO:
            return sys_pipe_info((pipesInfo *) param1);
        case SYS_DESTROY_PIPE:
            sys_destroy_pipe((unsigned int) param1);
            return 0;
        case SYS_REGISTER_SEM:
            return sys_register_sem((unsigned int) param1, (unsigned int) param2);
        case SYS_REGISTER_SEM_AVAILABLE:
            return sys_register_sem_available((unsigned int) param1);
        case SYS_WAIT_SEM:
            return sys_wait_sem((unsigned int) param1);
        case SYS_SIGNAL_SEM:
            return sys_signal_sem((unsigned int) param1);
        case SYS_SEMAPHORE_INFO:
            return sys_semaphore_info((semaphoreInfo *) param1);
        case SYS_DESTROY_SEM:
            sys_destroy_sem((unsigned int) param1);
            return 0;
        case SYS_REGISTER_CHILD_PROCESS:
            return sys_register_child_process((unsigned int) param1, (uint8_t) param2, (uint8_t) param3, (char**) param4);
        case SYS_WAIT_CHILDREN:
            sys_wait_children();
            return 0;
        case SYS_GET_PID:
            return sys_get_pid();
        case SYS_REGISTER_PROCESS:
            return sys_register_process((uint64_t) param1, (uint8_t) param2, (uint8_t) param3, (char**) param4);
        case SYS_PROCESS_ALIVE:
            return sys_process_alive((unsigned int) param1);
        case SYS_PAUSE_PROCESS:
            return sys_pause_process((unsigned int) param1);
        case SYS_PROCESS_INFO:
            return sys_process_info((processInfo *) param1);
        case SYS_KILL_PROCESS:
            return sys_kill_process((unsigned int) param1);
        case SYS_NICE:
			sys_nice((uint8_t) param1, (int) param2);
            return 0;
        case SYS_RENOUNCE_CPU:
            sys_renounce_cpu();
            return 0;
    }
}