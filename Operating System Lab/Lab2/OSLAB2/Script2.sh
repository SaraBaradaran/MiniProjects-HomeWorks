#!/bin/bash

if ! [ -d $3 ]
then
	mkdir $3
fi

cp -a $1/. $3
echo All $1 files copied to $3
cp -a $2/. $3
echo All $2 files copied to $3
ls $3 | less


