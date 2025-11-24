# LBYARCH S18 A
DELA CRUZ, ETHAN IAGO DOROPAN
DUMARAN, MARC IAN ALVAR
# Video Link: 
# How to Run
1. Make sure nasm and gcc commands are installed.
2. `nasm -f elf64 acceleration.asm -o acceleration.o`
3. `gcc main.c acceleration.o -o acceleration_test -Wall -O3 -lm -lrt -no-pie`
4. `./acceleration_test`

# LBYARCH-MP2
A car's peformance is usually measured using an acceleration test with a 1KM distance. Some cars are measured from a cold start (they start at 0KM/H), some are tested from a hot start (the car is running at a stable speed and then accelerates).

Factors that are needed to compute acceleration (m/s2):

1. Initial Velocity (Vi) - starting speed.

2. Final Velocity (Vf) - final speed at the target distance (1KM).

3. Time (T) - the total time consumed to reach 1KM.

The formula for acceleration is:

Acceleration = (Vf - Vi)/T

Sample Computation:

Vi =62.5 KM/H

Vf = 0.0 KM/H

T = 10.1 s

Acceleration  = (62.5KM/H - 0.0KM/H) / 10.1s

                       = (62.5KM/H) / 10.1s

                       = Convert KM/H to m/s

                       = ([62.5KM/H * 1000M/H] * 1m/3600s )/ 10.1s

                       = (17.36M/s) / 10.1s

                       = 1.7188 m/s2

                               = convert to int (1.7188 m/s2) = 2 m/s2

 

Task

Implement a program that computes for the acceleration of multiple cars stored in a Y by 3 matrix. Where Y is the number of cars. All inputs are in single floating point.

The output acceleration for each will be converted into Integers.

Each row will indicate Initial Velocity (in KM/H), Final Velocity (in KM/H), and Time (in Seconds).

Sample Matrix:

0.0, 62.5, 10.1

60.0, 122.3, 5.5

30.0, 160.7, 7.8

*Required to use functional scalar SIMD registers

*Required to use functional scalar SIMD floating-point instructions

Input: Matrix Rows, single float matrix values

Example.

3

0.0, 62.5, 10.1

60.0, 122.3, 5.5

30.0, 160.7, 7.8
