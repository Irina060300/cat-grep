#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""


declare -a tests=(
"-s test_1_cat.txt"
"-b -e -n -s -t -v test_1_cat.txt"
"-t test_3_cat.txt"
"-n test_2_cat.txt"
"no_file.txt"
"-n -b test_1_cat.txt"
"-s -n -e test_4_cat.txt"
"test_1_cat.txt -n"
"-nb test_1_cat.txt"
"-nt test_3_cat.txt test_2_cat.txt"
"-v test_5_cat.txt"
"-s -v -b -n ../s21_cat.c test_1_cat.txt"
"-b -e -n -s -t -v test_1_cat.txt"
"-ten test_3_cat.txt"
"-nst test_2_cat.txt"
"-vst -b -n no_file.txt"
"-s test_1_cat.txt -n"
"-ben -stv test_2_cat.txt ../s21_cat.c ../s21_cat.h"
"-ts test_2_cat.txt test_3_cat.txt"
"-tsvnb test_2_cat.txt test_3_cat.txt"
"-nb test_2_cat.txt"
"no_file.txt"
"-n -b test_1_cat.txt"
"-sne test_4_cat.txt"
"-n test_1_cat.txt"
"-nbs test_1_cat.txt ../s21_cat.h -t test_2_cat.txt"
"-nbs test_1_cat.txt ../s21_cat.h -b test_2_cat.txt"
"-vte test_5_cat.txt test_1_cat.txt"
"-est test_case_cat.txt"
"-kestr test_case_cat.txt"
)

testing()
{
    t=$(echo $@)
    .././s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo  "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $t"
    else
      (( FAIL++ ))
        echo  "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $t"
    fi
    rm test_s21_cat.log test_sys_cat.log
}

# специфические тесты
for i in "${tests[@]}"
do
    var="-"
    testing $i
done


echo  "\033[31mFAIL: $FAIL\033[0m"
echo  "\033[32mSUCCESS: $SUCCESS\033[0m"
echo  "ALL: $COUNTER"
