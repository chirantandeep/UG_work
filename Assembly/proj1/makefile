# //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
#
# makefile for hello.asm
#
# the makefile is used to automate the building of the
# program. It checks the source code for errors, add all
# necessary services from the OS and convert code -> a
# sequence of machine readable instructions.
#
# The make utility words with dependency tree.
# It sees that 'hello' depends on 'hello.o' and 'hello.o'
# depends on 'hello.asm' and that 'hello.asm' depends on
# nothing else. Make compares the last modification dates
# of the two files (hello.o and hello.asm). If 'hello.asm'
# is more recent then it executes the line after 'hello.o'
# which is hello.asm. Then makes restarts reading the
# makefile from the beginning and finds that 'hello.o' is
# more recent then 'hello' and therefore it executes the
# file 'hello.o'.
#

hello: hello.o 
	gcc -o hello hello.o -no-pie
	#
	# After nasm gives an .o file, the file is linked
	# with a linker. The linker takes the code and
	# searches for system services or other object
	# files needed. Everything is combined to
	# produce an executable. The linker used is gcc.
	# By default gcc generates Position Independent
	# Executables(this type prevents hackers from
	# investigating how memory is used by a program)
	# We do not need this now, therefore '-no-pie'.
	#
hello.o: hello.asm
	nasm -f elf64 -g -F dwarf hello.asm -l hello.lst
	# 
	# Here 'nasm' is the assembler. The '-f' is the
	# output format which is 'elf64'(Executable and
	# Linkable Format for 64-bit). The '-g' means we
	# want to include debug information in a format
	# '-F' which is 'dwarf'(Debug With Arbitary
	# Recorded Format).(another format is STABS-
	# Symbol TAble Strings). '-l' tells nasm to
	# generate a .lst file to examine results. 
	# nasm will create an object file '.o' after 
	# executation.
	#
