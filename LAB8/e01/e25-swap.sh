#!/bin/bash
# keep only 2 words for every line of a file

var0=tmp

while read var1 var2
do
  echo $var2 $var1;
done <$1 >$var0

mv $var0 $1
