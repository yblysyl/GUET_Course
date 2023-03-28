import time
import random
from multiprocessing import Process, Queue, current_process, freeze_support

def worker(task_queue, output):
    #持续执行task_queue.get()，直到取到'STOP'
    for func, args in iter(task_queue.get, 'STOP'):
        #调用相应的函数，并将计算结果放入队列
        result = calculate(func, args)
        output.put(result)

def calculate(func, args):
    result = func(*args)
    return '%s says that %s%s = %s' % \
        (current_process().name, func.__name__, args, result)

def mul(a, b):
    time.sleep(0.5*random.random())
    return a * b

def plus(a, b):
    time.sleep(0.5*random.random())
    return a + b

def test():
    NUMBER_OF_PROCESSES = 4
    TASKS1 = [(mul, (i, 7)) for i in range(10)]
    TASKS2 = [(plus, (i, 8)) for i in range(10)]

    #创建Queue对象
    task_queue = Queue()
    done_queue = Queue()
    
    #创建并启动进程
    for i in range(NUMBER_OF_PROCESSES):
        Process(target=worker, args=(task_queue, done_queue)).start()
        
    #提交任务
    for task in TASKS1:
        task_queue.put(task)

    #输出计算结果
    print('Unordered results:')
    for i in range(len(TASKS1)):
        print('\t', done_queue.get())

    #提交更多任务
    for task in TASKS2:
        task_queue.put(task)

    #输出更多结果
    for i in range(len(TASKS2)):
        print('\t', done_queue.get())

    #发送停止信号
    for i in range(NUMBER_OF_PROCESSES):
        task_queue.put('STOP')

if __name__ == '__main__':
    freeze_support()
    test()
