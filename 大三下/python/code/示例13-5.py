import asyncio
import urllib.parse
import sys

@asyncio.coroutine
def print_http_headers(url):
    url = urllib.parse.urlsplit(url)
    if url.scheme == 'https':
        connect = asyncio.open_connection(url.hostname, 443, ssl=True)
    else:
        connect = asyncio.open_connection(url.hostname, 80)
    reader, writer = yield from connect
    
    query = ('HEAD {path} HTTP/1.0\r\nHost: {hostname}\r\n\r\n'
            ).format(path=url.path or '/', hostname=url.hostname)
    writer.write(query.encode('latin-1'))
    
    while True:
        line = yield from reader.readline()
        if not line:
            break
        line = line.decode('latin1').rstrip()
        if line:
            print('HTTP header> %s' % line)

    writer.close()

url = 'https://docs.python.org/3/library/asyncio-stream.html'
loop = asyncio.get_event_loop()
task = asyncio.ensure_future(print_http_headers(url))
loop.run_until_complete(task)
loop.close()
