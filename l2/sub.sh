#!/bin/env bash

str=$1
oldstr=$2
newstr=$3
echo $str | sed "s/$oldstr/$newstr/g"
