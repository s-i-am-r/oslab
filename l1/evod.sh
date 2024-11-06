#!/bin/env bash
n=$1
ev=()
od=()
for (( i=0 ; i<= n ; i++ )); do
	if [[ $(( i % 2)) -eq 0  ]]; then
		ev+=($i)
	else
		od+=($i)
	fi
done

echo "even" "${ev[@]}"
echo "odd" "${od[@]}"
