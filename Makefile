# COLORS

PURPLE			=	\x1b[0m\x1b[38;2;128;0;128m
LIGHT_PURPLE	=	\x1b[0m\x1b[38;2;204;153;255m
DARK_PURPLE		=	\x1b[1m\x1b[38;2;75;0;130m

# VARIABLES

ISO_NAME 		= GoblinKernel.iso
BIN_NAME 		= GoblinKernel.bin
FLAGS 			= -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

SRC_C			= $(wildcard src/*.c)
OBJ_C			= $(patsubst src/%.c,build/%.o,$(SRC_C))
OBJ_ASM			= build/boot.o

# RULES

all: fclean build/$(BIN_NAME) build/$(ISO_NAME)

build/%.o: src/%.c
	@mkdir -p build
	@gcc -m32 $(FLAGS) -c $< -I inc -o $@

$(OBJ_ASM): src/boot.s
	@mkdir -p build
	@nasm -f elf32 $< -o $@

build/$(BIN_NAME): $(OBJ_ASM) $(OBJ_C)
	@ld -m elf_i386 -T src/linker.ld -o $@ $(OBJ_ASM) $(OBJ_C) > /dev/null 2>&1
	@echo -e '$(LIGHT_PURPLE) Linked $(DARK_PURPLE)GoblinKernel $(PURPLE)!'

build/$(ISO_NAME): build/$(BIN_NAME)
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
	@qemu-system-i386 -audiodev pa,id=speaker -machine pcspk-audiodev=speaker -cdrom GoblinKernel/boot/${ISO_NAME}
	@echo -e '$(LIGHT_PURPLE) Exited $(DARK_PURPLE)GoblinKernel $(PURPLE)!'
