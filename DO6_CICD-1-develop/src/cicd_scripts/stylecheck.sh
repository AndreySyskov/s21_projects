#!/bin/bash

cd ${CI_PROJECT_DIR}/src/cat
make clang > ${CI_PROJECT_DIR}/msg1.log 2>&1
cat ${CI_PROJECT_DIR}/msg1.log
#ls -la
echo "DONE"
countWarnings=`cat ${CI_PROJECT_DIR}/msg1.log | grep "warning: code should be clang-formatted" | wc -l`
if [ $countWarnings -gt 0 ]; then
    exit 1;
fi

cd ${CI_PROJECT_DIR}/src/grep
make clang > ${CI_PROJECT_DIR}/msg2.log 2>&1
cat ${CI_PROJECT_DIR}/msg2.log
echo "DONE"
countWarnings=`cat ${CI_PROJECT_DIR}/msg2.log | grep "warning: code should be clang-formatted" | wc -l`
if [ $countWarnings -gt 0 ]; then
    exit 1;
fi