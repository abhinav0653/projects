#!/bin/bash
function clean {
	rm log.txt
	touch log.txt
}

./prog1.out &
PID1=$!
./prog2.out &
PID2=$!
./prog3.out &
PID3=$!
./prog4.out &
PID4=$!
sleep 60


clean
kill -2 $PID1
sleep 1
cp log.txt ./multiple/mlog1.txt


clean
kill -2 $PID2
sleep 1
cp log.txt ./multiple/mlog2.txt

clean
kill -2 $PID3
sleep 1
cp log.txt ./multiple/mlog3.txt

clean
kill -2 $PID4
sleep 1
cp log.txt ./multiple/mlog4.txt

