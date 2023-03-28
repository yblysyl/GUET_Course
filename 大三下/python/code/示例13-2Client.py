import asyncio
import time

class EchoClientProtocol:
    def __init__(self, message, loop):
        self.message = message
        self.loop = loop

    def connection_made(self, transport):
        self.transport = transport
        self.transport.sendto(self.message.encode())

    def datagram_received(self, data, addr):
        print("Now is:", data.decode())
        self.transport.close()

    def error_received(self, exc):
        print('Error received:', exc)

    def connection_lost(self, exc):
        self.loop.stop()

loop = asyncio.get_event_loop()
message = "ask for time"
while True:
    connect = loop.create_datagram_endpoint(
        lambda: EchoClientProtocol(message, loop),
        remote_addr=('10.2.1.2', 9999))
    transport, protocol = loop.run_until_complete(connect)
    loop.run_forever()
    transport.close()
    time.sleep(1)
loop.close()
