#include "src/machine.h"

Machine machine;
extern unsigned char rom_bin[];
extern unsigned int rom_bin_len;

extern "C" {
   int _write ( int fd, char *ptr, int len ) {
      ( void ) fd;
      return Serial.write ( ptr, len );
   }
}

void setup() {
  // put your setup code here, to run once:
  while (!Serial);
  Serial.begin(115200);
  //mSerial.println("Hello serial");
  //printf("Hello printf\n\r");

  machine_initialize(&machine);
  machine_power(&machine, Z_TRUE);
  memcpy(machine.memory, rom_bin, rom_bin_len);
}

void loop() {
  // put your main code here, to run repeatedly:
  z80_run(&machine.cpu, 10);
}
