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

def create_example_list_of_strings(string_length:int,list_length:int):
    return [create_example_string(string_length) for q in range(list_length)]

def get_max_of_any_container(container): # solve the task
    result_list=[]
    for q in container:
        if result_list:
            if q>result_list[0]:
                result_list[0]=q
        else:
            result_list.append(q)
    if result_list:
        return result_list[0]
    else:
        print('error')

def pretty_print_collection(c):
    pprint.pprint(c)

# showing the work

d=create_example_dict_with_strings_and_numbers(9,4,9,1,9)
pretty_print_collection(d)
print(get_max_of_any_container(d))

length=create_example_list_of_strings(9,9)
pretty_print_collection(length)
print(get_max_of_any_container(length))

