#!/bin/bash

# Number of logins(s) of a specific user

echo -n "User name: "
read user

times=$(who | grep $user | wc -l)

echo "User $user has $times login(s)"

exit 0
