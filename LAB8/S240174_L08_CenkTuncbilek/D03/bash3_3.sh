#!/bin/bash
echo "Counting quantites"
tot=0
flag=0
while read pro quant ; do
	if [ $flag -ne 1 ] ; then
		let tot=tot+quant
	else
		flag=1
	fi
done < $1
echo "Total quantity: $tot"
exit 0





