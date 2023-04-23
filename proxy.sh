(
 [[ -n $ZSH_VERSION && $ZSH_EVAL_CONTEXT =~ :file$ ]] || 
 [[ -n $KSH_VERSION && "$(cd -- "$(dirname -- "$0")" && pwd -P)/$(basename -- "$0")" != "$(cd -- "$(dirname -- "${.sh.file}")" && pwd -P)/$(basename -- "${.sh.file}")" ]] || 
 [[ -n $BASH_VERSION ]] && (return 0 2>/dev/null)
) || (echo 'script should be sourced' ; exit)
export http_proxy="";
export socks_PROXY="";
while [ "$#" != '0' ]
do
    [ "$(echo "$1" | head -c 4)" == 'http' ] && export http_proxy="$1"
    [ "$(echo "$1" | head -c 4)" == 'sock' ] && export socks_proxy="$1"
    shift
done
export http_proxy="$http_proxy"
export HTTP_PROXY="$http_proxy"
export https_proxy="$http_proxy"
export HTTPS_PROXY="$http_proxy"
export ALL_PROXY="$http_proxy"
export all_proxy="$http_proxy"
export socks_PROXY="$socks_proxy"
export SOCKS_PROXY="$socks_proxy"
export socks4_PROXY="$socks_proxy"
export SOCKS4_PROXY="$socks_proxy"
export socks5_PROXY="$socks_proxy"
export SOCKS5_PROXY="$socks_proxy"

