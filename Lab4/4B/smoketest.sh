#!/bin/bash

declare -r pass="t"
mkdir smoketest_dir
cp lab4b.c smoketest_dir
cd smoketest_dir
gcc -g -o lab4b lab4b.c -lmraa -lm

./lab4b --BOGUS <<-EOF
EOF
if [[ $?  -ne 1 ]]; then
echo "test 1 didn't detect bad arg"
exit 1
fi

./lab4b <<-EOF
STOP
SCALE=F
LOG TESTING
OFF

if [[ $? -ne 0 ]]; then
echo "test 2 didn't exit successfully"
exit 1
fi
grep -rnw . -e "LOG TESTING"
if [[ $? -ne 0 ]]; then
echo "test 2 couldn't detect LOG TESTING"
exit 1
fi
grep -rnw . -e "STOP"
if [[ $?  -ne 0 ]]; then
echo "test 2 couldn't detect STOP"
exit 1
fi
grep -rnw . -e "SCALE"
if [[ $?  -ne 0 ]]; then
echo "test 2 couldn't detect SCALE"
exit 1
fi

echo "finished test two"

./lab4b --log=TESTLOGFILE.TXT<<-EOF
START
SCALE=C
EOF
if [[ $? -ne 0 ]]; then
echo "test 3 didn't exit successfully"
exit 1
fi
grep -rnw . -e "START"
if [[ $?  -ne 0 ]]; then
echo "test 3 couldn't detect START"
exit 1
fi
grep -rnw . -e "SCALE=C"
if [[ $?  -ne 0 ]]; then
echo "test 3 couldn't detect STOP"
exit 1
fi

cd ..
echo "All tests passed, cleaning up"
rm -r smoketest_dir
exit 0



