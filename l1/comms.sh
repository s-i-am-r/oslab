#!/bin/env bash

list=("ls" "cd" "man" "touch" "chmod" "cat")
read  cc
read -r -a  ar <<< "$cc"
found=""
for i in ${ar[@]} ; do
	if [ ${ar[0]} == $i ]; then
		found=" "
		break
	fi

done

if [[ $found ]]; then 
	echo "found"
	$cc
else
	echo "try again..."  "${list[@]}"

fi
