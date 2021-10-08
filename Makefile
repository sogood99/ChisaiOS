# Use wildcard to get all c files
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

# defualts to building os_img
all: os_img

# make run launches bochs
run: all
	bochs

os_img : boot/boot.bin kernel/kernel.bin
	cat $^ > os_img

kernel/kernel.bin : kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# combile all c to obj files
%.o : %.c ${H_EADERS}
	i386-elf-gcc -ffreestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -o $@

clean:
	rm os_img
	find . -name \*.o -type f -delete
	find . -name \*.bin -type f -delete
