#!/bin/bash
echo "Sorted by Product to file: quantity"
sort -k2 -n $1 > quantity
exit 0
