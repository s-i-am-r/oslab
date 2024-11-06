#!/bin/bash

function tee_clone(){
	file="$1"
	echo "">$file

	IFS=
	while read -r line
	do
		echo $line >> $file
		echo $line
	done
		
}
tee_clone "$1"
