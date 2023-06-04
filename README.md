# Introduction to Software Security Assignment (Laboratory) 5 
### For Computer Science B.S.c Ariel University

**By Roy Simanovich**

## Description
In this short demo program we demonstrate the difference between the rand() function and Intel's RDRAND instruction,
which is a hardware random number generator, that is built into the CPU itself (Intel Ivy Bridge and
above, AMD Zen and above, x86-64 / AMD64 architecture only).

In the case of rand(), the algorithm is a linear congruential generator (LCG), which is a very simple algorithm that
is fast, but has some undesirable properties. The most important of these is that the sequence of numbers it produces
is not very random. In fact, it is very easy to predict the next number in the sequence given the current number.
This is a problem if you are using the numbers for anything that requires a high degree of randomness, such as
cryptography. In the other hand, RDRAND is a hardware random number generator, that is built into the CPU itself,
is a true random number generator, which means that the numbers it produces are truly random. This is a much
better choice for anything that requires a high degree of randomness, such as cryptography. RDRAND is also much
faster than rand(), as it is a hardware instruction, and does not require any function calls or any calculations
to produce a number, and such, can be done in a single CPU cycle.

The program will run a loop 1,000,000 times, and each time it will generate a random number using rand() and RDRAND, and
will print the results, and the time it took to generate the number. The program will also print the average time
it took to generate a number using rand() and RDRAND.

**_NOTE_:** Please note that the RDRAND instruction returns a 64-bit number (long long int), and rand() returns a 32-bit number (int).

## Requirements
* Linux machine
* GNU C Compiler
* Make

## Building
```
# Cloning the repo to local machine.
git clone https://github.com/RoySenpai/soft_secure_5.git

# Building all the necessary files & the main programs.
make all

```

## Running
```
# Run the program
./rand_vs_rdrand
```