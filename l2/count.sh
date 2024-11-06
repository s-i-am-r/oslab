#!/bin/bash
printf "no of word: %d\n" $( cat "$1" | wc -w )
printf "no of chars: %d\n" $( cat "$1" | wc -c )
printf "no of spaces: %d\n" $( cat "$1" | tr -cd ' ' | wc -c )
printf "no of special chars: %d\n" $( cat "$1" | tr -d 'a-z,A-Z,0-9,\n, ' | wc -c )
body=$(echo "$1"| cut -d '.' -f 1 )
ext=$( echo "$1"| tr '.' '\n' | tac | head -n 1 ) 
mv "$1" "./$body renamed.$ext"
