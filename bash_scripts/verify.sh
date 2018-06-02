if [ "$#" -ne 1 ]; then
  echo "Usage: $0 file.elf" >&2
  exit 1
fi

arm-none-eabi-size -tA main.elf
