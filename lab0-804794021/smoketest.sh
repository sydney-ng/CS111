#!/bin/bash 

declare -r pass="t" 
mkdir smoketest_dir
cp Makefile smoketest_dir
cp lab0.c smoketest_dir
cd smoketest_dir
gcc -o lab0 lab0.c

echo "here" 
./lab0 --input=Makefile > output1.txt 
echo "finished 1" 
diff output1.txt Makefile > diffMakefile.txt 
echo "finished 2"
stat --printf="%s" diffMakefile.txt
if [[ $? != 0 ]]; then
 echo "input fail"       
exit 1  
fi

echo "here2"
./lab0 --input=Makefile --output=Makefile-output.txt 
diff Makefile-output.txt Makefile > diffMakefile2.txt 
stat --printf="%s" diffMakefile2.txt
if [[ $?  != 0 ]]; then
  echo "output test failed"
  exit 1
fi

echo "here3"

./lab0 --segfault > segfaultoutput.txt  
"Segmentation fault" > segmentation-og.txt
diff segfaultoutput.txt segmentation-og.txt > diffSegFault.txt
stat --printf="%s" diffSegFault.txt
if [[ $?  -ne 0 ]]; then
  echo "segfault test failed"
  exit 1
fi

echo "here4"
cd ..
echo "All tests passed, cleaning up"
rm -r smoketest_dir
exit 0 

