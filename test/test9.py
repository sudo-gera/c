import random
def create_example_list_with_random_numbers(length:int):
    if length<0:
        print('error')
        exit()
    return [
        random.randint(0,9)
        for q in range(length)
    ]
def convert_list_to_set_concatenating_repeating_numbers(l:list): # solve the task
    l.sort()
    s=[]
    for q,w in zip(l,l[1:]+[-1]):
        s.append(str(q)+' '*(q!=w))
    return {
        int(q)
        for q in ''.join(s).split()
    }
def print_collection_in_one_line(c):
    print(*c)

# showing the work
l=create_example_list_with_random_numbers(9)
print_collection_in_one_line(l)
s=convert_list_to_set_concatenating_repeating_numbers(l)
print_collection_in_one_line(s)
