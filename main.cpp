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

bool checkCondition(const ZZ& a, const ZZ& b, const ZZ& p) {
  ZZ temp;  // Preallocate temporary object for intermediate

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

int main() {
  auto primes = sieve(N);

#pragma omp parallel for simd
  for (int i = 0; i < primes.size(); i++) {
    auto p0 = primes[i];
    ZZ p = ZZ(p0);
    ZZ_p::init(p);  // Set modulus for ZZ_p operations

#pragma omp simd
    for (int a0 = 1; a0 < p0; a0++) {
      ZZ a = ZZ(a0);
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

      cout << p0 << "\n";
    }
  }

  return 0;
}
