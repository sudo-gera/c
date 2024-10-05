import datetime
import asyncio
import time
import sys

async def exec_command(*command, input=None):
    process = await asyncio.subprocess.create_subprocess_exec(*command, stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE, stdin=asyncio.subprocess.PIPE)
    stdout, stderr = await process.communicate(input=input)

async def run_ssh(date, server):
    start = time.monotonic()
    await exec_command(*f'sshpass -p 1234567890 ssh {date}-vpnjantit.com@{server}.vpnjantit.com -ND 127.0.0.1:1081 -o ExitOnForwardFailure=yes'.split())
    stop = time.monotonic()
    print(f'connection to {date}@{server} took {stop-start} seconds')

async def main():
    try:
        while 1:
            now = datetime.datetime.now()
            day = datetime.timedelta(days=1)
            await asyncio.gather(*[
                run_ssh(date, server)
                for server in 'nl1 nl2 nl3 nl4'.split()
                for date in [
                    f'{d.day:02d}x{d.month:02d}'
                    for d in [
                        now - offset * day
                        for offset in range(-2, 10)
                    ]
                ]
            ])
            print('waiting...', time.asctime())
            print()
            print()
            await asyncio.sleep(1)
    finally:
        await asyncio.sleep(0.1)


try:
    asyncio.run(main())
except KeyboardInterrupt:
    pass
