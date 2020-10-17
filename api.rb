require "net/http"
r=''
Net::HTTP.start('kpml.ru') do |q| ;r=q.get('/pages/raspisanie/izmeneniya-v-raspisanii') end
puts r.body


url=File.read 'url' 'r'
token=url.split('#')[1].split('&")[0].split('=')[1]


def api(path,data=''):
 if path!='' and path[-1] not in '&?' do
  if '?' in path do
   path+='&'
  end
  else do
   path+='?'
  end
 end
 sleep(1/6)
 data=data.encode()
 global token
 ret= loads(urlopen('https://api.vk.com/method/'+path+'v=5.101&access_token='+token,data=data).read().decode())
 return ret


