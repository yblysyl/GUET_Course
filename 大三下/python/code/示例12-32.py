import numpy as np
import pyopencl as cl
import pyopencl.array
from pyopencl.elementwise import ElementwiseKernel

#判断素数的C语言版GPU代码
isPrime = ElementwiseKernel(ctx,
    'long *a_g, long *b_g, long *res_g',
    '''
        int j;
        for(j=2; j<b_g[i]; j++)
        {
            if(a_g[i]%j == 0)
            {
                break;
            }
        }
        if(j >= b_g[i])
        {
            res_g[i] = a_g[i];
        }''',
    'isPrime'
)

#定义待测数值范围，和每次处理的数字数量
end = 100000000
start_end = range(2, end)
size = 1000

result = 0

ctx = cl.create_some_context()
queue = cl.CommandQueue(ctx)

#对指定范围内的数字进行分批处理
for i in range(end//size + 1):
    startN = i * size
    #本次要处理的数字范围
    a_np = np.array(start_end[startN: startN+size]).astype(np.int64)
    #b_np里的数字是a_np中数字的平方根取整后加1
    b_np = np.array(list(map(lambda x: int(x**0.5)+1, a_np))).astype(np.int64)
    #把数据写入GPU
    a_g = cl.array.to_device(queue, a_np)
    b_g = cl.array.to_device(queue, b_np)
    res_g = cl.array.zeros_like(a_g)
    #批量判断
    isPrime(a_g, b_g, res_g)
    t = set(filter(None, res_g.get()))
    #记录本批数字中素数的个数
    result += len(t)

print(result)
