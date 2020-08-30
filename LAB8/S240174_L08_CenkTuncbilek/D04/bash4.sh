#!/bin/bash
if [[ -f $1 ]] ; then
	echo "$1 not a directory, exiting"
	exit 1
fi
for FILE in $(find $1) ; do
	if test -d $FILE ; then
		let c=$(find  $FILE -type d | wc -l);let c=c-1
		full_path=$(readlink -f $FILE)
		echo "$full_path is a subdirectory with subdirectory count: $c"
	fi
	if test -f $FILE ; then
		size=$(find $FILE -printf "%s")
		per=$(find $FILE -printf "%M")
		full_path=$(readlink -f $FILE)
 		echo "Path: $full_path || Size: $size ||  User permissions: $per"
	fi
done > out.txt
sort -o out.txt out.txt
exit 0
