#!/bin/bash

file=`ls *.cl`
echo $file
for i in $file ; do
  coolc $i
done

echo "" > ref_result
code=`ls *.s`
for j in $code ; do
  if [[ "$j" != "25_"* ]]; then
    echo $j >> ref_result
    spim $j >> ref_result
    echo -e "\n\n" >> ref_result
  fi
done


file=`ls *.cl`
echo $file
cd ..
for i in $file ; do
  ./mycoolc -O tests/$i
done

cd tests
echo "" > opt_result
code=`ls *.s`
for j in $code ; do
  if [[ "$j" != "25_"* ]]; then 
    echo $j >> opt_result
    spim $j >> opt_result
    echo -e "\n\n" >> opt_result
  fi
done

file=`ls *.cl`
echo $file
cd ..
for i in $file ; do
  ./mycoolc tests/$i
done

cd tests
echo "" > unopt_result
code=`ls *.s`
for j in $code ; do
  if [[ "$j" != "25_"* ]]; then
    echo $j >> unopt_result 
    spim $j >> unopt_result
    echo -e "\n\n" >> unopt_result
  fi
done

cat opt_result | sed "/Stats/d" | sed "/#reads/d" > opt_output
cat unopt_result | sed "/Stats/d" | sed "/#reads/d" > unopt_output
cat ref_result | sed "/Stats/d" | sed "/#reads/d" > ref_output

echo ********DIFF WITH REFERENCE****
diff ref_output opt_output

echo -e "\n"
echo ********DIFF OUTPUT************
diff  opt_output  unopt_output
rm opt_output
rm unopt_output
rm ref_output
