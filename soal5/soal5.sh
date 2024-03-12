#!/bin/bash

total=0

while true; do
	read -p "Masukkan angka : " angka
	
	if [ $angka -lt 0 ]; then
		break
	fi

	total=$((total+angka))
done

echo "Total : $total"
