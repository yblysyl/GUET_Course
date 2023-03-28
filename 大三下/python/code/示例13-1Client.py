import asyncio
import time

class EchoClientProtocol(asyncio.Protocol):
    def __init__(self, message, loop):
        self.message = message
        self.loop = loop

    #连接创建成功
    def connection_made(self, transport):
        for m in message:
            transport.write(m.encode())
            print('Data sent: {!r}'.format(m))
            time.sleep(1)
        #全部消息发送完成，通知对方不再发送消息
        transport.write_eof()

    #收到数据
    def data_received(self, data):
        print('Data received: {!r}'.format(data.decode()))

    #连接被关闭
    def connection_lost(self, exc):
        print('The server closed the connection')
        print('Stop the event loop')
        self.loop.stop()

loop = asyncio.get_event_loop()
message = ['Hello World!', '你好']
coro = loop.create_connection(lambda: EchoClientProtocol(message, loop),
                         '127.0.0.1', 8888)
loop.run_until_complete(coro)
loop.run_forever()
loop.close()
