#!/bin/bash

echo $PWD
scp -r $PWD/src/cat/s21_cat andrey1@192.168.100.11:/usr/local/bin
scp -r $PWD/src/grep/s21_grep andrey1@192.168.100.11:/usr/local/bin
