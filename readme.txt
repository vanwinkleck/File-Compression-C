This is a project worked on by myself and Mohammad Alabdalla for CSCI-3500: Operating Systems. The Class was taught by Dr. David Ferry, who also provided help to us on this project.

The basic idea was to write a simple run-length-encoding type system for compressing files using the open(), close(), read(), and write() system calls. More detail can be found in "description.txt", where I have included the prompt and questions asked by Dr. Ferry. Our ansewers to the questions asked by Dr. Ferry can be found in "questions.txt".

To run the code, simply compile "rle.c" in the terminal and use one of the test files as the first argument, and output file with a name of your choice as the second argument, the compression length as the third, and the mode as the last. 

These test files are:

test1
test2
test3
1mil_random
1mil_strong_bias
1mil_weak_bias

and an example input would be: rle test1 test1out 1 0.

You may also use our code to compress images, although ours did not work perfectly for this scenario. However, the images "slu_logo.bmp" and "uncompressed.bmp" have been included for this use case. 
