curl -s 'https://api.vk.com/method/messages.send' \
-F "access_token=${token}" \
-F "v=5.199" \
-F "random_id=0" \
-F "peer_id=${peer_id}" \
-F "attachment=doc-${group_id}_670381440" \
| python3 -m json.tool

