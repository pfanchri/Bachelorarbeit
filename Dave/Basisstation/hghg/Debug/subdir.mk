################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.o 

C_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVEv4-64Bit\DAVE-4.2.6\eclipse\ARM-GCC-49/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4500_F100x1024 -I"D:\Bachelorarbeit\Dave\Basisstation\hghg\Libraries\XMCLib\inc" -I"D:\Bachelorarbeit\Dave\Basisstation\hghg/Libraries/CMSIS/Include" -I"D:\Bachelorarbeit\Dave\Basisstation\hghg/Libraries/CMSIS/Infineon/XMC4500_series/Include" -I"D:\Bachelorarbeit\Dave\Basisstation\hghg" -I"D:\Bachelorarbeit\Dave\Basisstation\hghg\Libraries" -I"D:\Bachelorarbeit\Dave\Basisstation\hghg\Dave\Generated" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo.

