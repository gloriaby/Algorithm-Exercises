#!/bin/bash

START=1
END=500
N=200
min=$((N*(N-1)/2))

for (( i=$START; i<=$END; i++ ))
do
	OUTPUT="$(./a.out)"
#	echo "${OUTPUT}"
	if [ $OUTPUT -lt $min ]
	then
		min=$OUTPUT
		echo "${min}"
	fi
	sleep 1
done
echo "finished. Mincut is"
echo "${min}"
