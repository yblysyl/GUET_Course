from heapq import heapify, heappush, heappop
from itertools import count
from collections import Counter
from random import choice
from string import ascii_letters, digits

def huffman(seq, frq):
    #这里的count()依次生成0,1,2,3,4,...
    #主要用来入堆时保持顺序
    num = count()
    #对原始列表进行堆化
    trees = list(zip(frq, num, seq))
    heapify(trees)
    while len(trees)>1:
        #弹出堆中频次最少的两个元素
        #_表示不关心这个值
        fa, _, a = heappop(trees)
        fb, _, b = heappop(trees)
        #合并后生成新节点，重新入堆
        heappush(trees, (fa+fb, next(num), [a,b]))

    #返回建好的二叉树    
    return trees[0][-1]

def codes(tree, prefix=''):
    if len(tree) == 1:
        #注意，这里不能合并成一个return (tree, prefix)语句
        yield (tree, prefix)
        return
    #二叉树左边节点编码为0，右边节点编码为1
    for bit, child in zip('01', tree):
        #在父节点编码基础上，接上每个节点的编码
        for pair in codes(child, prefix + bit):
            yield pair

def main(seq):
    #统计各字符频次
    global temp
    temp = Counter(seq)
    #这里只是为了让输出结果更直观，但实际上会影响效率
    for item in sorted(temp.items(), key=lambda x: x[1], reverse=True):
        print(item)
    print('='*20)
    #根据各字符出现频次，生成哈夫曼树
    seq = list(temp.keys())
    frq = [temp[t] for t in seq]
    tree = huffman(seq, frq)
    #根据哈夫曼树，返回各字符编码的生成器对象
    return codes(tree)

letters = ascii_letters + digits
avgLength = 0
#生成随机字符串，模拟信源信号
seq = ''.join((choice(letters) for i in range(100)))
print(seq+'\n'+'='*20)
#按编码长度从小到大输出
#这里只是为了让输出结果更直观，但实际上会影响效率
for item in sorted(main(seq), key=lambda x: len(x[1])):
    print(item)
    avgLength += temp.get(item[0]) * len(item[1])
    
#计算并输出平均码长
print(avgLength/len(seq))
