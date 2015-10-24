#!/bin/bash

echo "Building MentOS"
cd src
make clean && make
cd ..

echo "Generating ISO"
cp src/kernel.elf image/boot

genisoimage -R                              \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A MentOS                       \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o run/os.iso                   \
            image 
