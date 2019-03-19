After Action Report
For me, this project made me run into a few difficulties. To start,
I found one of the difficulties in this project to be when I started
implementing with multiple public variables. At first, it confused me,
as I had an error where nothing was written, which I found due to be 
that I did not allocate anything in the arrays in the first place. 
Next, I had the error of compiling, as I had forgotten to implement
-lpthread in the Makefile, leading to receive multiple gcc errors.
Following this was an error that I had an infinite loop due to 
redefining the variable. This gave me an infinite loop and wiped my 
data a lot.
However, timing on my program is as follows:

At 1 core:
time ./srt 1-test.ppm >1-test.ppm.tmp
real 0m47.858s
user 0m47.843s
sys  0m0.004s
---
At 2 cores:
time ./srt 2-test.ppm >2-test.ppm.tmp
real 0m24.374s
user 0m48.210s
sys  0m0.001s
---
At 4 cores:
time ./srt 4-test.ppm >4-test.ppm.tmp
real 0m12.624s
user 0m50.095s
sys  0m0.006s
---
At 8 cores:
time ./srt 8-test.ppm >8-test.ppm.tmp
real 0m7.327s
user 0m54.562s
sys  0m0.005s


For this, we can see tha tmultithreading allows the code to take 
optimal performance on the machine and greatly decrease its time to
run by a factor of two. By multithreading, we take and push the 
procressor(s) to run using all of its cores possible and we can
achieve efficiency through a result of a divide and conquer 
approach to many problems.
