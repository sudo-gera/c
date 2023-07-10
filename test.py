d=[
    None,
    2,2,
    3,3,
    4,4,4,
    5,5,5,
]
for q in range(1,99):
    for w in range(1,99):
        for e in range(-99,99):
            if all([(a*q+e)//w==d[a] for a in range(1,11)]):
                for a in range(1,11):
                    print(a,a*q,a*q+e,(a*q+e)//w,d[a],sep='\t')
                print(q,w,e)
                exit()
