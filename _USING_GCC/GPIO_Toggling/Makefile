stm_file.bin: stm_file.elf
	arm-none-eabi-objcopy -O binary stm_file.elf stm_file.bin

stm_file.elf:
	arm-none-eabi-gcc ./Src/* ./Drivers/Src/GPIO_lib.c ./Drivers/Src/TIMER_lib.c ./Startup/startup_stm32f303vctx.s -T STM32F303VCTX_FLASH.ld -I ./Drivers/Inc/ -o stm_file.elf -mcpu=cortex-m4 -mthumb

flash:
	st-flash write stm_file.bin 0x08000000
clean:
	rm stm_file.*
