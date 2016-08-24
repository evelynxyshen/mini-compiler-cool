#!/bin/bash

source=./PA4

dest=../../localProj

echo "************ SOURCE DIRECTORY: ${source} ****************"
for i in `ls -a ${source}/*.*`
do
echo "************ DIFF FILE: $i ****************"
diff $i ${dest}/$i
cp -r $i ${dest}/$i
done

echo "************ DEST DIRECTORY: ${dest} ****************"



