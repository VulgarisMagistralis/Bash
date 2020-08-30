#!/bin/bash

file1="tmp1"
file2="tmp2"
rm -rf $file1 $file2

while : ; do
  echo -n "String ("end" to terminate) "
  read var

  if [ $var = "end" ]; then
    break
  fi

  case $var in
    [aeiou]*) echo OK1; echo $var >> $file1;;
    [0-9]*) echo OK2; echo $var >> $file2;;
    *) echo String ignored;;
  esac

done

echo "Vowels"
cat $file1
echo "Digits"
cat $file2

