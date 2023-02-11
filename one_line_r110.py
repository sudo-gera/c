[[[print(bin(a[-1])[2:].zfill(40)[:40],end='\r'),a.append(a[-1]&~(a[-1]>>1)|a[-1]^(a[-1]<<1))] for w in a] for a in [[1]]]

