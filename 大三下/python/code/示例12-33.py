import tensorflow as tf
import numpy as np
import time

#使用 NumPy 生成随机数据, 总共 2行100列个点.
x_data = np.float32(np.random.rand(2, 200))
#矩阵乘法
#这里的W=[0.100, 0.200]和b=0.300是理论数据，通过后面的训练来验证
y_data = np.dot([0.100, 0.200], x_data) + 0.300

#构造一个线性模型，训练求解W和b
#初始值b = [0.0]
b = tf.Variable(tf.zeros([1]))
#初始值W为1x2的矩阵，元素值介于[-1.0, 1.0]区间
W = tf.Variable(tf.random_uniform([1, 2], -1.0, 1.0))
#构建训练模型，matmul为矩阵乘法运算
y = tf.matmul(W, x_data) + b

#最小均方差
loss = tf.reduce_mean(tf.square(y - y_data))
#使用梯度下降算法进行优化求解
optimizer = tf.train.GradientDescentOptimizer(0.5)
train = optimizer.minimize(loss)

#初始化变量
init = tf.global_variables_initializer()

with tf.device('/gpu:0'):
    with tf.Session() as sess:
        #初始化
        sess.run(init)

        #拟合平面，训练次数越多越精确，但是也没有必要训练太多次
        for step in range(0, 201):
            sess.run(train)
            #显示训练过程，这里演示了两种查看变量值的方法
            print(step, sess.run(W), b.eval())
