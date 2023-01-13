#!/bin/bash
echo -n "Enter 1 for sequential binary search, 2 for parallel binary search: "
read var

if [ $var -eq 1 ]
then
cd Final/Sequential
g++ -o output main.cpp
time ./output


elif [ $var -eq 2 ]
then 
cd Final/Parallel
echo -n "Enter number of processors: "
read noP
mpicxx -o main main.cpp
time mpirun -np $noP ./main

fi
