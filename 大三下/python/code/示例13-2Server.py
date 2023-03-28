import asyncio
import datetime
import socket

class EchoServerProtocol:
    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = data.decode()
        print('Received from', str(addr))
        now = str(datetime.datetime.now())[:19]
        self.transport.sendto(now.encode(), addr)
        print('replied')

loop = asyncio.get_event_loop()
print("Starting UDP server")
#获取本机IP地址
ip = socket.gethostbyname(socket.gethostname())
#创建Protocol实例，服务所有客户端
listen = loop.create_datagram_endpoint(EchoServerProtocol, local_addr=(ip, 9999))
transport, protocol = loop.run_until_complete(listen)

try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

transport.close()
loop.close()
