// Last edited: Dharmesh
This file contains a list of changes I have begun making to QuestOS to get things working on a Raspberry Pi. I will have things be chronological, where possible, but cannot guarantee that that will always happen, nor that every change will be documented here. Your best bet (as always) is to use `git blame`.

-- Per Sasan's advice, decided to create a separate Makefile that will target ARM exclusively for now. We will bring the x86 stuff back in later (perhaps over the summer?)
-- Removed -nostdinc from CFLAGS, since that appeard to mess up compilation when using arm-none-eabi-gcc
-- Removed -Wa,--32 from CPPFLAGS (C Pre-Processor Flags, *not* "CPlusPlus Flags", in case you forget again), since the default word size on ARMv7 is 32 bits anyway, the --32 flag is unnecessary.