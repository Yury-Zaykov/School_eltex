#!/usr/bin/bash

echo "Hi, in which dir do you want to create the folders and files:"

outs_dir=dir_ex
ins_dir=i_dir_in
ins_files=file

read ce_dir

while [[ !( -e $ce_dir ) ||  !( -d $ce_dir ) ]]
do
	echo -e "Path name error! \n"
	echo "Want to re-enter the path to the dir(yes/no):"
	read choose
	if [[ $choose == yes ]]
	then
		echo "Please enter a dir:"
		read ce_dir
	else
		exit 0
	fi
done

echo -e "\nHow many external dir do you want to create:"
read ex_dir

while [[ ( "$ex_dir" -le 0 ) || ( "$ex_dir" -gt 1001 ) ]]
do
	echo -e "So match dir or value less then 0! \n"
	echo "Want to re-enter a count to the dir(yes/no):"
	read choose
	if [[ $choose == yes ]]
	then
		echo "Please enter a count dir:"
		read ex_dir
	else
		ex_dir=50
		break
	fi
done

echo -e "\nEnter the names of external folder templates:"

read outs_dir

echo -e "\nHow many internal folders do you want to create:"
read in_dir

while [[ ( $in_dir -le 0 ) || ( $in_dir -gt 1001) ]]
do
	echo -e "So match dir or value less then 0! \n"
	echo "Want to re-enter a count to the dir(yes/no):"
	read choose
	if [[ $choose == yes ]]
	then
		echo "Please enter a count dir:"
		read ex_dir
	else
		in_dir=100
		break
	fi
done

echo -e "\nEnter the names of internal folder templates:"

read ins_dir

echo -e "\nHow many files do you want to create:"
read in_files

while [[ ( $in_files -le 0 ) || ( $in_files -gt 501) ]]
do
	echo -e "So match files or value less then 0! \n"
	echo "Want to re-enter a count to the files(yes/no):"
	read choose
	if [[ $choose == yes ]]
	then
		echo "Please enter a count files:"
		read in_files
	else
		in_files=200
		break
	fi
done

echo -e "\nEnter template names for files:"

read ins_files

echo -e "\nCreating files and dir"

p=1
sp="/-\|"
echo -n ' '

for ((i=1; i<$ex_dir+1; i++))
do
	mkdir ${ce_dir}/${outs_dir}${i}
	for ((j=1; j<in_dir+1; j++))
	do
		mkdir ${ce_dir}/${outs_dir}${i}/${ins_dir}${j}
		for ((k=1; k<in_files+1; k++))
		do
			touch ${ce_dir}/${outs_dir}${i}/${ins_dir}${j}/${ins_files}${k}
			printf "\b${sp:p++%${#sp}:1}"	
		done
	done
done

echo -e "/nFiles and dir created!"

exit 0
