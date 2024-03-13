curl -s \
-F 'file=@/Users/gera/c/test1.txt' \
"https://pu.vk.com/c909328/upload.php?act=add_doc_new&mid=-218708263&aid=-1&gid=0&type=0&peer_id=-218708263&rhash=0398c5f5d2941114f0b4b792fd3dac18&api=1&server=909328&_origin=https%3A%2F%2Fapi.vk.com&_sig=b1408d610d5a1e812c0db831dd4fd050" \
| python3 -m json.tool

