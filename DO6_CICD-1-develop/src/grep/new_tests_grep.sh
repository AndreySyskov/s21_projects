#!/bin/bash

# Массивы для сравнивания оригинальной команды и тестируемой 

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""


my_command=(
    "./s21_grep"
    )
sys_command=(
    "grep"
    )
 txt=(
   "reflag .leg test_files/my_text.txt"
   
 )   
flags=(
    "i"
    "v"
    "c"
    "l"
    "n"
    "h"
    "s"
    "o"
)





SucFail(){
    let "COUNTER++"
    # Если файлы идентичны, увеличиваем счетчик успешных тестов и выводим сообщение об успехе
    if [ "$(diff -s s21_grep.log grep.log)"  == "Files s21_grep.log and grep.log are identical" ]
    then
        let "SUCCESS++"
        echo "SUCCESS"
    # Иначе увеличиваем счетчик неудачных тестов и выводим сообщение об ошибке
    else
        let "FAIL++"
        echo "FAIL"
    fi
}




Autotest(){
    flags_txt=$(echo "$@" | sed "s/reflag/$nflag/")
    "${my_command[@]}" $flags_txt > "${my_command[@]}".log
    "${sys_command[@]}" $flags_txt > "${sys_command[@]}".log
    DIFF="$(diff -s "${my_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    # Если файлы идентичны, увеличиваем счетчик успешных тестов и выводим сообщение об успехе
    if [ "$DIFF" == "Files "${my_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $flags_txt"
    # Иначе увеличиваем счетчик неудачных тестов и выводим сообщение об ошибке
    else
        let "FAIL++"
      echo  "$COUNTER - Fail $flags_txt"
    fi
    rm -f "${my_command[@]}".log "${sys_command[@]}".log
}

echo -e "\n\033[45m=======ТЕСТИРОВАНИЕ УТИЛИТЫ GREP=======\033[0m\n"
echo  "Ручная проверка"
echo  "Флаг e"
"${my_command[@]}" -e ha test_files/my_text.txt test_files/txt.txt > s21_grep.log
"${sys_command[@]}" -e ha test_files/my_text.txt test_files/txt.txt  > grep.log
SucFail
"${my_command[@]}" -e .leg -e ha test_files/my_text.txt > s21_grep.log
"${sys_command[@]}" -e .leg -e ha test_files/my_text.txt  > grep.log
SucFail
"${my_command[@]}" -e .leg -e ha test_files/my_text.txt test_files/txt.txt > s21_grep.log
"${sys_command[@]}" -e .leg -e ha test_files/my_text.txt test_files/txt.txt  > grep.log
SucFail
echo  "Флаг f \n"
"${my_command[@]}" -f test_files/pattern.txt test_files/txt.txt > s21_grep.log
"${sys_command[@]}" -f test_files/pattern.txt test_files/txt.txt  > grep.log
SucFail
"${my_command[@]}" -f test_files/pattern.txt test_files/my_text.txt test_files/txt.txt > s21_grep.log
"${sys_command[@]}" -f test_files/pattern.txt test_files/my_text.txt test_files/txt.txt  > grep.log
SucFail




echo "AUTOTESTS"

   echo  "1 параметр"

for flag in "${flags[@]}"
do
    for txtc in "${txt[@]}"
    do
    nflag="-$flag"
    Autotest "$txtc"
    done 
done

echo  "2 параметра"
for flag in "${flags[@]}"
do
    for flag2 in "${flags[@]}"
    do
        if [ $flag != $flag2 ]
        then
            for txtc in "${txt[@]}"
            do
            nflag="-$flag -$flag2"
            Autotest "$txtc"
            done
        fi    
    done 
done






printf "\n"
echo -e "\033[1;31mFAILED: $FAIL\033[0m"
echo -e "\033[1;32mSUCCESSFUL: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
printf "\n"

FAIL=0
SUCCESS=0
COUNTER=0