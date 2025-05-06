#23020845 Hoàng Nhật Nam


# 1.1 Write shell commands to: 
# Creates a new directory named Exam inside the user's home directory. 
# Moves into the Exam directory. 
# 1.2 Count the total number of files in the user's directory that don't have the .c extension. 
# 1.3 Write a shell script that: 
# Takes an integer N as input from the user. 
# Calculates the product of numbers from 1 to N. 
# Appends the result to a file named Result_ex1.txt.


#!/bin/sh
mkdir -p $HOME/Exam
cd $HOME/Exam

find . -type f ! -name "*.c" | wc -l

read -p "Enter an integer N: " N

product=1
for (( i=1; i<=N; i++ )); do
  product=$(( product * i ))
done

echo "The product of numbers from 1 to $N is: $product" >> Result_ex1.txt