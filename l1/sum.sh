#!/bin/env bash
n=$1
sum=0
while [[ $n -gt 0 ]] ;do
	sum=$((sum + ${n: -1} ))
	n=${n::-1}
done
echo $sum
