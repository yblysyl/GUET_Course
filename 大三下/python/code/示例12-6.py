import threading
import time
import queue 

#自定义生产者线程类
class Producer(threading.Thread):
    def __init__(self, threadname):
        threading.Thread.__init__(self, name = threadname)
    def run(self):
        global myqueue
        #在队列尾部追加元素
        time.sleep(1)
        try:
            myqueue.put(self.getName(), timeout=1)
            print(self.getName(), ' put ', self.getName(), ' to queue.')
        except:
            pass

class Consumer(threading.Thread):
    def __init__(self, threadname):
        threading.Thread.__init__(self, name = threadname)
    def run(self):
        global myqueue
        #在队列首部获取元素
        time.sleep(0.1)
        try:
            print(self.getName(), ' get ', myqueue.get(timeout=1.1), ' from queue.')
        except:
            pass

myqueue = queue.Queue(5)

#创建生产者线程和消费者线程
plist = []
clist = []
for i in range(10):
    p = Producer('Producer' + str(i))
    plist.append(p)
    c = Consumer('Consumer' + str(i))
    clist.append(c)

#依次启动生产者线程和消费者线程
for p, c in zip(plist, clist):
    p.start()
    c.start()
