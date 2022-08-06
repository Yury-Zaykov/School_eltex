#!/usr/bin/bash

echo "Specify the path to the file:"

read sound

while [[ !( -e ${sound} ) || !( -f ${sound} ) ]]
do
	echo -e "File input error \n"
	echo "Want to re-enter the path to the file(yes/no):"
	read choose
	if [[ $choose == yes ]]
	then
		echo "Please enter path to the file:"
		read sound
	else
		exit 0
	fi
done

echo "play $sound" > ~/for_at.sh

chmod +x ~/for_at.sh

echo -e "\nEnter the time in the format hh mm MMDDYY:"

read hh mm yy 

at ${hh}:${mm} ${yy} -f ~/for_at.sh

#play $sound

# /home/yruy/Downloads/The_Weeknd.mp3
