import sys
import itertools

def get_primes(n):
    primes = []
    if n <= 0:
        return []
    for q in itertools.count(2):
        for p in primes:
            if q % p == 0:
                break
        else:
            primes.append(q)
        if len(primes) == n:
            break
    return primes

if __name__ == '__main__':
    n = int(sys.argv[1])
    primes = get_primes(n)
    print(*primes)

