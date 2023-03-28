import threading
from random import randint
from time import sleep

#自定义生产者线程类
class Producer(threading.Thread):
    def __init__(self, threadname):
        threading.Thread.__init__(self,name=threadname)
    def run(self):
        global x
        while True:
            #获取锁
            con.acquire()
            #假设共享列表中最多能容纳20个元素
            if len(x) == 20:
                #如果共享列表已满，生产者等待
                con.wait()
                print('Producer is waiting.....')
            else:
                print('Producer:', end=' ')
                #产生新元素，添加至共享列表
                x.append(randint(1, 1000))
                print(x)
                sleep(1)
                #唤醒等待条件的线程
                con.notify()
            #释放锁
            con.release()
        
#自定义消费者线程类
class Consumer(threading.Thread):
    def __init__(self, threadname):
        threading.Thread.__init__(self, name =threadname)
    def run(self):
        global x
        while True:
            #获取锁
            con.acquire()
            if not x:
                #等待
                con.wait()
                print('Consumer is waiting.....')
            else:
                print(x.pop(0))
                print(x)
                sleep(2)
                con.notify()
            con.release()
        
#创建Condition对象以及生产者线程和消费者线程
con = threading.Condition()
x = []
p = Producer('Producer')
c = Consumer('Consumer')
p.start()
c.start()
p.join()
c.join()
