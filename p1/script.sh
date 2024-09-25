#!/bin/bash


for (( ; ; )) do 
    clear; 
    pstree -cp | grep $1;
    sleep 0.5;
done
