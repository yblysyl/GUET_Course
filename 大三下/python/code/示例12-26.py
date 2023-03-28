import asyncio.subprocess
import sys

@asyncio.coroutine
def get_date():
    code = 'import datetime; print(datetime.datetime.now())'

    #创建子进程，并把标准输出重定向到管道
    create = asyncio.create_subprocess_exec(sys.executable, '-c', code,
                                     stdout=asyncio.subprocess.PIPE)
    proc = yield from create

    #读取一行输出
    data = yield from proc.stdout.readline()
    line = data.decode('ascii').rstrip()

    #等待子进程退出
    yield from proc.wait()
    return line

if sys.platform == "win32":
    loop = asyncio.ProactorEventLoop()
    asyncio.set_event_loop(loop)
else:
    loop = asyncio.get_event_loop()

date = loop.run_until_complete(get_date())
print("Current date: %s" % date)
loop.close()
