#!/bin/bash
function clean {
	rm log.txt
	touch log.txt
}

clean
./prog1.out &
PID=$!
sleep 30
kill -2 $PID
sleep 1
cp log.txt ./single/log1.txt

clean
./prog2.out &
PID=$!
sleep 30
kill -2 $PID
sleep 1
cp log.txt ./single/log2.txt

clean
./prog3.out &
PID=$!
sleep 30
kill -2 $PID
sleep 1
cp log.txt ./single/log3.txt

clean
./prog4.out &
PID=$!
sleep 30
kill -2 $PID
sleep 1
cp log.txt ./single/log4.txt

