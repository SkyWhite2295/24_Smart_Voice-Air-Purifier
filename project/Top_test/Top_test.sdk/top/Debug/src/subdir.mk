################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/asr.c \
../src/dht.c \
../src/forcast.c \
../src/jq.c \
../src/oled.c \
../src/pm.c \
../src/top.c \
../src/tts.c 

OBJS += \
./src/asr.o \
./src/dht.o \
./src/forcast.o \
./src/jq.o \
./src/oled.o \
./src/pm.o \
./src/top.o \
./src/tts.o 

C_DEPS += \
./src/asr.d \
./src/dht.d \
./src/forcast.d \
./src/jq.d \
./src/oled.d \
./src/pm.d \
./src/top.d \
./src/tts.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../top_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


