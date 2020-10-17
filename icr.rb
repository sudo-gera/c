require "net/http"
r=''
Net::HTTP.start('kpml.ru') do |q| ;r=q.get('/pages/raspisanie/izmeneniya-v-raspisanii') end
puts r.body
