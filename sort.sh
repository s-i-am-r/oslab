#!/bin/bash

function merge() {
	LC_COLLATE=C
	exec 3<<<"$1"
	exec 4<<<"$2"
	IFS=
	line1=
	line2=
	while true; do

		[ -z "$line1" ] && read -r line1 <&3
		[ -z "$line2" ] && read -r line2 <&4

		if [ -z "$line1" ]; then
			[ -n "$line2" ] && cat <<< "$line2"
			cat <&4
			return
		elif [ -z "$line2" ]; then
			[ -n "$line1" ] && cat<<<"$line1"
			cat <&3
			return
		fi

		if [[ $line1 < $line2 ]]; then
			cat <<< "$line1"
			line1=
		else
			cat <<< "$line2"
			line2=
		fi

	done
}

function merge_sort() {
	file="$(cat <&0)"
	
	n="$(./wc_clone.sh -l <<< "$file")"
	if ((  $n <= 1 )) ; then 
		echo "$file"
		return
	fi
	n="$((n / 2))"
	f1="$(head -n "$n" <<< "$file" | merge_sort)"
	f2="$(tail -n "+"$((n + 1)) <<< "$file" | merge_sort)"
	
	# echo "$f1"$'\n'"$f2"
	merge "$f1" "$f2"

}

# if [[ -f $1 ]]; then
# 	cat "$1" | merge_sort
# else
# 	merge_sort
# fi
