# Kernel configuration

# Compiler optimization level
OPT = 0

# Disable SMP
CFG += -DNO_SMP

# Compile for ARM
CFG += -DARM_SPEC

# Get rid of Quest-V for now
CFG += -DNO_QUESTV

# Disable USB Support: ARM Specific 
CFG += -DNO_USB
# Disable "logger" thread
# CFG += -DNO_LOGGER

# Disable ACPI support
# CFG += -DNO_ACPI

# Disable Intel Multiprocessor Specification parsing
#CFG += -DNO_INTEL_MPS

# Use VMX-based virtual machines for isolation
# CFG += -DUSE_VMX
