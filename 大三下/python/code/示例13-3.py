import asyncio

try:
    from socket import socketpair
except ImportError:
    from asyncio.windows_utils import socketpair

class MyProtocol(asyncio.Protocol):
    def connection_made(self, transport):
        self.transport = transport

    def data_received(self, data):
        #接收数据，关闭Transport对象
        print("Received:", data.decode())
        self.transport.close()

    def connection_lost(self, exc):
        #Socket已被关闭，停止事件循环
        loop.stop()

#创建一对互相连通的Socket
rsock, wsock = socketpair()
loop = asyncio.get_event_loop()

#注册用来等待接收数据的Socket
connect_coro = loop.create_connection(MyProtocol, sock=rsock)
transport, protocol = loop.run_until_complete(connect_coro)

#往互相连通的Socket中的一个写入数据
loop.call_soon(wsock.send, 'hello world.'.encode())

#启动事件循环
loop.run_forever()

rsock.close()
wsock.close()
loop.close()
