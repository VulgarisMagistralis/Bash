#!/bin/bash

echo -n "V1: "

iter=1

for val in `cat $1`
do
   if [ $iter -eq 1 ]
   then
     let f=3*val*val
   elif [ $iter -eq 2 ]
   then
     let f=f+4*val
   elif [ $iter -eq 3 ]
   then
     let f=f+5*val
     iter=0
     echo -n "$f "
   fi
   let iter=iter+1
done

echo
echo -n "V2: "

while read row
do

   iter=1
   for val in $row
   do

     if [ $iter -eq 1 ]
     then
      let f=3*val*val
     elif [ $iter -eq 2 ]
     then
       let f=f+4*val
     elif [ $iter -eq 3 ]
     then
       let f=f+5*val
     fi

     let iter=iter+1
   done

   echo -n "$f "

done < $1

echo
echo -n "V3: "

while read x y z
do
  let f=3*x*x+4*y+5*z
  echo -n "$f "
done < $1

echo

