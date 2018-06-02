if [ "$#" -ne 1 ]; then
  echo "Usage: $0 file.bin"
  exit 1
fi

st-flash write $1 0x8000000
