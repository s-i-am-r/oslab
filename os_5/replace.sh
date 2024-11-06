#!/bin/bash

file=$1

rep1=$2
rep2=$3

sed  "s/$rep1/$rep2/g" $file > $file
