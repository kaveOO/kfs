# COLORS

PURPLE			=	\x1b[0m\x1b[38;2;128;0;128m
LIGHT_PURPLE	=	\x1b[0m\x1b[38;2;204;153;255m
DARK_PURPLE		=	\x1b[1m\x1b[38;2;75;0;130m

# VARIABLES

ISO_NAME 		= build/GoblinKernel.iso
BIN_NAME 		= build/GoblinKernel.bin



FLAGS 			= -fno-builtin -fno-exception -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs

# RULES


clean:
	@rm -rf $(ISO_NAME) ${BIN_NAME}
	@echo -e '$(LIGHT_PURPLE) Cleaned $(DARK_PURPLE)build folder !'

fclean: clean
	@rm -rf build/
	@echo -e '$(LIGHT_PURPLE) Deleted $(DARK_PURPLE)build folder !'

run:
	@qemu-system-i386 -cdrom ${ISO_NAME}
	@echo -e '$(LIGHT_PURPLE) Exited $(DARK_PURPLE)GoblinKernel !'

