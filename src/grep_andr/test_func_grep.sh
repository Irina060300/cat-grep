#!/bin/bash

# SUCCESS=0
# FAIL=0
# COUNTER=0
# DIFF_RES=""

# declare -a tests=(
# "s test_0_grep.txt VAR"
# "for s21_grep.c s21_grep.h Makefile VAR"
# "for s21_grep.c VAR"
# "-e for -e ^int s21_grep.c s21_grep.h Makefile VAR"
# "-e for -e ^int s21_grep.c VAR"
# "-e regex -e ^print s21_grep.c VAR -f test_ptrn_grep.txt"
# "-e while -e void s21_grep.c Makefile VAR -f test_ptrn_grep.txt"
# )

# declare -a extra=(
# "-n for test_1_grep.txt test_2_grep.txt"
# "-n for test_1_grep.txt"
# "-n -e ^\} test_1_grep.txt"
# "-ce ^int test_1_grep.txt test_2_grep.txt"
# "-e ^int test_1_grep.txt"
# "-nivh = test_1_grep.txt test_2_grep.txt"
# "-e"
# "-ie INT test_5_grep.txt"
# "-echar test_1_grep.txt test_2_grep.txt"
# "-ne = -e out test_5_grep.txt"
# "-iv int test_5_grep.txt"
# "-in int test_5_grep.txt"
# "-c -l aboba test_1_grep.txt test_5_grep.txt"
# "-v test_1_grep.txt -e ank"
# "-noe ) test_5_grep.txt"
# "-l for test_1_grep.txt test_2_grep.txt"
# "-o -e int test_4_grep.txt"
# "-e = -e out test_5_grep.txt"
# "-noe ing -e as -e the -e not -e is test_6_grep.txt"
# "-e ing -e as -e the -e not -e is test_6_grep.txt"
# "-c -e . test_1_grep.txt -e '.'"
# "-l for no_file.txt test_2_grep.txt"
# "-f test_3_grep.txt test_5_grep.txt"
# )

# testing()
# {
#     t=$(echo $@ | sed "s/VAR/$var/")
#     ./s21_grep $t > test_s21_grep.log
#     grep $t > test_sys_grep.log
#     DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
#     (( COUNTER++ ))
#     if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
#     then
#       (( SUCCESS++ ))
#       echo -e "$FAIL $SUCCESS $COUNTER success grep $t"
#     else
#       (( FAIL++ ))
#       echo -e "$FAIL $SUCCESS $COUNTER fail grep $t"
#     fi
#     rm test_s21_grep.log test_sys_grep.log
# }

# # специфические тесты
# for i in "${extra[@]}"
# do
#     var="-"
#     testing $i
# done

# # 1 параметр
# for var1 in v c l n h o
# do
#     for i in "${tests[@]}"
#     do
#         var="-$var1"
#         testing $i
#     done
# done

# # 2 параметра
# for var1 in v c l n h o
# do
#     for var2 in v c l n h o
#     do
#         if [ $var1 != $var2 ]
#         then
#             for i in "${tests[@]}"
#             do
#                 var="-$var1 -$var2"
#                 testing $i
#             done
#         fi
#     done
# done

# # 3 параметра
# for var1 in v c l n h o
# do
#     for var2 in v c l n h o
#     do
#         for var3 in v c l n h o
#         do
#             if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#             then
#                 for i in "${tests[@]}"
#                 do
#                     var="-$var1 -$var2 -$var3"
#                     testing $i
#                 done
#             fi
#         done
#     done
# done

# # 2 сдвоенных параметра
# for var1 in v c l n h o
# do
#     for var2 in v c l n h o
#     do
#         if [ $var1 != $var2 ]
#         then
#             for i in "${tests[@]}"
#             do
#                 var="-$var1$var2"
#                 testing $i
#             done
#         fi
#     done
# done

# # 3 строенных параметра
# for var1 in v c l n h o
# do
#     for var2 in v c l n h o
#     do
#         for var3 in v c l n h o
#         do
#             if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#             then
#                 for i in "${tests[@]}"
#                 do
#                     var="-$var1$var2$var3"
#                     testing $i
#                 done
#             fi
#         done
#     done
# done

# echo -e "FAIL: $FAIL"
# echo -e "SUCCESS: $SUCCESS"
# echo "ALL: $COUNTER"


SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_grep"
    )
sys_command=(
    "./grep"
    )

flags=(
    "v"
    "c"
    "l"
    "n"
    "h"
    "o"
)

tests=(
"s  test_0_grep.txt FLAGS"
"for s21_grep.c s21_grep.h Makefile FLAGS"
"for s21_grep.c FLAGS"
"-e for -e ^int s21_grep.c s21_grep.h Makefile FLAGS"
"-e for -e ^int s21_grep.c FLAGS"
"-e regex -e ^print s21_grep.c FLAGS -f  test_ptrn_grep.txt"
"-e while -e void s21_grep.c Makefile FLAGS -f  test_ptrn_grep.txt"
"-e intel -e int FLAGS  test_7_grep.txt"
"-e int -e intel FLAGS  test_7_grep.txt"
)

manual=(
"-n for  test_1_grep.txt  test_2_grep.txt"
"-n for  test_1_grep.txt"
"-n -e ^\}  test_1_grep.txt"
"-c -e /\  test_1_grep.txt"
"-ce ^int  test_1_grep.txt  test_2_grep.txt"
"-e ^int  test_1_grep.txt"
"-nivh =  test_1_grep.txt  test_2_grep.txt"
"-e"
"-ie INT  test_5_grep.txt"
"-echar  test_1_grep.txt  test_2_grep.txt"
"-ne = -e out  test_5_grep.txt"
"-iv int  test_5_grep.txt"
"-in int  test_5_grep.txt"
"-c -l aboba  test_1_grep.txt  test_5_grep.txt"
"-v  test_1_grep.txt -e ank"
"-noe )  test_5_grep.txt"
"-l for  test_1_grep.txt  test_2_grep.txt"
"-o -e int  test_4_grep.txt"
"-e = -e out  test_5_grep.txt"
"-noe ing -e as -e the -e not -e is  test_6_grep.txt"
"-e ing -e as -e the -e not -e is  test_6_grep.txt"
"-c -e .  test_1_grep.txt -e '.'"
"-l for no_file.txt  test_2_grep.txt"
"-e int -si no_file.txt s21_grep.c no_file2.txt s21_grep.h"
"-si s21_grep.c -f no_pattern.txt"
"-f  test_3_grep.txt  test_5_grep.txt"
)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${s21_command[@]}" $param > "${s21_command[@]}".log
    "${sys_command[@]}" $param > "${sys_command[@]}".log
    DIFF="$(diff -s "${s21_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${s21_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log
}

echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "TESTS WITH NORMAL FLAGS"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
printf "\n"
echo "#######################"
echo "MANUAL TESTS"
echo "#######################"
printf "\n"

for i in "${manual[@]}"
do
    var="-"
    run_test "$i"
done

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test "$i"
    done
done
printf "\n"
echo "======================="
echo "2 PARAMETERS"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                run_test "$i"
            done
        fi
    done
done
printf "\n"
echo "======================="
echo "3 PARAMETERS"
echo "======================="
printf "\n"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    run_test "$i"
                done
            fi
        done
    done
done
printf "\n"
echo "======================="
echo "4 PARAMETERS"
echo "======================="
printf "\n"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            for var4 in "${flags[@]}"
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        run_test "$i"
                    done
                fi
            done
        done
    done
done
printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "DOUBLE PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                run_test "$i"
            done
        fi
    done
done

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "TRIPLE PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    run_test "$i"
                done
            fi
        done
    done
done
printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"