#!/bin/bash
echo "Opening file: $1"
 max=0
 cur=0
lines=0
while read line; do
	cur=$(echo $line | wc -c)
	let lines=lines+1
	if [ $max -lt $cur ] ; then
	 	let max=cur
	fi
done < $1
#lines=$(wc -l $1)
let lines=lines+1
echo "Max line: $max"
echo "Line count: $lines"
echo "Finished"
exit 0
