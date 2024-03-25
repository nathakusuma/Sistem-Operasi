#!/bin/bash

read -p "Banyaknya angka random : " n
read -p "Batas bawah : " l
read -p "Batas atas : " h

for ((i=0; i<n; i++)) do
	echo $(((RANDOM % h)+l))
done

echo -1
