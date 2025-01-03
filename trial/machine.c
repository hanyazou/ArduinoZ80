#include "debug.h"
#include "machine.h"
#include <stdio.h>
#include <string.h>

static zuint8 machine_cpu_read(Machine *self, zuint16 address)
{
    zuint8 res;

    res = address < MEMORY_SIZE ? self->memory[address] : 0xFF;
    print_debug("read  %04x, %02x\n", address, res);

    return res;
}


static void machine_cpu_write(Machine *self, zuint16 address, zuint8 value)
{
    print_debug("write %04x, %02x\n", address, value);
    if (address >= ROM_SIZE && address < MEMORY_SIZE) {
        self->memory[address] = value;
    }
}


static zuint8 machine_cpu_in(Machine *self, zuint16 port)
{
    zuint8 res;

    res = 0xFF;
    print_debug("in    %04x, %02x\n", port, res);

    return res;
}


static void machine_cpu_out(Machine *self, zuint16 port, zuint8 value)
{
    zuint8 port8 = (port & 0xff);

    print_debug("out   %04x, %02x\n", port, value);
    switch (port8) {
    case 00:
        putchar(value);
        break;
    }
}


void machine_initialize(Machine *self)
{
    self->cpu.context      = self;
    self->cpu.fetch_opcode =
        self->cpu.fetch        =
        self->cpu.nop          =
        self->cpu.read         = (Z80Read )machine_cpu_read;
    self->cpu.write        = (Z80Write)machine_cpu_write;
    self->cpu.in           = (Z80Read )machine_cpu_in;
    self->cpu.out          = (Z80Write)machine_cpu_out;
    self->cpu.halt         = Z_NULL;
    self->cpu.nmia         = Z_NULL;
    self->cpu.inta         = Z_NULL;
    self->cpu.int_fetch    = Z_NULL;
    self->cpu.ld_i_a       = Z_NULL;
    self->cpu.ld_r_a       = Z_NULL;
    self->cpu.reti         = Z_NULL;
    self->cpu.retn         = Z_NULL;
    self->cpu.hook         = Z_NULL;
    self->cpu.illegal      = Z_NULL;
    self->cpu.options      = Z80_MODEL_ZILOG_NMOS;
}


void machine_power(Machine *self, zboolean state)
{
    if (state) {
        self->cycles = 0;
        memset(self->memory, 0, sizeof(self->memory));
    }

    z80_power(&self->cpu, state);
}


void machine_reset(Machine *self)
{
    z80_instant_reset(&self->cpu);
}


void machine_run_frame(Machine *self)
{
    /* CPU cycles before the INT signal */
    self->cycles += z80_execute(&self->cpu, CYCLES_AT_INT - self->cycles);

    /* CPU cycles during the INT signal */
    z80_int(&self->cpu, Z_TRUE);
    self->cycles += z80_run(&self->cpu, (CYCLES_AT_INT + CYCLES_PER_INT) - self->cycles);
    z80_int(&self->cpu, Z_FALSE);

    /* CPU cycles after the INT signal */
    self->cycles += z80_execute(&self->cpu, CYCLES_PER_FRAME - self->cycles);

    self->cycles -= CYCLES_PER_FRAME;
}
