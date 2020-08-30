#!/bin/bash
number=0
for x in `cat $1`
do
  number=$[$number+$x]
  echo number
done
