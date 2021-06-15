// Segmented Sieve

#include <iostream>
#include <vector>
#include <cmath>
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


void segmentedSieve(int n)
{
    int segmentSize = sqrt(n);      // To divide the range [0..n] in segments, chosen segment size is sqrt(n).

    vector<bool> isPrime = sieve(segmentSize);
    vector<int> primes = getPrimes(isPrime);    // Get all primes upto sqrt(n).

    for(const auto& p : primes)                 // Prints the primes upto sqrt(n).
        cout << ' ' << p;

    int low = segmentSize + 1, high = 2 * segmentSize;

    while(low <= n) {
        vector<bool> status(segmentSize + 1, true);

        for(const auto& p : primes) {         // Use found primes by sieve() to find primes in current range.
            int s = ceil(1.0 * low / p) * p;            // Find minimum multiple of p in range [low..high].
            while(!(s & 1) && s <= high) s += p;        // If s is even, take the next odd multiple of p in that range.

            for(int i = s; i <= high; i += (p << 1))    // Mark odd multiples of p.
                status[i - low] = false;
        }

        for(int i = low + !(low & 1); i <= high; i += 2)    // Check only the odd numbers in range [low..high].
            if(status[i - low])
                cout << ' ' << i;

        low = low + segmentSize;                        // Update low and high for next segment.
        high = high + segmentSize;
        if(high > n) high = n;
    }
}

int main()
{
    int n = 100;        // Time complexity (or number of operations) by Segmented Sieve
                        // is same as Simple Sieve. It has advantages for large ‘n’
                        // as it has better locality of reference and requires.
    cout << "Primes upto " << n << ":\n";

    segmentedSieve(n);

    return 0;
}

/*
Output:

Primes upto 100:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
*/
