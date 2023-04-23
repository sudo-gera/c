echo "$0"
export _q=1
hp="8080"
sp="1080"
hadd="http://192.168.49.1"
sadd="socks5h://192.168.49.1"
export http_proxy="$hadd:$hp";
export HTTP_PROXY="$hadd:$hp";
export https_proxy="$hadd:$hp";
export HTTPS_PROXY="$hadd:$hp";
export socks_PROXY="$sadd:$sp";
export SOCKS_PROXY="$sadd:$sp";
export socks4_PROXY="$sadd:$sp";
export SOCKS4_PROXY="$sadd:$sp";
export socks5_PROXY="$sadd:$sp";
export SOCKS5_PROXY="$sadd:$sp";
export ALL_PROXY="$hadd:$hp";
export all_proxy="$hadd:$hp";

