include config.mk
ARCH=armv7
CPU=cortex-a7
PREFIX=arm-none-eabi-
KER_SRC = ../src/kernel
ASMSOURCES = $(wildcard $(KER_SRC)/*.S)
#GRUBLIB = grub/x86_64-pc
GRUB2 = grub2
TFTPDIR=tftp
LD = $(PREFIX)ld -marmelf
RPIBOOT=rpiboot
# ifeq ($(ARCH),armv7)
# 	CC = gcc-4.8
# else
# 	CC = arm-none-eabi-gcc
# endif
CC = $(PREFIX)gcc # gcc-4.8 -- used as a litmus test
TAR = tar
#CFLAGS = -m32 -march=i586 -fno-builtin -fno-stack-protector -fno-strict-aliasing -fno-delete-null-pointer-checks -g -Wall -Wno-attributes -O$(OPT) $(CFG) $(EXTRA_CFLAGS)
CFLAGS= -marm -mcpu=$(CPU) -fpic -ffreestanding -fno-builtin -fno-stack-protector -fno-strict-aliasing -nostdlib -fno-delete-null-pointer-checks -g -Wall -Wno-attributes $(DIRECTIVES) -O$(OPT) $(CFG) $(EXTRA_CFLAGS)
#CPPFLAGS = -D_QUEST -Wa,--32 -MMD -Iinclude -Iinclude/drivers/acpi -I. -I../libc/include 
# TODO: You will need libc ported before getting sysprogs/shell to work.
CPPFLAGS = -D_QUEST -MMD -Iinclude -I../libc/include
INDENT = indent
INDENTFLAGS = -gnu -br -ce --no-tabs

##################################################

MNT_POINT=/mnt/quest
PROGS = quest
#	sysprogs/shell sysprogs/spinner sysprogs/iotest sysprogs/ipctest \
#	tests/exec tests/race tests/test1 tests/test2 \
#	tests/test3 tests/test4 tests/test5 tests/test6 tests/test7

##################################################
#	drivers/usb/uhci_hcd.o drivers/usb/uvc.o drivers/usb/umsc.o \
#	drivers/usb/hub.o drivers/usb/net.o drivers/usb/asix.o \
#	drivers/usb/ftdi.o drivers/usb/pl2303.o \
#	drivers/usb/rtl8187b.o \
#	drivers/usb/usb_tests.o \
#	drivers/usb/usb.o drivers/usb/enumeration.o \
#	drivers/sb16/sound.o \
#	drivers/acpi/quest-acpica.o \
#	drivers/eeprom/93cx6.o \
# 	drivers/pci/pci.o drivers/pci/pci_irq.o \
#	drivers/net/ethernetif.o drivers/net/pcnet.o \
#	drivers/net/e1000.o drivers/net/e1000e.o \
#	drivers/net/bnx2.o drivers/net/r8169.o \
#	drivers/net/mac80211.o drivers/net/netsetup.o \
#	drivers/ata/ata.o drivers/ata/diskio.o \
#	drivers/input/keyboard_8042.o drivers/input/keymap.o \
#	drivers/serial/mcs9922.o \
# 	util/cpuid.o util/printf.o util/screen.o util/debug.o util/circular.o \
#	util/crc32.o util/bitrev.o \
#	util/cpuid.o util/printf.o util/screen.o util/debug.o util/circular.o \
#	util/crc32.o util/bitrev.o \
#	vm/vmx.o vm/vm86.o vm/code16.o \
#	util/logger.o util/perfmon.o \
#	sched/vcpu.o
#	kernel.o module/loader.o \
#	interrupt.o interrupt_handler.o \
#	smp/boot-smp.o smp/smp.o smp/intel.o smp/acpi.o smp/apic.o smp/semaphore.o \
#	sched/task.o sched/sched.o sched/sleep.o  sched/ipc.o \
#	mem/physical.o mem/virtual.o mem/pow2.o \
#	fs/fsys.o \
#	fs/ext2/fsys_ext2fs.o \
#	fs/iso9660/fsys_iso9660.o \
#	fs/vfat/fsys_vfat.o \
#	fs/tftp/fsys_tftp.o \
#	kdb/i386-stub.o


libuspi.a: $(OBJS)
	@echo "  AR    $@"
	@rm -f $@
	@$(AR) cr $@ $(OBJS)


OBJS =  boot/boot.o boot/init.o atag/atag.o \
	drivers/uart/uart.o mem/mem.o gpu/gpu.o \
	common/dstdlib.o \
	raspi/mailbox.o raspi/interrupts.o raspi/timer.o raspi/process.o \
	raspi/framebuffer.o raspi/interrupt_vector.o raspi/process_asm.o raspi/lock_asm.o \
	util/kerio.o module/loader.o

#OBJS += $(patsubst $(KER_SRC)/%.S, $(OBJ_DIR)/%.o, $(ASMSOURCES))
CFILES = $(patsubst %.o,%.c,$(OBJS))
DFILES = $(patsubst %.o,%.d,$(OBJS))
MAPFILES = $(patsubst %.o,%.map,$(OBJS))

##################################################

# ACPI_SRCS = $(shell ls drivers/acpica/*.c)
# ACPI_OBJS = $(patsubst %.c,%.o,$(ACPI_SRCS))
# ACPI_DEPS = $(patsubst %.c,%.d,$(ACPI_SRCS))

##################################################
#LIBLWIP = lwip.a

# LWIP_CFILES = \
#   lwip/api/netbuf.c \
#   lwip/api/api_msg.c \
#   lwip/api/tcpip.c \
#   lwip/api/sockets.c \
#   lwip/api/netdb.c \
#   lwip/api/netifapi.c \
#   lwip/api/err.c \
#   lwip/api/api_lib.c \
#   lwip/core/dhcp.c \
#   lwip/core/tcp_in.c \
#   lwip/core/pbuf.c \
#   lwip/core/netif.c \
#   lwip/core/tcp.c \
#   lwip/core/dns.c \
#   lwip/core/stats.c \
#   lwip/core/tcp_out.c \
#   lwip/core/raw.c \
#   lwip/core/sys.c \
#   lwip/core/mem.c \
#   lwip/core/ipv4/inet.c \
#   lwip/core/ipv4/ip.c \
#   lwip/core/ipv4/icmp.c \
#   lwip/core/ipv4/ip_addr.c \
#   lwip/core/ipv4/igmp.c \
#   lwip/core/ipv4/autoip.c \
#   lwip/core/ipv4/ip_frag.c \
#   lwip/core/ipv4/inet_chksum.c \
#   lwip/core/init.c \
#   lwip/core/memp.c \
#   lwip/core/udp.c \
#   lwip/netif/ethernetif.c \
#   lwip/netif/slipif.c \
#   lwip/netif/loopif.c \
#   lwip/netif/etharp.c

# LWIP_OBJS = $(patsubst %.c,%.o,$(LWIP_CFILES))
# LWIP_DEPS = $(patsubst %.c,%.d,$(LWIP_CFILES))

##################################################

.PHONY: all tags clean cleanacpi cleanlwip vmware cleanall indent netboot

all: $(PROGS)

quest: $(OBJS) $(ACPI_OBJS) $(LWIP_OBJS)
	rm -f quest
	$(LD) -Map quest.map -T ldscripts/quest-arm.ld -L ./include -luspi -luspienv -o $@ $^ 

%: %.o
	$(LD) -o $@ $< -T ldscripts/module.ld -Map $@.map

%: %.c

# %.o: %.dats
# 	$(ATSCC) $(ATSFLAGS) -fno-builtin -m32 -o $@ -c $^

install: $(PROGS)
	cp $(PROGS) welcome.raw $(MNT_POINT)/boot
	sync

vmware: install quest.iso
	qemu-img convert c.img -O vmdk c-img.vmdk
	cp c-img.vmdk /mnt/hgfs/shared/quest/
	cp quest.iso /mnt/hgfs/shared/quest/

quest-raspi.iso: quest $(PROGS) iso-grub.cfg
	mkdir -p iso/boot/grub 
	cp iso-grub.cfg iso/boot/grub/grub.cfg
	cp $(GRUB2)/eltorito.img iso/boot/grub/
	$(TAR) -C iso/boot/grub -jxf $(GRUB2)/mods.tar.bz2
	cp $(PROGS) welcome.raw iso/boot/ 
	mkisofs -quiet $(MSINFO) \
		-R -b boot/grub/eltorito.img \
		-no-emul-boot -boot-load-size 4 \
		-boot-info-table -o $@ iso

quest.iso: quest $(PROGS) iso-grub.cfg
	mkdir -p iso/boot/grub 
	cp iso-grub.cfg iso/boot/grub/grub.cfg
	cp $(GRUB2)/eltorito.img iso/boot/grub/
	$(TAR) -C iso/boot/grub -jxf $(GRUB2)/mods.tar.bz2
	cp $(PROGS) welcome.raw iso/boot/ 
	mkisofs -quiet $(MSINFO) \
		-R -b boot/grub/eltorito.img \
		-no-emul-boot -boot-load-size 4 \
		-boot-info-table -o $@ iso

indent:
	(for f in $(CFILES); do [ -f "$$f" ] && $(INDENT) $(INDENTFLAGS) "$$f"; done)

tags:
	find . -name '*.[ch]' | xargs etags -o TAGS 
	find . -name '*.[ch]' | xargs ctags -o tags

clean:
	-rm -f $(OBJS) $(DFILES) $(MAPFILES) $(PROGS) quest.iso quest.map
	-rm -rf iso tftp

cleanacpi:
	-rm -f $(ACPI_OBJS) $(ACPI_DEPS)

cleanall: clean cleanacpi cleanlwip

define ACPI_template
$(1): $(patsubst %.o,%.c,$(1))
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $$@ -c $$^
endef

$(foreach obj,$(ACPI_OBJS),$(eval $(call ACPI_template,$(obj))))

raspi: quest-raspi.iso
ifeq ($(ARCH),armv7)
	# Arm specific stuff here
endif
	mkdir -p $(TFTPDIR)/boot/grub
	#cp quest sysprogs/shell $(TFTPDIR)/boot
	cp netboot/grub.cfg $(TFTPDIR)/boot/grub
	cp $(GRUB2)/grub2pxe $(TFTPDIR)
	$(TAR) -C $(TFTPDIR)/boot/grub -jxf $(GRUB2)/mods.tar.bz2
	mv quest-raspi.iso tftp/
	cp qemu.sh tftp/

netboot: quest.iso
ifeq ($(ARCH),armv7)
	# Arm specific stuff here
endif
	mkdir -p $(TFTPDIR)/boot/grub
	cp quest sysprogs/shell $(TFTPDIR)/boot
	cp netboot/grub.cfg $(TFTPDIR)/boot/grub
	cp $(GRUB2)/grub2pxe $(TFTPDIR)
	$(TAR) -C $(TFTPDIR)/boot/grub -jxf $(GRUB2)/mods.tar.bz2
	mv quest.iso tftp/
	cp qemu.sh tftp/
##################################################
# LWIP
$(LIBLWIP): $(LWIP_OBJS)
	$(AR) r $@ $(LWIP_OBJS)
	ranlib $@

cleanlwip:
	-rm -f $(LWIP_OBJS) $(LWIP_DEPS) $(LIBLWIP)

##################################################

config.mk: default-config.mk
	cp -f default-config.mk config.mk

#-include $(shell find . -name '*.d')
