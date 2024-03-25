#!/bin/bash

n=1
for dat in $(ls); do
	echo "File ke $n adalah $dat"
	echo "Tipenya adalah $(file -b $dat)"
	n=$((n+1))
done
