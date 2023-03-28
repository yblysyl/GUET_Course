from multiprocessing import freeze_support
from multiprocessing.managers import BaseManager, BaseProxy
import operator

#普通类
class Foo:
    def f(self):
        print('you called Foo.f()')
    def g(self):
        print('you called Foo.g()')
    def _h(self):
        print('you called Foo._h()')

#生成器
def baz():
    for i in range(10):
        yield i*i

#生成器对象的代理类
class GeneratorProxy(BaseProxy):
    _exposed_ = ['__next__']
    def __iter__(self):
        return self
    def __next__(self):
        return self._callmethod('__next__')

#返回operator模块的函数
def get_operator_module():
    return operator

class MyManager(BaseManager):
    pass

#注册Foo类，默认的公开成员f()和g()可以通过代理访问
MyManager.register('Foo1', Foo)

#注册Foo类，明确指定成员g()和_h()可以通过代理来访问
MyManager.register('Foo2', Foo, exposed=('g', '_h'))

#注册生成器函数baz; 指定代理类型为GeneratorProxy
MyManager.register('baz', baz, proxytype=GeneratorProxy)

#注册函数get_operator_module()，使其可以通过代理进行访问
MyManager.register('operator', get_operator_module)

def test():
    manager = MyManager()
    manager.start()

    print('-' * 20)
    #创建对象
    f1 = manager.Foo1()
    #调用对象成员
    f1.f()
    f1.g()
    #确认对象拥有哪些可访问的成员
    assert not hasattr(f1, '_h')
    assert sorted(f1._exposed_) == sorted(['f', 'g'])

    print('-' * 20)
    f2 = manager.Foo2()
    f2.g()
    f2._h()
    assert not hasattr(f2, 'f')
    assert sorted(f2._exposed_) == sorted(['g', '_h'])

    print('-' * 20)
    it = manager.baz()
    for i in it:
        print('<%d>' % i, end=' ')
    print()

    print('-' * 20)
    op = manager.operator()
    print('op.add(23, 45) =', op.add(23, 45))
    print('op.pow(2, 94) =', op.pow(2, 94))
    print('op._exposed_ =', op._exposed_)

if __name__ == '__main__':
    #支持使用py2exe、Pyinstaller和cx_Freeze打包为Windows可执行程序
    freeze_support()
    test()
