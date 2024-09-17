#!/bin/bash


for (( ; ; )) do 
    clear; 
    pstree -c | grep $1;
    sleep 0.5;
done
