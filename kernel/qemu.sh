#!/bin/bash
qemu-system-x86_64 -boot n -net nic,model=pcnet -net user,tftp=tftp,bootfile=grub2/grub2pxe -cdrom quest.iso 
