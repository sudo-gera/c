import json
from urllib.request import urlopen
from pprint import pprint
import time

group_token = [*json.load(open('/Users/gera/.IPoVKtoken')).items()][-3][0]

def api(path):
    time.sleep(1)
    url = f'https://api.vk.ru/method/{path}&v=5.154&access_token={group_token}'
    result = json.load(urlopen(url))
    # pprint(result)
    return result['response']

my_id = 225847803


print()
print('=== group id ===')
pprint(api('groups.getById?'))

print()
print('=== my id ===')
pprint(api(f'users.get?user_ids={my_id}'))

print()
print('=== chat id ===')
chat_id = api(f'messages.createChat?user_ids={my_id}&title=EXAMPLE')
# chat_id = 30
print(chat_id)

print()
print('=== chat members ===')
pprint(api(f'messages.getConversationMembers?peer_id={2000000000 + chat_id}'))


