#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace NTL;

const long N = 1000000;  // Upper limit for the sieve

vector<long> sieve(long n) {
  vector<bool> prime(n + 1, true);
  vector<long> primes;
  prime[0] = prime[1] = false;
  for (long p = 3; p * p <= n; p += 2) {
    if (prime[p]) {
      // We don't care to rule out numbers which aren't 1 mod 6
      for (long i = p * p; i <= n; i += 6 * p) {
        prime[i] = false;
      }
    }
  }
  // The first element of the loop must be 1 mod 6
  // This ensures p = 1 mod 3 and p = 1 mod 2
  // Change the line below if you want to start in a bigger prime
  for (long p = 7; p <= n; p += 6) {
    if (prime[p]) {
      primes.push_back(p);
    }
  }
  return primes;
}

ZZ temp;  // Preallocate temporary object for intermediate

bool checkCondition(const ZZ& a, const ZZ& b, const ZZ& p) {
  ZZ p6 = power(p, 6);
  ZZ value(0);  // Initialize value to 0 to avoid garbage accumulation
                // calculations

  // Reuse temp for all intermediate steps
  sqr(temp, a);  // a^2
  add(value, value, temp);
  mul(temp, a, b);  // a*b
  add(value, value, temp);
  sqr(temp, b);  // b^2
  add(value, value, temp);
  value %= p6;

  return IsZero(value);
}

void findRootsAndCheck(ZZ p) {
  ZZ_p::init(p);  // Set modulus for ZZ_p operations

  for (ZZ a = ZZ(1); a < p; a++) {
    // Optimizing arithmetic operations to use temporary objects
    // efficiently
    ZZ rhs = MulMod(-3, SqrMod(a, p), p);  // RHS = -3*a^2 mod p

    ZZ b_squared;
    SqrRootMod(b_squared, rhs, p);
    // Directly check conditions without additional temporary
    // variables
    if (checkCondition(a, b_squared, p)) {
      cout << "a: " << a << ", b: " << b_squared << ", p: " << p
           << "\n";
      exit(0);
    }
    ZZ b2 = p - b_squared;
    if (b_squared != b2 && checkCondition(a, b2, p)) {
      cout << "a: " << a << ", b: " << b2 << ", p: " << p << "\n";
      exit(0);
    }
  }
}

int main() {
  auto primes = sieve(N);

  #pragma omp parallel for
  for (auto it = primes.begin(); it != primes.end(); it++) {
    findRootsAndCheck(to_ZZ(*it));
    // Print the prime
    // cout << *it << "\n";
    // If you want that the primes are printed right away, uncomment the
    // line below instead. Note that it would slow down the program though
    // cout << *it << endl;
  }

  return 0;
}
