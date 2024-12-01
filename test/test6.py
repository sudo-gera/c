import random
import pprint
def create_example_string(length:int):
    if length<0:
        print('error')
        exit()
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(length)])[:length]

def create_example_dict_with_strings_and_numbers(length_of_dict:int, min_length_of_string:int, max_length_of_string:int, min_number:int, max_number:int):
    if length_of_dict<0 or min_length_of_string<0 or min_length_of_string>max_length_of_string or min_number>max_number:
        print('error')
        exit()
    return {
        create_example_string(random.randint(min_length_of_string, max_length_of_string)): random.randint(min_number, max_number)
        for q in range(length_of_dict)
    }

def swap_keys_and_values(d:dict): # solve the task
    res={}
    for q,w in d.items():
        res[w]=[]
    for q,w in d.items():
        res[w].append(q)
    return res

def print_dict(d:dict):
    pprint.pprint(d)

# showing the work

d=create_example_dict_with_strings_and_numbers(9,4,9,1,9)
print_dict(d)
d=swap_keys_and_values(d)
print_dict(d)
