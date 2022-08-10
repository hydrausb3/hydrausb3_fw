RM := rm -rf

COMPILER_PREFIX ?= riscv-none-embed

PROJECT = HydraUSB3_Blink_ULED

# BSP
C_SRCS += ../SRC/RVMSIS/core_riscv.c
OBJS   += core_riscv.o

C_SRCS += \
../SRC/Peripheral/src/CH56x_bsp.c \
../SRC/Peripheral/src/CH56x_bus8.c \
../SRC/Peripheral/src/CH56x_clk.c \
../SRC/Peripheral/src/CH56x_debug_log.c \
../SRC/Peripheral/src/CH56x_dvp.c \
../SRC/Peripheral/src/CH56x_ecdc.c \
../SRC/Peripheral/src/CH56x_emmc.c \
../SRC/Peripheral/src/CH56x_flash.c \
../SRC/Peripheral/src/CH56x_gpio.c \
../SRC/Peripheral/src/CH56x_hspi.c \
../SRC/Peripheral/src/CH56x_hydrausb3.c \
../SRC/Peripheral/src/CH56x_pwm.c \
../SRC/Peripheral/src/CH56x_pwr.c \
../SRC/Peripheral/src/CH56x_serdes.c \
../SRC/Peripheral/src/CH56x_spi.c \
../SRC/Peripheral/src/CH56x_sys.c \
../SRC/Peripheral/src/CH56x_timer.c \
../SRC/Peripheral/src/CH56x_uart.c

OBJS += \
  CH56x_bsp.o \
  CH56x_bus8.o \
  CH56x_clk.o \
  CH56x_debug_log.o \
  CH56x_dvp.o \
  CH56x_ecdc.o \
  CH56x_emmc.o \
  CH56x_flash.o \
  CH56x_gpio.o \
  CH56x_hspi.o \
  CH56x_hydrausb3.o \
  CH56x_pwm.o \
  CH56x_pwr.o \
  CH56x_serdes.o \
  CH56x_spi.o \
  CH56x_sys.o \
  CH56x_timer.o \
  CH56x_uart.o

# All of the sources participating in the build are defined here
C_SRCS += ./User/Main.c
OBJS   += Main.o startup_CH56x.o
DEPS   = $(subst .o,.d,$(OBJS))
LIBS   =

DEBUG  = -g -DDEBUG=1
C_OPTS = -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 \
         -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections \
         $(INCLUDES) $(DEBUG) -std=gnu99 -MMD -MP -MT"$(@)"

INCLUDES = \
  -I"../SRC/RVMSIS" \
  -I"../SRC/Peripheral/inc" \
  -I"../SRC/Startup" \
  -I"../SRC/Peripheral/inc"

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
$(PROJECT).elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	$(COMPILER_PREFIX)-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T ".ld" -nostartfiles -Xlinker --gc-sections  -Xlinker --print-memory-usage -Wl,-Map,"$(PROJECT).map" --specs=nano.specs --specs=nosys.specs -o "$(PROJECT).elf" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

$(PROJECT).hex: $(PROJECT).elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	$(COMPILER_PREFIX)-objcopy -O ihex "$(PROJECT).elf"  "$(PROJECT).hex"
	@echo 'Finished building: $@'
	@echo ' '

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

post-build:
	-@echo 'Create Flash Image BIN'
	-$(COMPILER_PREFIX)-objcopy -O binary "$(PROJECT).elf"  "$(PROJECT).bin"
	-@echo ' '

.PHONY: all clean dependents post-build
