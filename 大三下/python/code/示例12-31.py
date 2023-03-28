import time
import pycuda.autoinit
import pycuda.driver as drv
import numpy as np
from pycuda.compiler import SourceModule

#编译C代码进入显卡，并行判断素数
mod = SourceModule('''
__global__ void isPrime(int *dest, int *a, int *b)
{
    const int i = threadIdx.x+blockDim.x*blockIdx.x;
    int j;
    for(j=2;j<b[i];j++)
    {
        if(a[i]%j == 0)
        {
            break;
        }
    }
    if(j >= b[i])
    {
        dest[i] = a[i];
    }
}
''')

#定义待测数值范围，和每次处理的数字数量
end = 100000000
size = 1000

#获取函数
isPrime = mod.get_function("isPrime")
result = 0

start = time.time()
#分段处理，每次处理1000个数字
for i in range(end//size):
    startN = i * size
    a = np.array(range(startN, startN+size)).astype(np.int64)
    #b中是a中对应数字的平方根加1后的整数，用于快速判断素数
    b = np.array(list(map(lambda x: int(x**0.5)+1, a))).astype(np.int64)
    dest = np.zeros_like(a)
    isPrime(drv.Out(dest), drv.In(a), drv.In(b),
            block=(size,1,1), grid=(2,1))
    result += len(set(filter(None, dest)))
print(time.time()-start)

#上面的代码中把1也算上了，这里减去
print(result-1)
