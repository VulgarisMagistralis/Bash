#!/bin/bash

# This script:
#   clears terminal
#   displays greetings
#   lists the currently logged users
#   sets and displays two shell local variables

clear

echo "Hello, $USER!"
echo

echo "List logged users"
who

echo "Set two shell local variables"
COLOR="black"
VALUE="9"

echo "String: $COLOR"
echo "Number: $VALUE"
echo

echo "Completed"
echo