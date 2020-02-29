/*
 *  problem: https://leetcode-cn.com/problems/count-primes/
 */

//Solution (Sieve of Eratosthenes):
//Time complexity: O(nloglogn)
//Space complexity: O(n)

class Solution {
public:
    bool isPrime(int num) {
        for(int i = 2;i <= sqrt(num);++i) {
            if(num % i == 0)
                return false;
        }
        return true;
    }
    int countPrimes(int n) {
        if(n < 2)
            return 0;
        vector<int> v(n,1);
        for(int i = 2;i < sqrt(n);++i) {
            if(isPrime(i)) {
                for(int j = i * i;j < n;j +=i) {  //If j starts with 2 * i, it will duplicate.
                    v[j] = 0;
                }
            }
        }
        return count(v.begin() + 2,v.end(),1);
    }
};
