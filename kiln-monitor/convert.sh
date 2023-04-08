#!/bin/bash

IMAGE=${1:-img.jpg}
THRESHOLD=${2:-25}

#mogrify -format bmp "$IMAGE"
#rm "$IMAGE"

convert "$IMAGE" -channel R -separate img_red.bmp
convert "$IMAGE" -channel G -separate img_green.bmp
convert "$IMAGE" -channel B -separate img_blue.bmp

convert img_blue.bmp img_red.bmp -compose minus -composite minus.bmp
convert img_green.bmp img_red.bmp -compose minus -composite minus2.bmp
convert minus2.bmp minus.bmp -compose minus -composite minus3.bmp
convert minus3.bmp -threshold "${THRESHOLD}%" thresh.bmp

found=$(convert thresh.bmp -format %c histogram:info:- | sed '/000000/d;s/:.*//;s/[[:space:]]*//g')

if [[ $found > 30 ]] ; then
    echo "ON"
else
    echo "OFF"
fi



