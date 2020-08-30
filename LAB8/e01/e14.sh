#!/bin/bash

# reads from terminal
read output_filename

# read is redirected to the first argument of the command line
n=1
while read row
do
  echo "Row=$n $row"
  let n=n+1
done < $1 > $output_filename

exit 0
