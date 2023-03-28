from random import randint

def mul(a, b):
    '''小学竖式两个整数相乘的算法实现'''
    #把两个整数分离开成为各位数字再逆序
    aa = list(map(int, reversed(str(a))))
    bb = list(map(int, reversed(str(b))))
    
    #n位整数和m位整数的乘积最多是n+m位整数
    result = [0] * (len(aa)+len(bb))
    
    #按小学整数乘法竖式计算两个整数的乘积
    for ia, va in enumerate(aa):
        #c表示进位，初始为0
        c = 0
        for ib, vb in enumerate(bb):
            #Python中内置函数devmod()可以同时计算整商和余数
            c, result[ia+ib] = divmod(va*vb+c+result[ia+ib], 10)
        #最高位的余数应进到更高位
        result[ia+ib+1] = c

    #整理，变成正常结果
    result = int(''.join(map(str,reversed(result))))
    return result

#测试
for i in range(100000):
    a = randint(1, 1000)
    b = randint(1, 1000)
    r = mul(a, b)
    if r != a*b:
        print(a, b, r, 'error')
