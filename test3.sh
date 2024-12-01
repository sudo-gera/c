curl -s 'https://api.vk.com/method/docs.save' \
-F "access_token=${token}" \
-F "v=5.199" \
-F "file=-218708263|0|-1|909328|cd83e38dff|txt|22698|test1.txt|72cf6a70502728d9627ab224919327c7|32a80589d56035732173f3eb852c268a||||eyJkaXNrIjoiMzciLCJwZWVyX3NlbmRlciI6Ii0yMTg3MDgyNjMifQ==" \
| python3 -m json.tool

