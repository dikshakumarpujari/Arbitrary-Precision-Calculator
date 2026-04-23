# Arbitrary Precision Calculator

An arbitrary precision calculator developed in C that performs arithmetic operations on very large numbers beyond the limits of standard data types. The project uses custom data structures to achieve high-precision computations.

## Features
- Perform addition of large numbers
- Perform subtraction of large numbers
- Perform multiplication of large numbers
- Perform division of large numbers
- Handles numbers beyond built-in data type limits
- Accurate high-precision calculations

## Technologies Used
- C Programming
- Data Structures (Linked Lists)
- Pointers
- Functions
- Dynamic Memory Allocation

## How It Works
The project performs arithmetic operations on numbers of arbitrary size by representing them as sequences of digits.

- Large numbers are stored using linked lists
- Each digit is processed individually
- Operations are performed similar to manual calculations

Addition:
- Digits are added one by one from right to left
- Carry is handled for each step

Subtraction:
- Digits are subtracted with borrow handling

Multiplication:
- Uses repeated digit multiplication and accumulation

Division:
- Follows long division approach to compute quotient and remainder

## How to Run
1. Compile the code:
   gcc *.c -o apc
3. Run the program:
   ./apc <num1> operator <num2>
