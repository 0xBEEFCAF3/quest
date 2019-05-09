#!/bin/bash
#qemu-system-i386 -boot n -s -smp 4 -net nic,model=pcnet -net user,tftp=tftp,bootfile=grub2pxe -cdrom quest.iso
qemu-system-arm -M raspi2 -m 256M  -kernel quest.elf -serial stdio
