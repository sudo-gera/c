import prettytable
import random
import pprint
def create_string(l):
    if l<0:
        print('error')
        exit()
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(l)])[:l]
def create_cart(n):
    if n<0:
        print('error')
        exit()
    cart={}
    for q in range(n):
        cart[q+1]=dict(
            name=create_string(9),
            price=random.randint(1,9),
            count=random.randint(1,9),
        )
    return cart
def print_cart(cart):
    pprint.pprint(cart)
def count_price(cart):
    table=[]
    p_table=prettytable.PrettyTable()
    p_table.field_names=['name','cost']
    for q,w in cart.items():
        table.append([w['name'],w['price']*w['count']])
    table.sort(key=lambda r:r[1],reverse=True)
    for q in table:
        p_table.add_row(q)
    return p_table
def print_table(table):
    print(table)
cart=create_cart(9)
print_cart(cart)
table=count_price(cart)
print_table(table)




