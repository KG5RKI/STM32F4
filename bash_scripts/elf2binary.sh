if [ "$#" -ne 2 ]; then
  echo "Usage: $0 file.elf file.bin"
  exit 1
fi

arm-none-eabi-objcopy -O $1 $2
