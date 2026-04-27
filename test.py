from h import *

@cache
def len_squares(n: int) -> int:
    return len({x*x%n for x in range(0, n)})

for pn in range(1, 99):
    n = reduce(mul, primes[1:pn+1])
    print(pn, len_squares(n)/(n+0), (2/3)**pn)

# # step_size = 100800
# step_size = 1000003
# d = 11
# ns_gcd = None
# try:
#     for n in range(0, 9999999, step_size):
#         if len_squares(n) < 0.011 * n:
#             ns_gcd = n if ns_gcd is None else gcd(n, ns_gcd)
#             print(n, n % (step_size*d), ns_gcd // step_size)
# finally:
#     ...

# print(
#     *[
#         f"{round(v/n*100)*'#':100s} {v = :4d} {n = :4d} {v/n = :0.2f} {len(factor(n)) = }"
#         for v,n in [
#             (
#                 len({x*x%n for x in range(0, n)}),
#                 n
#             )
#             for n in range(1,9999)
#         ]
#     ], sep='\n'
# )
