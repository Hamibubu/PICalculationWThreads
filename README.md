# Pi Calculation Project

Author: **Abraham de León Gutiérrez**

## Description

This project contains two programs that calculate the value of Pi using the numerical integration method with rectangles:

- **`piserial.c`**: Calculates Pi sequentially without using threads.
- **`pithreads.c`**: Calculates Pi using multiple threads (`pthread`) to improve performance.

## Usage

### Compilation

To compile the program type the following command

```
make
```

Clean generated files:

```
make clean
```

### Execution


To run the sequential program:

```
./piserial <number of subintervals>
```

To run the threaded program:

```
./pithreads <number of subintervals>
```

## Requirements

- gcc compiler with pthread support.
- math.h and pthread.h libraries.
