def read_numbers_from_different_lines_as_set(count_of_lines_to_read:int):
    if count_of_lines_to_read<0:
        print('error')
        exit()
    return {
        int(input())
        for q in range(count_of_lines_to_read)
    }
def print_length_and_sorted_content_of_set(s:set):
    print(len(s))
    print(*sorted(list(s)))

n, m = list(map(int, input().split()))

a=read_numbers_from_different_lines_as_set(n)
s=read_numbers_from_different_lines_as_set(m)

print()
print_length_and_sorted_content_of_set(a & s)
print()
print_length_and_sorted_content_of_set(a - s)
print()
print_length_and_sorted_content_of_set(s - a)

