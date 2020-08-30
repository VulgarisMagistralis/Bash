#!/bin/bash

LIMIT=$#
total_sum=0
# echo -n -> non newline
# Notice (( and LIMIT without $
echo -n "The command line argumets are: "
for ((a=1; a <= LIMIT ; a++)) 
do
   echo -n "${!a} "
   let "total_sum += ${!a}"
done  
echo

echo "The total sum of the numeric values given on the comman line \
is $total_sum."

# other solution
for a in "$@"
do
   echo -n "$a "
done  
echo

# another solution
for a in `echo "$*"`   
# notice the backquotes (return the list of words resulting by the execution of the command)
do
   echo -n "$a "
done  
echo

# another solution
for a in $(echo "$*")   
# notice that $( ) substitutes ` `
do
   echo -n "$a "
done  
echo

# nother solution (with arrays)
# Notice \ before special characters like `
echo -n "the array content is: "
for ((a=1; a <= $# ; a++))
do
   vet[$a]=${!a}
   echo -n "${vet[$a]} "
done
echo
