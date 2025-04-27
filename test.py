if 1:
    from h import *
    canvas_size = 256
    canvas = [[[255,255,255] for w in range(canvas_size * 2 + 1)] for q in range(canvas_size * 2 + 1)]

    # def vec_prod(x1,y1,x2,y2):
    #     return x1*y2-x2*y1

    # left_bottom_corner = [0,0]
    # right_bottom_corner = [len(canvas[0])-1,0]
    # top_corner = [(len(canvas[0])-1)//2, round((len(canvas[0])-1)/2*3**0.5)]

    # for q in range(99999):
    #     x = randint(0, len(canvas[0])-1)
    #     y = randint(0, len(canvas)-1)
        
    right_corner = cmath.rect(1, cmath.pi*0)
    upper_left_corner = cmath.rect(1, cmath.pi*2/3)
    lower_left_corner = cmath.rect(1, -cmath.pi*2/3)
    #print(abs(top_corner-bottom_left_corner), abs(bottom_left_corner - bottom_right_corner), abs(bottom_right_corner - top_corner))
    #assert abs(top_corner-bottom_left_corner) == abs(bottom_left_corner - bottom_right_corner) == abs(bottom_right_corner - top_corner)

    dots : list[complex] = []

    for q in range(999999):
        x = randint(-canvas_size, canvas_size)/canvas_size
        y = randint(-canvas_size, canvas_size)/canvas_size
        z = complex(x,y)
        if all([
            cmath.phase(
                (a - z)
                    /
                (a - s)
            ) > 0
            for a,s in [
                [right_corner, upper_left_corner],
                [upper_left_corner, lower_left_corner],
                [lower_left_corner, right_corner],
            ]
        ]):
            distances = [
                (z * cmath.rect(1, c)).real - upper_left_corner.real
                for c in [
                    0,
                    2/3*pi,
                    -2/3*pi,
                ]
            ]
            distances.sort()
            if distances[1] < (right_corner.real - upper_left_corner.real)*1/3:
                dots.append(z)

    for dot in dots:
        dot += complex(1,1)
        dot *= canvas_size
        x = min(max(round(dot.real), 0), canvas_size * 2)
        y = min(max(round(dot.imag), 0), canvas_size * 2)
        canvas[x][y] = [0,0,0]

    bmp_write(canvas, 'test.bmp')
else:
    from h import *
    s = [randint(1, 999) for q in range(999)]
    s = [*{*s}]

    d = 0
    for a in s:
        r=0
        for q in s:
            if q % a == 0:
                r += a*q
        for q in s:
            if a % q == 0:
                r -= a*q
        # r *= a
        d += r
    print(d)
        
