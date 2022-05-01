from h import *
try:
	a=urlopen('https://api.ipify.org').read()
	a=loads(urlopen('http://ip-api.com/batch',data=b'[{"query":"'+a+b'","fields":"isp"}]').read().decode())
except KeyboardInterrupt:
	a=''
	print()
except:
	a=''
if a:
	a=a[0]['isp']
	print('current provider is:',a)
	try:
		a=input('switch? ')
	except KeyboardInterrupt:
		print()
	except:
		a='n'
	if a.lower() in ['y','']:
		print('switching...')
		system('adb connect 192.168.49.1:53142')
		system('adb shell cmd statusbar click-tile com.cloudflare.onedotonedotonedotone/com.cloudflare.app.domain.quicksettingstile.QuickSettingsTileService')
	else:
		print('aborted.')
