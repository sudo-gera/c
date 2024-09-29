# 6
# from fractions import Fraction
# print(
# (
# 2 * (33**132 - 5) + 3 * (33**66 + 3)**2 - (33**66 + 9)**2
# )*Fraction(1)/(
# (33**66 - 4) * ((33**66 - 1) ** 2 - (33**66 + 1) * (33**66 - 2) - 7)
# )
# )

# 7
# for q in range(0, 999):
#     for w in range(0, 999):
#         if q * w == 252:
#             if q * (w - 6) == 168:
#                 print( (q - 5) * (w - 6) )

# 8
# for q in range(10**3, 10**4):
#     if q % 9 == 0:
#         for w in range(10**3, 10**4):
#             if q * 3 - 2658 == w:
#                 if str(w)[:-1] in str(q):
#                     print(q, w)

#         # for w in range(10):
#         #     e = int(str(q)[1:] + str(w))
#         #     if q * 3 - 2658 == w:
#         #         if q % 9 == 0:
#         #             print(q)

# 4
print(
sum([
q * 12 + 6
for q in range(6)
])
)
