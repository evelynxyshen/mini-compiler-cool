#!/bin/bash

echo "" > ref_result
echo "" > opt_result
echo "" > unopt_result

file=( book_list cells complex cool lam list new_complex primes)
test_dir=tests/examples
for i in ${file[@]:0} ; do
  coolc $i.cl
  spim $i.s > a.out
  cd ../..
  ./mycoolc -O $test_dir/$i.cl
  spim $test_dir/$i.s > $test_dir/b.out
  ./mycoolc  $test_dir/$i.cl
  spim $test_dir/$i.s > $test_dir/c.out
  cd $test_dir
  echo **********DIFF WITH OPTIMIZED*****
  diff a.out b.out
  echo **********DIFF WITH UNOPT*********
  diff a.out c.out
  rm a.out b.out c.out
done


