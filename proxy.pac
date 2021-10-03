function FindProxyForURL(url, host){
	// alert('_____________________________________')
	if(host=='192.168.49.1'){
		return 'DIRECT';
	}else{
		// alert(isResolvable('google.com'));
		if (isResolvable('google.com')){
			return "DIRECT; PROXY 192.168.49.1:8282; SOCKS 192.168.49.1:8181";
		}else{
			return "PROXY 192.168.49.1:8282; SOCKS 192.168.49.1:8181; DIRECT";
		}
		// alert(isResolvable('192.168.49.1:8282/proxy.pac'));
		// return "DIRECT; PROXY 192.168.49.1:8282; SOCKS 192.168.49.1:8181";
		// return "PROXY 192.168.49.1:8282; SOCKS 192.168.49.1:8181; DIRECT";
	}
}