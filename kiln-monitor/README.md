# Kiln Monitor

Utility for monitoring a kiln for when it is on/off. The currently targeted kiln is 240 volts with a light and a cone controlled switch. 


Current strategy is to take a picture of the light with a webcam, then process the image to tell if the light is on.

## Dependancies

Kiln Monitor uses the folowing libraries:
ImageMagick
fswebcam

### Network
https://github.com/Ybalrid/kissnet

### Needed packages

	sudo git cmake build-essential

## Build
	cmake .
	make

## Home Assistant configuration
TODO add steps for HA config

## Installation
TODO add install steps (probably for raspberry pi)
