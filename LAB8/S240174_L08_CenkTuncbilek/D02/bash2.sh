#!/bin/bash
echo "opening file $1"
while read w1 w2 w3 rest_of_line
	do
	new=$(echo $w3 | tr [:lower:] [:upper:])
        echo "$w1 $w2 $new $rest_of_line"
done < $1 > result
echo "words replaced"
cp result $1
exit 0
