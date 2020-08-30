#!/bin/bash
echo "Running program"
./test3 &
pid1=$!
sleep 2s
echo "Sending signals to "$pid1
#echo "Test1: Expected output => Error"
#kill -SIGUSR1 $pid1
#kill -SIGUSR2 $pid1
#kill -SIGALRM $pid1
#echo "Test2: Expected output => Success"
#kill -SIGALRM $pid1
#kill -SIGUSR1 $pid1
#kill -SIGUSR1 $pid1
#sleep 6s
kill -SIGALRM $pid1
echo "Test3: Expected output => Termination"
#kill -SIGALRM $pid1
kill -SIGUSR2 $pid1
kill -SIGUSR2 $pid1
kill -SIGUSR2 $pid1
kill -SIGUSR2 $pid1
sleep 1s
kill -SIGUSR2 $pid1
echo "Waiting program to end"
wait $pid1
echo "Testing Done"


exit 0
