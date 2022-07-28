def get_radix_val(x, digit_index, radix) -> int:
	for w in range(digit_index):
		x//=radix
	return x%radix

def american_flag_sort_helper(a_list, start: int, end: int, digit_index, radix) -> None:
	if start==end:
		return
	counts = [0 for _ in range(radix)]
	for i in range(start, end):
		val = get_radix_val(a_list[i], digit_index, radix)
		counts[val] += 1
	offsets = [0 for _ in range(radix)]
	sum = 0
	for i in range(radix):
		offsets[i] = sum
		sum += counts[i]
	i = start
	next_free = offsets[:]
	cur_block = 0
	while cur_block < radix - 1:
		if i >= start + offsets[cur_block + 1]:
			cur_block += 1
			continue
		radix_val = get_radix_val(a_list[i], digit_index, radix)
		if radix_val == cur_block:
			i += 1
			continue
		swap_to = start + next_free[radix_val]
		a_list[i], a_list[swap_to] = a_list[swap_to], a_list[i]
		next_free[radix_val] += 1
	if digit_index == 0:
		return
	for i in range(len(offsets) - 1):
		american_flag_sort_helper(a_list, start+offsets[i], start+offsets[i + 1], digit_index - 1, radix)
	american_flag_sort_helper(a_list, start+offsets[-1], end, digit_index - 1, radix)


def american_flag_sort(a_list, radix) -> None:
	for x in a_list:
		assert type(x) == int
	max_val = max(a_list)
	max_digit = int(floor(log(max_val, radix)))
	american_flag_sort_helper(a_list, 0, len(a_list), max_digit, radix)

from h import *
n=scan()
if n==0:
	exit()
a=[scan() for w in range(n)]
s=a[:]
american_flag_sort(a,256)
s.sort()
if not (a==s):
	print(a)
	print(s)
	1/0

