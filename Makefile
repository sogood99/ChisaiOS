# Use wildcard to get all c files
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)

OBJ = ${C_SOURCES:.c=.o}

# defualts to building os.img
all: os.img

# make run launches qemu
run: all
	qemu-system-x86_64 -drive format=raw,file=os.img

debug: all
	qemu-system-x86_64 -s -S -drive format=raw,file=os.img

os.img : boot/boot.bin kernel/kernel.bin
	cat $^ > os.img

# link using link.ld file, with entry -e 0x1000
kernel/kernel.bin : kernel/kernel_entry.o ${OBJ}
	ld -T link.ld -e 0x1000 -m elf_i386 -o $@ $^ --oformat binary

# combile all c to obj files
%.o : %.c ${H_EADERS}
	gcc -m32 -fno-pie -static -nostdlib -ffreestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf os.img
	find . -name \*.o -type f -delete
	find . -name \*.bin -type f -delete
