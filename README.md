# Freshman's Nightmare

## Overview

This project is dedicated to exploring a particular number-theoretic conjecture related to prime numbers congruent to 1 modulo 3. It is well known that if $p$ is a prime such that $p \equiv 1 \mod 3$ and $p^k$ divides $a^2 + ab + b^2$, then $p^{2k+1}$ divides $(a+b)^p - a^p - b^p$. However, a conjecture posed by a reader of Kvant magazine suggests that there are no solutions for $k > 2$ ([Kvant, 1984](http://kvant.mccme.ru/1984/08/p34.htm)).

I met this conjecture during an attempt to solve a problem from the ELMO 2009 (P6). It has been discussed in various mathematical forums and communities, including:

- [Art of Problem Solving](https://artofproblemsolving.com/community/c6h514444p2890151)
- [MathOverflow](https://mathoverflow.net/questions/255911/may-p3-divide-abp-ap-bp)
- [Math Stack Exchange](https://math.stackexchange.com/questions/1961526/lemma-on-switching-between-mod-p-and-mod-p2-or-mod-p3)

Hensel's Lemma, which is related to this problem, is detailed further at [ProofWiki](https://proofwiki.org/wiki/Hensel%27s_Lemma).

The code included in this project checks for solutions up to prime numbers up to some `N`, validating the conjecture within this range. Execution with `N` equals one million on an Intel i5-8265U processor took approximately 20 hours. To extend this and cover larger primes, leveraging additional computing power, running it into the GPU, or even adapting the code for supercomputing resources would be advantageous.

## Installation

The implementation utilizes the Number Theory Library (NTL) with support for GMP (the GNU Multiple Precision Arithmetic Library) for efficient mathematical operations.

### Prerequisites

- [NTL](https://libntl.org/doc/tour-unix.html): A library for performing number theory operations.
- [GMP](https://libntl.org/doc/tour-gmp.html): Required for NTL when working with large numbers for increased efficiency.

### Building the Project

The primes are looked up to the constant `N`:
```cpp
const long N = 1000000;  // Upper limit for the sieve
```

To compile the project, ensure that NTL and GMP are correctly installed on your system. Then, you can build the project using the following command:

```sh
g++ -Ofast -o main main.cpp -lntl -lgmp -lm -fopenmp
```

And for running the program:
```sh
./main
```

This will run through all triples $(a, b, p)$ with $p$ prime less than `N`, and $0 < a, b < p$, and only print a triple (and stop) if $p^6$ divides $a^2 + a b + b^2$. If you want it to print every prime, you can change the following:
```cpp
// Print the prime
// cout << *it << "\n";
```
To:
```cpp
// Print the prime
cout << *it << "\n";
```

## Contributing

To contribute to this research or to verify the conjecture over an even larger set of primes, you're encouraged to run the code on systems with more significant computational resources. Any findings, optimizations, or adaptations for different computational environments would be highly appreciated.

Your contributions can help advance our understanding of this conjecture and potentially uncover new mathematical insights.
