#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"-n int ../s21_grep.c"
"-i char ../s21_grep.h"
"-l grep_ ../s21_grep.h"
"-c return ../s21_grep.c"
"-h ';$' ../s21_grep.c"
"-n -e i ../Makefile"
"-i -e char -evoid -e the ../s21_grep.h t1.txt"
"-l -f pat3.txt t4.txt"
"-c -ewhen -ewh -ethe -eth -o t4.txt ../s21_grep.c"
"-h '^O' ../s21_grep.c"
"-n include ../s21_grep.c nofile.txt"
"-n include ../s21_grep.c nofile.txt -s"
"-i -eint -e void ../s21_grep.c -e char ../s21_grep.h ../Makefile -e pat"
"-vin ../s21_grep.c empty.txt ../s21_grep.h ../Makefile"
"-v -h -c -l include ../s21_grep.c ../s21_grep.h ../Makefile"
"-f pat1.txt -e'^size' -e';' -e check -e gcc ../s21_grep.c ../s21_grep.h -ni ../Makefile"
"-f pat1.txt -e'^size' -e';' -e check -e gcc ../s21_grep.c ../s21_grep.h -ni ../Makefile nofile.txt -s"
"-o ../s21_grep.c -f pat3.txt -fpat2.txt ../s21_grep.h ../Makefile"
"-hov ../s21_grep.c -eread -e clean -f pat1.txt -fpat2.txt ../s21_grep.h ../Makefile"
"-i inc ../s21_grep.c ../s21_grep.h ../Makefile -e"
"-i inc ../s21_grep.c ../s21_grep.h ../Makefile -f"
"-i inc ../s21_grep.c -fnopat ../s21_grep.h ../Makefile -evoid"
"-i inc ../s21_grep.c -f empty_pat.txt ../s21_grep.h ../Makefile -evoid"
"-ofpat1.txt -eestr -e- ../s21_grep.c ../s21_grep.h  -n ../Makefile -fpat3.txt"
"-ofpat1.txt -eestr -e- ../s21_grep.c ../s21_grep.h  -nis nofile.txt ../Makefile -fpat3.txt"
"-v int -i -h ../s21_grep.c ../s21_grep.h ../Makefile"
"-v int -i -lc ../s21_grep.c ../s21_grep.h ../Makefile"
"-ofpat1.txt -eestr -e- ../s21_grep.c ../s21_grep.h  -nis nofile.txt ../Makefile -fpat3.txt -c"
"-i -eint -e void ../s21_grep.c -e char ../s21_grep.h ../Makefile -e pat -l"
"-i -eint -e ind -e void ../s21_grep.c -e char ../s21_grep.h ../Makefile -e pat -lc"
"../s21_grep.c -e"
"../s21_grep.c ../s21_grep.h ../Makefile"
"../s21_grep.c ../Makefile -erebuild -e gcc -vo -f pat2.txt -fempty.txt"
"../s21_grep.c ../Makefile -erebuild -e gcc -vo -f pat2.txt -fempty.txt -h"
"../s21_grep.c ../Makefile -erebuild -e gcc -vo -f pat2.txt -fempty.txt -in"
"-nivh = t1.txt t2.txt"
"-ie INT ../s21_grep.c"
"-echar -e main -i -eINCLUDE t2.txt ../s21_grep.c ../s21_grep.h -n"
"-ne = -e out t4.txt"
"-iv int t4.txt"
"-in int t4.txt"
"-c -l aboba t1.txt t4.txt"
"-v t1.txt -e ank"
"-noe ) t4.txt"
"-l for t1.txt t2.txt"
"-o -e int t4.txt"
"-e = -e out t4.txt"
"-noe ing -e as -e the -e not -e is test_6_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-c -e . t1.txt -e '.'"
"-l for no_file.txt t2.txt"
"-f test_3_grep.txt t4.txt"
"-l ../s21_grep.c -f ../s21_grep.c ../s21_grep.h"
"-i -v -e INCLUDE -einclude -e int ../s21_grep.c ../s21_grep.h -n"
"-f ../s21_grep.c -l ../s21_grep.c ../s21_grep.h"
"-e inclu.e ../s21_grep.c -f pat1.txt -fpat2.txt ../s21_grep.c"
"-v -c inClu.e ../s21_grep.c"
"-i -vhc -e INCLUDE -einclude -e int ../s21_grep.c ../s21_grep.h -n"
"the t1.txt -n"
"-e'r.' -n -i ../s21_grep.c t1.txt t2.txt t4.txt -fpat1.txt"
"-e'[a-c]' -ni ../s21_grep.c t1.txt t2.txt t4.txt -fpat2.txt -o"
"-e'.$' -n -i ../s21_grep.c t1.txt t2.txt t4.txt -fpat1.txt"
"-e'g.' -novh ../s21_grep.c  t2.txt t4.txt -fpat2.txt ../Makefile"
"-e'.$' -ni ../s21_grep.c t1.txt t2.txt -f pat3.txt t4.txt -fpat1.txt"
"int nof -f"
"-fpat4.txt pat4.txt -fpat3.txt -efor -e while -i -e Ch.r ../Makefile -e'[a-c]'"
"-fpat2.txt pat1.txt -fpat3.txt -efor -e while -i -e Ch.r t1.txt t3.txt -novh -e'[a-c]'"
"-hnilvo -e The -e people t1.txt -e peo t2.txt -k -fpat1.txt t4.txt -fpat2.txt"
"-vohni -e The -e people t1.txt -e peo t2.txt -fpat1.txt t4.txt -fpat2.txt"
"-vohnicl -e The -e people t1.txt -e peo t2.txt -fpat1.txt t4.txt -fpat2.txt"
"-hnilvo -e The -e people t1.txt -e peo t2.txt -fpat1.txt t4.txt -fpat2.txt"
"-hnilvo -e The -e people t1.txt -e peo t2.txt -fpat1.txt t4.txt -fpat2.txt"
"-hnilvko -e The -e people t1.txt -e peo t2.txt -fpat1.txt t4.txt -fpat2.txt"
"-e inclu.e ../s21_grep.c -f pat1.txt -fpat2.txt ../s21_grep.c"
)

testing()
{
    t=$(echo $@)
    .././s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo  "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo  "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32mfail\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for i in "${tests[@]}"
do
    var="-"
    testing $i
done


echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
