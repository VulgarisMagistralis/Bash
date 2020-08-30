#!/bin/bash
echo "List of Products"
tot=0
flag=0
sort -u $1 > list2
while read pro quant ; do
        if [ $flag -ne 1 ] ; then
                let tot=tot+quant
        else
                flag=1
        fi
done < list2
echo "Total quantity: $tot"
exit 0




