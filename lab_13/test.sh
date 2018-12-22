#!/bin/bash

make

for i in {1..4}
do
	echo TEST $i
	./app.exe <in_$i.txt >out
	echo "———— DIFF START ————"
	diff out out_$i.txt
	echo "———— DIFF  END  ————"
	echo ""
	rm out
done
