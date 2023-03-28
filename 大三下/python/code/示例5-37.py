from random import randint, random

def hillMax(lst, howFar):
    '''爬山算法
    lst:待确定最大值的列表
    howFar:爬山时能看到的“最远方”，越大越准确'''
    #由于切片是左闭右开区间，所以howFar必须大于1
    assert howFar>1, 'howFar must >1'
    
    #从列表第一个元素开始爬
    #如果已经到达最后一个元素，或者已找到局部最大值，结束
    start = 0
    ll = len(lst)
    while start <= ll:
        m = lst[start]
        loc = lst[start+1:start+howFar]
        mm = max(loc)
        if m > mm:
            return m
        else:
            #局部最大数的位置
            mmPos = loc.index(mm)
            start += mmPos+1

def simAnnealingMax(lst, howFar):
    '''模拟退火算法，与粗暴的爬山算法相比，有可能跳出局部而获得全局最优解，
    也有可能会因为忽略当前的局部最优解而得到更差的解，参数设置很重要
    lst:待确定最大值的列表
    howFar:爬山时能看到的“最远方”，越大越准确'''
    #由于切片是左闭右开区间，所以howFat必须大于1
    assert howFar>1, 'parameter "howFar" must >1'
    
    #从列表第一个元素开始爬
    #如果已经到达最后一个元素，或者已找到局部最大值，结束
    start = 0
    ll = len(lst)
    #随机走动的次数
    times = 1
    while start <= ll:
        #当前局部最优解
        m = lst[start]
        #下一个邻域内的数字
        loc = lst[start+1:start+howFar]
        #如果已处理完所有数据，结束
        if not loc:
            return m
        #下一个邻域的局部最优解及其位置
        mm = max(loc)
        mmPos = loc.index(mm)
        #如果下一个邻域内有更优解，走过去
        if m <= mm:
            start += mmPos+1
        else:
            #如果下一个邻域内没有更优解，以一定的概率前进或结束
            delta = (m-mm)/(m+mm)
            #随机走动次数越多，对概率要求越低
            if delta <= random()/times:
                start += mmPos+1
                times += 1
            else:
                return m
            
#性能测试，比较两种算法优劣，其中的参数k的值很重要
for j in range(10):
    win = 0
    compareTimes = 1000
    for i in range(compareTimes):
        lst = [randint(1, 100) for i in range(200)]
        k = 3
        if simAnnealingMax(lst, k) >= hillMax(lst, k):
            win += 1
    if win >= compareTimes//2:
        print('win')
