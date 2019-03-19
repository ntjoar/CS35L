#!/bin/bash

n=24
total=$((2**24*4))

od -An -t fF -N $total < /dev/urandom | 
tr -s [:blank:] '\n' | 
sed '/^$/d' > random.txt
