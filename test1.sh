curl -s 'https://api.vk.com/method/docs.getMessagesUploadServer' \
-F "access_token=${token}" \
-F "v=5.199" \
-F "peer_id=${peer_id}" \
| python3 -m json.tool

