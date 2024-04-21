#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mach/mach.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <PID> <ADDRESS>\n", argv[0]);
        return -1;
    }

    pid_t pid = atoi(argv[1]);
    mach_port_t task;
    kern_return_t kr;

    kr = task_for_pid(mach_task_self(), pid, &task);
    if (kr != KERN_SUCCESS) {
        fprintf(stderr, "Unable to get task for pid %d: %s\n", pid, mach_error_string(kr));
        return -1;
    }

    vm_address_t address;
    sscanf(argv[2], "%lx", &address);

    vm_size_t size = 1024;
    vm_offset_t data;
    mach_msg_type_number_t data_count;

    kr = vm_read(task, address, size, (vm_offset_t *)&data, &data_count);
    if (kr == KERN_SUCCESS) {
        printf("Data read from %p: %s\n", (void*)address, (char *)data);
        vm_deallocate(mach_task_self(), data, data_count);
    } else {
        fprintf(stderr, "Failed to read memory: %s\n", mach_error_string(kr));
    }

    return 0;
}