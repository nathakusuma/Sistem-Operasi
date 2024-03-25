#!/bin/bash

read -p "Masukkan bilangan pertama : " bil1
read -p "Masukkan tanda operasi : " operasi
read -p "Masukkan bilangan kedua : " bil2

case $operasi in
	t) hasil=$((bil1+bil2));;
	k) hasil=$((bil1-bil2));;
	b) hasil=$((bil1/bil2));;
	x) hasil=$((bil1*bil2));;
	*) echo "Tanda tidak sah" && exit 1;;
esac

echo "Hasilnya adalah $hasil"
