import numpy

l = numpy.array(
    [
        [1, 2, 3],
    ]
)




g = numpy.array(
    [
        [4, 1, 0],
        [1, 4, 0],
        [0, 0, 1],
    ]
)


r = numpy.array(
    [
        [1],
        [2],
        [3],
    ]
)

print(l @ g @ r)
