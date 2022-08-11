RM := rm -rf

COMPILER_PREFIX ?= riscv-none-embed

PROJECT = HydraUSB3_Blink_ULED

RVMSIS_DIR   = ../SRC/RVMSIS
RVMSIS_SRCS  = $(wildcard $(RVMSIS_DIR)/*.c)
OBJS        += $(patsubst $(RVMSIS_DIR)/%.c,%.o,$(RVMSIS_SRCS))

PERIPH_DIR   = ../SRC/Peripheral
PERIPH_SRCS  = $(wildcard $(PERIPH_DIR)/src/*.c)
OBJS        += $(patsubst $(PERIPH_DIR)/src/%.c,%.o,$(PERIPH_SRCS))

USER_DIR     = ./User
USER_SRCS    = $(wildcard $(USER_DIR)/*.c)
OBJS        += $(patsubst $(USER_DIR)/%.c,%.o,$(USER_SRCS))

C_SRCS = $(RVMSIS_SRCS) $(PERIPH_SRCS) $(USER_SRCS)

# All of the sources participating in the build are defined here
OBJS += startup_CH56x.o
DEPS  = $(subst .o,.d,$(OBJS))
LIBS  =

DEBUG       = -g -DDEBUG=1
BASE_OPTS   = -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections
C_OPTS      = $(BASE_OPTS) $(DEBUG) \
              $(INCLUDES) -std=gnu99 -MMD -MP -MT"$(@)"
LD_OPTS     = -T ".ld" -nostartfiles -Xlinker --gc-sections  -Xlinker --print-memory-usage -Wl,-Map,"$(PROJECT).map" --specs=nano.specs --specs=nosys.specs

INCLUDES = \
  -I"$(RVMSIS_DIR)" \
  -I"$(PERIPH_DIR)/inc" \
  -I"../SRC/Startup"

# Add inputs and outputs from these tool invocations to the build variables
SECONDARY_FLASH += \
$(PROJECT).hex \
$(PROJECT).bin \

SECONDARY_LIST += \
$(PROJECT).lst \

SECONDARY_SIZE += \
$(PROJECT).siz \

SECONDARY_MAP += \
$(PROJECT).map \

SECONDARY_OUTPUTS = $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE) $(SECONDARY_MAP)
secondary-outputs: $(SECONDARY_OUTPUTS)

# All Target
all: $(PROJECT).elf secondary-outputs

startup_CH56x.o: ../SRC/Startup/startup_CH56x.S
	@echo 'Building file: $<'
	$(COMPILER_PREFIX)-gcc $(C_OPTS) -x assembler -c -o "$@" "$<"
	@echo ' '

%.o: ./User/%.c
	@echo $(OBJS)
	@echo 'Building file: $<'
	$(COMPILER_PREFIX)-gcc $(C_OPTS) -c -o "$@" "$<"
	@echo ' '

%.o: ../SRC/RVMSIS/%.c
	@echo 'Building file: $<'
	$(COMPILER_PREFIX)-gcc $(C_OPTS) -c -o "$@" "$<"
	@echo ' '

%.o: ../SRC/Peripheral/src/%.c
	@echo 'Building file: $<'
	$(COMPILER_PREFIX)-gcc $(C_OPTS) -c -o "$@" "$<"
	@echo ' '

# Tool invocations
$(PROJECT).elf: $(OBJS)
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	$(COMPILER_PREFIX)-gcc $(BASE_OPTS) $(LD_OPTS) -o "$(PROJECT).elf" $(OBJS) $(LIBS)
	@echo ' '

$(PROJECT).hex: $(PROJECT).elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	$(COMPILER_PREFIX)-objcopy -O ihex "$(PROJECT).elf"  "$(PROJECT).hex"
	@echo 'Finished building: $@'
	@echo ' '

$(PROJECT).bin: $(PROJECT).elf
	-@echo 'Create Flash Image BIN'
	-$(COMPILER_PREFIX)-objcopy -O binary "$(PROJECT).elf"  "$(PROJECT).bin"
	-@echo ' '

$(PROJECT).lst: $(PROJECT).elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	$(COMPILER_PREFIX)-objdump --source --all-headers --demangle --line-numbers --wide "$(PROJECT).elf" > "$(PROJECT).lst"
	@echo 'Finished building: $@'
	@echo ' '

$(PROJECT).siz: $(PROJECT).elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	$(COMPILER_PREFIX)-size --format=berkeley "$(PROJECT).elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS) $(DEPS) $(SECONDARY_OUTPUTS) $(PROJECT).elf
	-@echo ' '

.PHONY: all clean dependents
