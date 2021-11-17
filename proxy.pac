function FindProxyForURL(url, host){
	if(host=='192.168.49.1'){
		return 'DIRECT';
	}else{
		if (isResolvable('google.com')){
			return "DIRECT; PROXY 192.168.49.1:8282; SOCKS 192.168.49.1:8181";
		}else{
			return "SOCKS 192.168.49.1:8181; PROXY 192.168.49.1:8282; DIRECT";
		}
	}
}