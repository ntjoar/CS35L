#!/bin/sh

echo "Running make clean check. Please be patient..."
echo "---"
make clean check
echo "-------------------------------------------------------------------"
echo "Running my personal tester..."
echo "---"

echo "Testing baseline.ppm and 1-test.ppm..."
test=$(diff baseline.ppm 1-test.ppm)
echo "Output: "
diff baseline.ppm 1-test.ppm
if [ "$test" == "" ]
then 
    echo "Baseline and 1-test.ppm are the same! Test 0.1 passed."
else
    echo "Baseline and 1-test.ppm are not the same! Test 0.1 failed."
fi
echo "---"

echo "Testing baseline.ppm and 2-test.ppm..."
test=$(diff baseline.ppm 2-test.ppm)
echo "Output: "
diff baseline.ppm 2-test.ppm
if [ "$test" == "" ]
then
    echo "Baseline and 2-test.ppm are the same! Test 0.2 passed."
else
    echo "Baseline and 2-test.ppm are not the same! Test 0.2 failed."
fi
echo "---"

echo "Testing baseline.ppm and 4-test.ppm..."
test=$(diff baseline.ppm 4-test.ppm)
echo "Output: "
diff baseline.ppm 4-test.ppm
if [ "$test" == "" ]
then
    echo "Baseline and 4-test.ppm are the same! Test 0.4 passed."
else
    echo "Baseline and 4-test.ppm are not the same! Test 0.4 failed."
fi
echo "---"

echo "Testing baseline.ppm and 8-test.ppm..."
test=$(diff baseline.ppm 8-test.ppm)
echo "Output: "
diff baseline.ppm 8-test.ppm
if [ "$test" == "" ]
then
    echo "Baseline and 8-test.ppm are the same! Test 0.8 passed."
else
    echo "Baseline and 8-test.ppm are not the same! Test 0.8 failed."
fi
echo "-------------------------------------------------------------------"

echo "Testing 1-test.ppm and 2-test.ppm..."
test=$(diff 1-test.ppm 2-test.ppm)
echo "Output: "
diff 1-test.ppm 2-test.ppm
if [ "$test" == "" ]
then
    echo "1-test.ppm and 2-test.ppm are the same! Test 1.2 passed."
else
    echo "1-test.ppm and 2-test.ppm are not the same! Test 1.2 failed."
fi
echo "---"

echo "Testing 1-test.ppm and 4-test.ppm..."
test=$(diff 1-test.ppm 4-test.ppm)
echo "Output: "
diff 1-test.ppm 4-test.ppm
if [ "$test" == "" ]
then
    echo "1-test.ppm and 4-test.ppm are the same! Test 1.4 passed."
else
    echo "1-test.ppm and 4-test.ppm are not the same! Test 1.4 failed."
fi
echo "---"

echo "Testing 1-test.ppm and 8-test.ppm..."
test=$(diff 1-test.ppm 8-test.ppm)
echo "Output: "
diff 1-test.ppm 8-test.ppm
if [ "$test" == "" ]
then
    echo "1-test.ppm and 8-test.ppm are the same! Test 1.8 passed."
else
    echo "1-test.ppm and 8-test.ppm are not the same! Test 1.8 failed."
fi
echo "-------------------------------------------------------------------"

echo "Testing 2-test.ppm and 4-test.ppm..."
test=$(diff 2-test.ppm 4-test.ppm)
echo "Output: "
diff 2-test.ppm 4-test.ppm
if [ "$test" == "" ]
then
    echo "2-test.ppm and 4-test.ppm are the same! Test 2.4 passed."
else
    echo "2-test.ppm and 4-test.ppm are not the same! Test 2.4 failed."
fi
echo "---"

echo "Testing 2-test.ppm and 8-test.ppm..."
test=$(diff 2-test.ppm 8-test.ppm)
echo "Output: "
diff 2-test.ppm 8-test.ppm
if [ "$test" == "" ]
then
    echo "2-test.ppm and 8-test.ppm are the same! Test 2.8 passed."
else
    echo "2-test.ppm and 8-test.ppm are not the same! Test 2.8 failed."
fi
echo "-------------------------------------------------------------------"

echo "Testing 4-test.ppm and 8-test.ppm..."
test=$(diff 4-test.ppm 8-test.ppm)
echo "Output: "
diff 4-test.ppm 8-test.ppm
if [ "$test" == "" ]
then
    echo "4-test.ppm and 8-test.ppm are the same! Test 4.8 passed."
else
    echo "4-test.ppm and 8-test.ppm are not the same! Test 4.8 failed."
fi
echo "-------------------------------------------------------------------"

echo "Running given testers for the homework from the professor. 
Be very patient..."
echo "---"
make clean check > make-log.txt
make clean check | diff -u - make-log.txt
echo "If time difference is immense, you have an error."

echo "-------------------------------------------------------------------"
echo "End of tests, please fix main.c for failed tests if any."
echo "-------------------------------------------------------------------"
