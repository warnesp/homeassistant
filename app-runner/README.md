# AppRunner

Listens on a UDP port for commands. When received, it runs a pre-configured command.


## Dependancies

AppRunner uses the folowing libraries:

### JSON
https://github.com/nlohmann/json

### Network
https://github.com/Ybalrid/kissnet

### Needed packages

	sudo apt install git cmake build-essential

## Build
	cmake .
	make

## Home Assistant configuration

Here is an example configuration in the home assistant configuration file.

	shell_command:
    	launch_netflix: printf "netflix" | nc -u -w 1 10.0.0.29 5577
	    launch_amazon: printf "amazon" | nc -u -w 1 10.0.0.29 5577
    	launch_crunchyroll: printf "crunchyroll" | nc -u -w 1 10.0.0.29 5577
	    launch_disney: printf "disney" | nc -u -w 1 10.0.0.29 5577
	    launch_disney: printf "youtube" | nc -u -w 1 10.0.0.29 5577
	    launch_disney: printf "hulu" | nc -u -w 1 10.0.0.29 5577
	    launch_disney: printf "youtubekids" | nc -u -w 1 10.0.0.29 5577

Create Scripts that run each shell\_command. Alexa will show the scripts as Scenes in the Alexa app. You can run the script by saying "Alexa Run \<\<script name\>\>".



