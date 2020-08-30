#!/bin/bash

# count characters

echo -n "String: "
read word

l=$(echo -n $word | wc -c)

echo "Word $word is $l character long"

exit 0
