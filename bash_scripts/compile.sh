if [ "$#" -ne 2 ]; then
  echo "Usage: $0 file.c file.elf"
  exit 1
fi

arm-none-eabi-gcc -std=gnu99 -g -O2 -Wall -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4 -fsingle-precision-constant -Wdouble-promotion $1 -o $2
