#!/bin/bash

function lines() {
	i=0
	p=
	IFS=
	while true; do
		read -r x
		if (($?)); then
			break
		else
			i=$((i + 1))

		fi

	done
	# if [[ $x ]]; then
	# 	((i++))
	# fi
	echo "$i"
}
function words() {
	i=0
	while read -r x; do
		echo "$x"
		read -r -a d <<<$x

		i=$((i + "${#d[@]}"))
	done

	echo "$i"
}

function longest() {
	l=0
	i=0
	IFS=
	while read -r -d '' -n 1 x; do
		echo "$x:$i"
		if [[ "$x" == $'\n' ]]; then
			if [[ $i -gt $l ]]; then
				l=$i
			fi
			i=0
			continue
		fi
		((i++))
	done
	echo "$l"

}

case $1 in
-l)
	lines
	;;
-w)
	words
	;;
-ll)
	longest
	;;
*)
	echo "invalid usage!"
	;;

esac
