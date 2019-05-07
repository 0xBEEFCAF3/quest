#!/bin/bash
qemu-system-i386 -boot n -s -smp 4 -net nic,model=pcnet -net user,tftp=tftp,bootfile=grub2pxe -cdrom quest.iso
