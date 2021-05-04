################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/leon3_bprint.c \
../src/leon3_uart.c \
../src/prac5_2.c 

OBJS += \
./src/leon3_bprint.o \
./src/leon3_uart.o \
./src/prac5_2.o 

C_DEPS += \
./src/leon3_bprint.d \
./src/leon3_uart.d \
./src/prac5_2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C Compiler'
	sparc-rtems-gcc -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/moni/workspace/prac5_2/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


