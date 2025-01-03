#include "machine.h"
#include "hello.h"
#include <string.h>

Machine machine;

int main(int ac, char* av[])
{
    machine_initialize(&machine);
    machine_power(&machine, Z_TRUE);
    memcpy(machine.memory, hello_bin, hello_bin_len);
    z80_run(&machine.cpu, 1000);
}
