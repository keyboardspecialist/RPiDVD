
arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -Wl,-T,rpi.x -I../../headers -o kernel.elf kmain.c cstartup.c start.s gpu.c debug.c mailbox.c interrupt.c timer.c draw2d.c pcm.c audio.s

arm-none-eabi-objcopy kernel.elf -O binary kernel.img