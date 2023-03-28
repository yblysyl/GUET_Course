import asyncio

class EchoServerClientProtocol(asyncio.Protocol):
    #连接建立成功
    def connection_made(self, transport):
        peername = transport.get_extra_info('peername')
        print('Connection from {}'.format(peername))
        self.transport = transport

    #收到数据
    def data_received(self, data):
        message = data.decode()
        print('Data received: {!r}'.format(message))

        print('Send: {!r}'.format(message))
        self.transport.write(data)

    #对方发送消息结束
    def eof_received(self):
        print('Close the client socket')
        self.transport.close()

loop = asyncio.get_event_loop()
#创建服务器，每个客户端的连接请求都会创建一个新的Protocol实例
coro = loop.create_server(EchoServerClientProtocol, '127.0.0.1', 8888)
server = loop.run_until_complete(coro)

#服务器一直运行，直到用户按下组合键Ctrl+C
print('Serving on {}'.format(server.sockets[0].getsockname()))
try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

#关闭服务器
server.close()
loop.run_until_complete(server.wait_closed())
loop.close()
