#!/bin/bash 
echo "enter numbers"
read n;
declare -a a;
for((i=0;i<n;i++))
 do
   read a[$i];
 done
for((i=0;i<n;i++))
do
 for((j=i+1;j<n;j++))
  do
     {
        if((a[i]>a[j]))
        then
        temp=${a[i]};
         a[$i]=${a[j]};
         a[$j]=$temp;
        fi
     }
done
done
for((i=0;i<n;i++))
do
echo ${a[i]}
done
