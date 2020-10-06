################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../detrimis/WearhouseManager.c \
../detrimis/app.c \
../detrimis/test.c 

OBJS += \
./detrimis/WearhouseManager.o \
./detrimis/app.o \
./detrimis/test.o 

C_DEPS += \
./detrimis/WearhouseManager.d \
./detrimis/app.d \
./detrimis/test.d 


# Each subdirectory must supply rules for building sources it contributes
detrimis/%.o: ../detrimis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


