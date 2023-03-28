import asyncio
import operator
import functools

@asyncio.coroutine
def slow_operation(future, n):
    yield from asyncio.sleep(1)
    result = functools.reduce(operator.mul, range(1, n+1))
    #设置计算结果
    future.set_result(result)

loop = asyncio.get_event_loop()
future = asyncio.Future()
#创建并启动任务，计算50的阶乘
asyncio.ensure_future(slow_operation(future, 50))
loop.run_until_complete(future)
#输出计算结果
print(future.result())
loop.close()
