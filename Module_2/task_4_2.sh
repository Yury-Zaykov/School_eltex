#!/usr/bin/bash

stat=$(ps -x | grep $1 | grep T | awk '{ print$3 }');

var=${stat:0:1};

echo $var;

#ps -x | grep $1 | grep T | awk '{ print$3 }'

if [[ ( ${var} -eq "T" ) ]]
then
	kill -CONT $1
fi

#ps -x | grep 14722 | grep T

#echo "$1"

