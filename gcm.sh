#!/bin/bash
gcd () {
echo "Enter 1st number :"
read a
echo "Enter 2nd number :"
read b
m=1
n=$(( a > b ? b : a ))
for ((i=n; i>0; i--))
do
    if [[ $((a % n)) -eq 0 && $((b % n)) -eq 0 ]]; then
    m=$i
    break
fi

done
echo "THE GCD IS $m"
}
gcd


