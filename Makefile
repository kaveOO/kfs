# COLORS

PURPLE			=	\x1b[0m\x1b[38;2;128;0;128m
LIGHT_PURPLE	=	\x1b[0m\x1b[38;2;204;153;255m
DARK_PURPLE		=	\x1b[1m\x1b[38;2;75;0;130m

# VARIABLES

ISO_NAME 		= GoblinKernel.iso
BIN_NAME 		= GoblinKernel.bin
FLAGS 			= -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

# RULES

all: fclean
	@mkdir -p build
	@gcc -m32 $(FLAGS) -c src/kernel.c -I inc -o build/kernel.o
	@nasm -f elf32 src/boot.s -o build/boot.o
	@echo -e '$(LIGHT_PURPLE) Built $(DARK_PURPLE)GoblinKernel $(PURPLE)!'
	@ld -m elf_i386 -T src/linker.ld -o build/$(BIN_NAME) build/boot.o build/kernel.o > /dev/null 2>&1
	@echo -e '$(LIGHT_PURPLE) Linked $(DARK_PURPLE)GoblinKernel $(PURPLE)!'
	@mv build/$(BIN_NAME) GoblinKernel/boot/$(BIN_NAME)
	@grub-mkrescue -o build/$(ISO_NAME) GoblinKernel/ > /dev/null 2>&1
	@mv build/$(ISO_NAME) GoblinKernel/boot
	@echo -e '\n$(LIGHT_PURPLE)-> make run <- $(PURPLE)to start the $(DARK_PURPLE)GoblinKernel $(PURPLE)!'

re: fclean all

clean:
	@rm -rf build
	@echo -e '$(LIGHT_PURPLE) Deleted $(PURPLE)build folder !'

fclean: clean
	@rm -rf GoblinKernel/boot/$(BIN_NAME) GoblinKernel/boot/$(ISO_NAME)
	@echo -e '$(LIGHT_PURPLE) Deleted $(PURPLE)boot files !'

run:
	@qemu-system-i386 -cdrom GoblinKernel/boot/${ISO_NAME}
	@echo -e '$(LIGHT_PURPLE) Exited $(DARK_PURPLE)GoblinKernel $(PURPLE)!'
