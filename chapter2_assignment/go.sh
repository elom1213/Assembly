#!/bin/bash

nasm -f elf64 print_uint.asm -o  print_uint.o
ld -o print_uint print_uint.o
chmod 755 print_uint