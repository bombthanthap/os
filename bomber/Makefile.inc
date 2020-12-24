CROSS = ~/../../bin/arm-none-eabi-
CC = gcc
AS = as
LD = ld
ASFLAGS = -mcpu=arm1176jzf-s
CFLAGS = -O2 -mcpu=arm1176jzf-s -nostdlib -nostartfiles -ffreestanding
LFLAGS = --no-undefined -T $(LINKER_SCRIPT)

LINKER_SCRIPT = kernel.ld
