from h import *
# def if_first_wins(state):
#     return not if_second_wins(state)

# def if_second_wins(state: set[int]):
#     for q in state:
#         [if_first_wins(state|{q+w})
#             for w in state-{q}
#                 if w+q not in state]



def make_inf_rec(f):
    async def r(q, *a,**s):
        q.put_nowait(await f(*a, **s))
    @wraps(f)
    async def t(*a, **s):
        try:
            return await f(*a, **s)
        except RecursionError:
            pass
        q = asyncio.Queue()
        asyncio.create_task(r(q, *a, **s))
        return await q.get()
    return t

d={}
@make_inf_rec
async def if_first_wins(state_: int, end):
    res = d.get((state_, end), None)
    if res is not None:
        return res
    try:
        for q in range(end):
            if state_ & 2**q:
                for w in range(end):
                    if state_ & 2**w and not 2**(q+w)&state_ and q+w<end and q!=w:
                        if not (await if_first_wins(state_|2**(q+w), end)):
                            d[state_, end]=True
                            return true
        d[state_, end]=False
        return false
    except RecursionError:
        state = {a for a in range(end) if state_ & (1<<a)}
        print(len(state))
        raise KeyboardInterrupt

async def main():
    for q in range(10**3):
        print(q, await if_first_wins(2**3+2**5, q))


asyncio.run(main())


# def would_A_win(state: set[int], current_turn_is_As: bool):
#     if current_turn_is_As:
#         a=[
#             would_A_win(state|{q+w}, False)
#             for q in state
#                 for w in state-{q}
#                     if q+w not in state
#         ]
#         return any(a)
#     else:
#         a=[
#             would_A_win(state|{q+w}, True)
#             for q in state
#                 for w in state-{q}
#                     if q+w not in state
#         ]
#         return not all(a)


        
