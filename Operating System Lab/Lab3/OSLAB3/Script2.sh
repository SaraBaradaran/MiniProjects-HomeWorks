#!/bin/bash

if [ $1 == "-r" ]
then
	cat $2
elif [ $1 == "-m" ]
then
	for((i=$5;i<=$6;i++))
	do
		touch $2$3_$i.$4
	done
fi

