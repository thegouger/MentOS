OBJECTS = loader.o framebuffer.o kmain.o io_ports.o interrupts.o int.o keyboard.o lib/memcpy.o lib/itoa.o \
					systick.o
LINKERSCRIPT = kernel.ld

CC = g++
LD = ld
AS = nasm

CPPFLAGS = -std=c++11 -m32 -nostdlib -fno-builtin -fno-stack-protector -fno-exceptions \
           -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Ilib/ -Iutilities/
LDFLAGS = -T $(LINKERSCRIPT) -melf_i386
ASFLAGS = -f elf

all: kernel.elf

%.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@
	size -A $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *.elf

