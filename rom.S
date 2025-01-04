
	cpu	z80
	ORG	0

CONDAT		equ	0

	LD	HL,MSG
LOOP:
	LD	A,(HL)
	OR	A
	JR	Z,DONE
	OUT	(CONDAT),A
	INC	HL
	JR	LOOP

DONE:
	HALT

MSG:
	DB "Hello, world!\r\n\0"
