import asyncio

try:
    from socket import socketpair
except ImportError:
    from asyncio.windows_utils import socketpair

@asyncio.coroutine
def wait_for_data(loop):
    #创建一对互相连通的Socket
    rsock, wsock = socketpair()

    #注册用来接收数据的Socket
    reader, writer = yield from asyncio.open_connection(sock=rsock, loop=loop)

    #通过Socket写入数据
    loop.call_soon(wsock.send, 'This is a test.'.encode())

    #等待接收数据
    data = yield from reader.read(100)
    print("Received:", data.decode())

    writer.close()
    wsock.close()

loop = asyncio.get_event_loop()
loop.run_until_complete(wait_for_data(loop))
loop.close()
