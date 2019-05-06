# Kernel configuration

# Compiler optimization level
OPT = 0

# Disable SMP
CFG += -DNO_SMP

# Compile for ARM
CFG += -DARM_SPEC

# Disable "logger" thread
# CFG += -DNO_LOGGER

# Disable ACPI support
# CFG += -DNO_ACPI

# Disable Intel Multiprocessor Specification parsing
# CFG += -DNO_INTEL_MPS

# Use VMX-based virtual machines for isolation
# CFG += -DUSE_VMX
