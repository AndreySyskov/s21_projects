#!/bin/bash

cd ${CI_PROJECT_DIR}/src/cat
cat test_cat_unit.log
counter=`cat test_cat_unit.log | grep "falied " | wc -l`
if [ $counter -gt 0 ]; then
    exit 1;
fi

cd ${CI_PROJECT_DIR}/src/grep
cat test_grep_unit.log
counter_grep=`cat test_grep_unit.log | grep "fail" | wc -l`
if [ $counter_grep -gt 7 ]; then
    echo "Too many FAILED tests!"
    exit 1;
    else
    echo "The number of failed tests is less than 10%, we consider the testing successful!"
fi