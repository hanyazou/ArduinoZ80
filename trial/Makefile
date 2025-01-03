
Z80AS = ../asl-releases/asl
Z80LD = ../asl-releases/p2bin

SRCS = \
  ../Z80/sources/Z80.c \
  main.c \
  machine.c \
  debug.c \

INCS = \
  machine.h \
  debug.h \

DEFS = \
  -DZ80_STATIC \
  -DZ80_WITH_EXECUTE \
  -DZ80_WITH_LOCAL_HEADER \

OPTS = \
  -I../Zeta/API \
  -I../Z80/API \

OBJS = $(patsubst %.c,%.o,$(SRCS))

all: trial

$(SRCS): $(INCS)

trial: $(SRCS) hello.h
	CC $(DEFS) $(OPTS) -o trial $(SRCS) 

hello.bin: hello.z80
	$(Z80AS) hello.z80
	$(Z80LD) hello

hello.h: hello.bin
	xxd -i hello.bin > hello.h

.PHONY: clean
clean:
	rm -f trial hello.p hello.bin hello.h $(OBJS)
