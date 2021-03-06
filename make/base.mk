CC := gcc

CFLAGS := -fno-asynchronous-unwind-tables -ffreestanding \
	-nostdlib -mno-red-zone -fno-stack-protector -mno-sse -mno-mmx \
	-mno-sse2 -mno-3dnow -mno-avx -maccumulate-outgoing-args -Wall \
	-Wextra -I./include -fno-exceptions -g -DDebug

LD := ld
LDFLAGS :=

ASM := nasm
ASMFLAGS := 

TARGETS :=
ALL_OBJS :=

include make/module.mk