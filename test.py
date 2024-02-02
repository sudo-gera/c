# from h import *
# for q in range(-99,99):
#     for e in range(2,99):
#         assert from_radix_list(to_radix_list(q,e),e) == q

def coords_and_A1(a,s = None):
    '''
        A1 is (0,0)
        A2 is (1,0)
        B1 is (0,1)
        B2 is (1,1)
        works in both directions
    '''

    letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    def get_columns_with_len(l):
        if not l:
            yield ''
            return
        for head in letters:
            for tail in get_columns_with_len(l-1):
                yield head + tail

    import itertools
    import functools
    import re
    import time

    coords_and_A1.num_and_col_dict = getattr(coords_and_A1, 'num_and_col_dict', {})
    coords_and_A1.iter = getattr(coords_and_A1, 'iter', itertools.count(1))
    num_and_col_dict = coords_and_A1.num_and_col_dict
    
    def col_and_num(a):
        while a not in num_and_col_dict:
            fill_columns()
        return num_and_col_dict[a]

    def fill_columns(*a):
        for col in get_columns_with_len(next(coords_and_A1.iter)):
            num = len(num_and_col_dict)//2
            num_and_col_dict[num]=col
            num_and_col_dict[col]=num

    if s is None:
        a,s = re.fullmatch(r'(\D+)(\d+)', a).groups()
        return int(s)-1, col_and_num(a.upper())
    return col_and_num(s)+str(a+1)

