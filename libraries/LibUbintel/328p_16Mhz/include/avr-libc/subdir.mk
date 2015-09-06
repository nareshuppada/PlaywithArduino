################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/avr-libc/malloc.c \
../include/avr-libc/realloc.c 

C_DEPS += \
./include/avr-libc/malloc.d \
./include/avr-libc/realloc.d 

OBJS += \
./include/avr-libc/malloc.o \
./include/avr-libc/realloc.o 


# Each subdirectory must supply rules for building sources it contributes
include/avr-libc/%.o: ../include/avr-libc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Naresh\c-workspace\LibUbintel" -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


