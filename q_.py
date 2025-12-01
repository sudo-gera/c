from h import *
for x in range(81):
    if x in range(50, 81):
        for n in range(x**2, x**3)[::-1]:
            a=to_radix_list(n**2, x)
            s=to_radix_list(n, x)
            if a[len(a)-len(s):]==s:
                break
    else:
        x = 0
        n = 0
    print(n, ',')
