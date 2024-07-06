import mmap
import base64
import random

with (
        open('/Users/gera/random_bytes.txt') as file,
        mmap.mmap(file.fileno(), 0, mmap.MAP_PRIVATE, mmap.PROT_READ) as m
    ):
    # a=0
    # for q in range(10**3):
    #     a = random.randint(0, 17179869184) if not random.randint(0, 0) else random.randint(a-6400, a+6400)%17179869184
    #     s = m[a:a+10**6]
    # for q in range(12):
    #     a = random.randint(0, 17179869184)
    #     for w in range(a, ):
    #         pass
    #         # print(q)
    m[:10**9]


# def inversions(a):
#     ic = 0
#     for q in range(len(a)):
#         for w in range(len(a)):
#             if q < w and a[q] > a[w]:
#                 ic += 1
#     return ic


# def merge_sort(a, s, b, e):
#     # assert a[b:e] == s[b:e]
#     if e - b < 2:
#         return 0
#     c = (b + e) // 2
#     ic = 0
#     ic += merge_sort(s, a, b, c)
#     ic += merge_sort(s, a, c, e)
#     zi = b
#     xi = c
#     ai = b
#     for ai in range(b, e):
#         if xi < e and (zi == c or s[zi] > s[xi]):
#             a[ai] = s[xi]
#             ic += c - zi
#             xi+=1
#         else:
#             a[ai] = s[zi]
#             zi+=1
#     return ic

# def merge_inversions(a):
#     return merge_sort(a[:], a[:], 0, len(a))

# while 1:
    # a = [random.randint(0, 2**64)-1 for q in range(10**3)]
    # s = sorted(a)
    # d = a[:]
    # ic = inversions(a)
    # assert ic == merge_inversions(a)
    # assert ic == merge_sort(a, d, 0, len(a))
    # assert a == s
    # print(random.randint(0, 9), end='\r')

# a = [random.randint(0, 2**64)-1 for q in range(10**3)]
# print(merge_inversions(a))
# for s in range(63, -1, -1):
#     inv1 = merge_inversions(a)
#     for q in range(len(a)):
#         a[q] ^= 2**s
#     inv2 = merge_inversions(a)
#     if inv2 > inv1:
#         for q in range(len(a)):
#             a[q] ^= 2**s
# print(merge_inversions(a))




