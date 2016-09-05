// Segmented Sieve

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void sieve(int upto, vector<int> &primes)
{
    vector<bool> status(upto+3, true);
    int rt = sqrt(upto);

    for(int i = 3; i <= rt; i += 2)
        if(status[i])
            for(int j = i*i; j <= upto; j += i<<1)
                status[j] = false;

    //primes.push_back(2);
    for(int i = 3; i <= upto; i+=2)
        if(status[i])
            primes.push_back(i);
}

void segmentedSieve(int n)
{
    int segmentSize = sqrt(n);      // To divide the range [0..n] in segments,
                                    // chosen segment size is sqrt(n).
    vector<int> primes;
    sieve(segmentSize, primes);     // Get all primes upto sqrt(n).

    cout << 2;
    for(auto &p : primes)           // Prints the primes upto sqrt(n).
        cout << ' ' << p;

    int low = segmentSize+1, high = 2*segmentSize;

    while(low < n) {
        vector<bool> status(segmentSize+3, true);

        for(auto &p : primes) {         // Use found primes by sieve() to find primes in current range.
            int s = ceil(1.0 * low / p) * p;        // Find minimum multiple of p in range [low..high].
            if(!(s & 1)) s += p;                    // If s is even, take the next odd multiple of p.

            for(int i = s; i <= high; i += p<<1)    // Mark odd multiples of p.
                status[i-low] = false;
        }

        for(int i = low + !(low&1); i <= high; i+=2)// Check only the odd numbers in range [low..high].
            if(status[i-low])
                cout << ' ' << i;

        low = low + segmentSize;                    // Update low and high for next segment.
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
