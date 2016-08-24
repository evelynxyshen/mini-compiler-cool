#!/bin/sh
test_file=5_string_null.cl
echo ""> 5_string_null.cl
echo "class Main inherits IO {" >> $test_file
echo -e "\tmyString : String <- \"Hell\0o World!\\\n;\";" >>$test_file
echo -e "\tmain(): Object {  " >> $test_file
echo -e "\t  out_string(myString) " >> $test_file
echo -e "\t};" >> $test_file
echo  "};" >> $test_file

