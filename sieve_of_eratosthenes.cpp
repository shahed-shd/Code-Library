// Algorithm        : Sieve of Eratosthenes
// Time complexity  : O(n log log n)
// Language         : C++11

#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;


vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);

    isPrime[0] = isPrime[1] = false;

    for (int i = 4; i <= n; i += 2) {
        isPrime[i] = false;
    }
    
    int rt = sqrt(n);

    for (int i = 3; i <= rt; i += 2) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += (i << 1)) {
                isPrime[j] = false;
            }
        }
    }

    return isPrime;
}


vector<int> getPrimes(const vector<bool>& isPrime) {
    vector<int> primes;
    primes.push_back(2);

    int sz = isPrime.size();

    for (int i = 3; i < sz; i += 2) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}


int main()
{
    int n = 100;
    vector<bool> isPrime = sieve(n);
    vector<int> primes = getPrimes(isPrime);

    printf("Total primes upto %d: %lu\n", n, primes.size());

    for(const int& x : primes) {
        printf("%d ", x);
    }

    return 0;
}
