#!/bin/bash
echo "Sorted by Product to file: products"
sort -r $1 > products
exit 0
