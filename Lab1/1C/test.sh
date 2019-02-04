#!/bin/bash

declare -r pass="t"
mkdir smoketest_dir
cp Makefile smoketest_dir
cp lab1b.c smoketest_dir
cd smoketest_dir
gcc -o simpsh lab1b.c

./simpsh --rdonly Makefile > output1.txt
echo $? > rdonly.txt
echo "0" > rdonly-og.txt
diff rdonly.txt rdonly-og.txt
if [[ $?  -ne 0 ]]; then
echo "rdonly test failed"
exit 1
fi

./simpsh --wronly Makefile
echo $? > wronly.txt
echo "0" > wronly-og.txt
diff wronly.txt wronly-og.txt
if [[ $?  -ne 0 ]]; then
echo "wronly test failed"
exit 1
fi

./simpsh --creat --rdwr test6.txt
if [[ ! -e test6.txt ]]; then
echo "--creat test failed"
exit 1
fi

./simpsh --verbose --rdonly Makefile > output2.txt
grep -rnw . -e "--rdonly Makefile"
if [[ $?  -ne 0 ]]; then
echo "verbose test failed"
exit 1
fi

touch test4.txt
./simpsh --creat --excl --rdwr test4.txt
if [[ $?  -ne 1 ]]; then
echo "--creat --excl test failed"
exit 1
fi

./simpsh --abort
if [[ $?  -ne 139 ]]; then
echo "--abort test failed"
exit 1
fi

./simpsh --profile --rdwr Makefile --creat --trunc --rdwr test1out.txt --creat --trunc --rdwr test1err.txt --pipe --command 0 4 2 wc -c --wait --command 3 1 2 wc -l --close 0 --close 1 --close 2 --close 4 --close 3 --wait
if [[ $?  -ne 0 ]]; then
echo "--test 1 with --profile test failed"
exit 1
fi

./simpsh --profile --rdwr Makefile --creat --trunc --rdwr test1out.txt --creat --trunc --rdwr test1err.txt --pipe --command 0 4 2 wc -w --wait --command 3 1 2 wc -c --close 0 --close 1 --close 2 --close 4 --close 3 --wait
if [[ $?  -ne 0 ]]; then
echo "--test 1 with --profile test failed"
exit 1
fi

./simpsh --profile --rdwr Makefile --creat --trunc --rdwr test1out.txt --creat --trunc --rdwr test1err.txt --pipe --command 0 4 2 sort --command 3 1 2 cat --close 0 --close 1 --close 2 --close 4 --close 3 --wait
if [[ $?  -ne 0 ]]; then
echo "--test 1 with --profile test failed"
exit 1
fi

cd ..
echo "All tests passed, cleaning up"
rm -r smoketest_dir
exit 0
