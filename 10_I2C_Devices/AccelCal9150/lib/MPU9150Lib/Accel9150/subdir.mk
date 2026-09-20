################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
C:\Eclipse\ for\ Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\MPU9150Lib\Accel9150\Accel9150.ino 

INO_DEPS += \
.\libraries\MPU9150Lib\Accel9150\Accel9150.ino.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\MPU9150Lib\Accel9150/Accel9150.o: C:\Eclipse\ for\ Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\MPU9150Lib\Accel9150\Accel9150.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Eclipse for Arduino\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\cores\arduino" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\variants\standard" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\MPU9150Lib" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\CalLib" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire\src" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\EEPROM" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\EEPROM\src" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\I2CDev" -I"C:\Eclipse for Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\MotionDriver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


