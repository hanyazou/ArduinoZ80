#ifndef ArduinoZ80_trial_MACHINE_H__
#define ArduinoZ80_trial_MACHINE_H__

#include <Z/constants/pointer.h>
#include <Z80.h>

#define CYCLES_PER_FRAME 69888
#define CYCLES_AT_INT    24
#define CYCLES_PER_INT   32
#define ROM_SIZE         0x1000 /* 4 KiB */
#define MEMORY_SIZE      0x2000 /* 8 KiB */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    zusize  cycles;
    zuint8  memory[MEMORY_SIZE];
    Z80     cpu;
} Machine;

void machine_initialize(Machine *self);
void machine_power(Machine *self, zboolean state);
void machine_reset(Machine *self);

#ifdef __cplusplus
}
#endif

#endif  /* ArduinoZ80_trial_MACHINE_H__ */
