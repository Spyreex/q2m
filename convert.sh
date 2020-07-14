#!/bin/bash

gcc *.c -D BUFFER_SIZE=32
cp input/*.qua .
mkdir output
rm output/*
for i in *.qua 
do
	perl -p -e 's/\r//g' $i > $i.new
done
a='ls *.qua.new'
./a.out $a
mv *.osu output/
rm *.qua* ./a.out
cp input/* output/
rm output/*.qua