import threading

#自定义线程类
class mythread(threading.Thread):
    def __init__(self, threadname):
        threading.Thread.__init__(self, name = threadname)
        
    def run(self):
        global myevent
        #根据Event对象是否已设置做出不同的响应
        if myevent.isSet():
            #清除标志
            myevent.clear()
            #等待
            myevent.wait()
            print(self.getName()+' set')
        else:
            print(self.getName()+' not set')
            #设置标志
            myevent.set()

myevent = threading.Event()
#设置标志
myevent.set()

for i in range(10):
    t = mythread(str(i))
    t.start()
