################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Applications/Arduino.app/Contents/Resources/Java/libraries/LiquidCrystal/src/LiquidCrystal.cpp 

CPP_DEPS += \
./Libraries/LiquidCrystal/src/LiquidCrystal.cpp.d 

LINK_OBJ += \
./Libraries/LiquidCrystal/src/LiquidCrystal.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/LiquidCrystal/src/LiquidCrystal.cpp.o: /Applications/Arduino.app/Contents/Resources/Java/libraries/LiquidCrystal/src/LiquidCrystal.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/avr/cores/arduino" -I"/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/avr/variants/standard" -I"/Applications/Arduino.app/Contents/Resources/Java/libraries/LiquidCrystal" -I"/Applications/Arduino.app/Contents/Resources/Java/libraries/LiquidCrystal/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


