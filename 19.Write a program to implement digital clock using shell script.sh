#!/bin/bash
while true 
do
   date +'%a %b %e %Y%n%I:%M%p'
done |awk '!seen[$0]++'
