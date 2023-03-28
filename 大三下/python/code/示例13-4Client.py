import asyncio

@asyncio.coroutine
def tcp_echo_client(loop):
    reader, writer = yield from asyncio.open_connection('10.2.1.2', 8888,loop=loop)

    while True:
        message = input('You said:')
        writer.write(message.encode())
        data = yield from reader.read(100)
        print('Received: %r' % data.decode())
        if message == 'Bye':
            break
        
    print('Close the socket')
    writer.close()

loop = asyncio.get_event_loop()
loop.run_until_complete(tcp_echo_client(loop))
loop.close()
