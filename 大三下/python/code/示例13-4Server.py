import asyncio

messages = {'Hello':'nihao',
           'How are you?':'Fine, thank you.',
           'Did you have breakfast?':'Yes',
           'Bye':'Bye'}
@asyncio.coroutine
def handle_echo(reader, writer):
    while True:
        data = yield from reader.read(100)
        message = data.decode()
        addr = writer.get_extra_info('peername')
        print("Received %r from %r" % (message, addr))

        messageReply = messages.get(message, 'Sorry')
        print("Send: %r" % messageReply)
        writer.write(messageReply.encode())
        yield from writer.drain()
        if messageReply == 'Bye':
            break

    print("Close the client socket")
    writer.close()

#创建事件循环
loop = asyncio.get_event_loop()
#创建并启动服务器
coro = asyncio.start_server(handle_echo, '10.2.1.2', 8888, loop=loop)
server = loop.run_until_complete(coro)

print('Serving on {}'.format(server.sockets[0].getsockname()))
#按组合键Ctrl+C或Ctrl+Break退出
try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

# Close the server
server.close()
loop.run_until_complete(server.wait_closed())
loop.close()
