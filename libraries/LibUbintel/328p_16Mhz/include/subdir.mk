################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/WInterrupts.c \
../include/wiring.c \
../include/wiring_analog.c \
../include/wiring_digital.c \
../include/wiring_pulse.c \
../include/wiring_shift.c 

CPP_SRCS += \
../include/CDC.cpp \
../include/HID.cpp \
../include/HardwareSerial.cpp \
../include/IPAddress.cpp \
../include/Print.cpp \
../include/Stream.cpp \
../include/Tone.cpp \
../include/USBCore.cpp \
../include/WMath.cpp \
../include/WString.cpp \
../include/main.cpp \
../include/new.cpp 

C_DEPS += \
./include/WInterrupts.d \
./include/wiring.d \
./include/wiring_analog.d \
./include/wiring_digital.d \
./include/wiring_pulse.d \
./include/wiring_shift.d 

OBJS += \
./include/CDC.o \
./include/HID.o \
./include/HardwareSerial.o \
./include/IPAddress.o \
./include/Print.o \
./include/Stream.o \
./include/Tone.o \
./include/USBCore.o \
./include/WInterrupts.o \
./include/WMath.o \
./include/WString.o \
./include/main.o \
./include/new.o \
./include/wiring.o \
./include/wiring_analog.o \
./include/wiring_digital.o \
./include/wiring_pulse.o \
./include/wiring_shift.o 

CPP_DEPS += \
./include/CDC.d \
./include/HID.d \
./include/HardwareSerial.d \
./include/IPAddress.d \
./include/Print.d \
./include/Stream.d \
./include/Tone.d \
./include/USBCore.d \
./include/WMath.d \
./include/WString.d \
./include/main.d \
./include/new.d 


# Each subdirectory must supply rules for building sources it contributes
include/%.o: ../include/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Users\Naresh\c-workspace\LibUbintel" -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/%.o: ../include/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Naresh\c-workspace\LibUbintel" -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


