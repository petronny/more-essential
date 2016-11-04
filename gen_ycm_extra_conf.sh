#!/bin/sh
MAKEFILE="makefile.ycm"
rm -f .ycm_extra_conf.py
pebble clean 1>/dev/null 2>&1
echo 'all:' > $MAKEFILE
pebble build -v 2>&1 | grep runner >> $MAKEFILE
sed \
	-e 's/\[//g' \
	-e 's/\]//g' \
	-e "s/[']//g" \
	-e "s/, / /g" \
	-e 's/^.*runner/\t/g' \
	-e 's/-D__FILE_NAME__="\([^"]*\)"/-D__FILE_NAME__=\\"\1\\"/g' \
	-e 's/arm-none-eabi-gcc/$(CC)/g' \
	-e 's/ src/ build\/src/g' \
	-e 's/\.\.\/src/src/g' \
	-e 's/ basalt/ build\/basalt/g' \
	-e 's/pebble-app\.map/build\/pebble-app.map/g' \
	-i $MAKEFILE
CC=arm-none-eabi-gcc make -f $MAKEFILE
CC=arm-none-eabi-gcc ycm_generator -b make -M="-f $MAKEFILE" .
rm $MAKEFILE
