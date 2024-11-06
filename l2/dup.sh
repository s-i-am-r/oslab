#!/bin/env bash


str=$1
echo $str | fold -w1| sort  |uniq | tr -d '\n'
 
