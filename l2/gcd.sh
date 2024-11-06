#!/bin/env bash


find_gcd(){
	if [[ $q1 -gt $q2 ]];then 
		q1=$1
		q2=$2
	else
		q1=$2
		q2=$1
	fi
	rem=$(( $q1%$q2 ))
	if [[ $rem -eq 0 ]]; then
		echo $q2
	else
		echo $( find_gcd $q2 $rem )
	fi

}
find_gcd $1 $2



