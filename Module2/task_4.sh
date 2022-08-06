#!/usr/bin/bash

echo "Enter the parameters in the format hh mm PID"

read hh mm name_PID

crontab -l > foocron

#bash ~/study_linux/task_4(2).sh name_PID

if [[ ( ${hh} -eq 0 ) && ( ${mm} -eq 0 ) ]]
then
	echo "* * * * * bash ~/study_linux/task_4_2.sh ${name_PID}" >> foocron	
elif [[ ( ${hh} -eq 0 ) ]]
then
	echo "*/${mm} * * * * bash ~/study_linux/task_4_2.sh ${name_PID}" >> foocron
elif [[ ( ${mm} -eq 0 ) ]]
then
	echo "* */${hh} * * * bash ~/study_linux/task_4_2.sh ${name_PID}" >> foocron
fi

crontab foocron

#rm foocron


