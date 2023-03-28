class Node:
    '''节点结构'''
    def __init__(self, data, leftNode=None, rightNode=None):
        #设置当前节点的值和指向下一个节点的指针
        self.data = data
        self.left = leftNode
        self.right = rightNode

    def insertAfter(self, node):
        if node.data == 'HEAD':
            print('You cannot make another head node.')
            return
        
        #在当前节点后面插入新节点，要考虑当前节点是否为最后一个节点
        node.right = self.right
        if self.right != None:
            self.right.left = node
        node.left = self
        self.right = node

    def insertBefore(self, node):
        if self.data == 'HEAD':
            print('You cannot insert node before the head node.')
            return
        if node.data == 'HEAD':
            print('You cannot make another head node.')
            return
        
        #在当前节点前面插入新节点，要考虑当前节点是否为第一个节点
        node.left = self.left
        if self.left != None:
            self.left.right = node
        node.right = self
        self.left = node

    def deleteRight(self):
        #删除当前节点之后的节点
        if self.right == None:
            print('Nothing to delete')
            return
        p = self.right
        if p.right != None:
            p.right.left = self
        self.right = p.right
        #删除节点，释放空间
        del p

    def deleteLeft(self):
        #删除当前节点之前的节点
        p = self.left
        if p.data == 'HEAD':
            print('Nothing to delete.')
            return
        self.left = p.left
        p.left.right = self
        #删除节点，释放空间
        del p

#头节点
head = Node('HEAD')

p = head
for i in range(1, 10):
    #依次生成9个数字，并创建相应的节点
    #把节点连接到链表的尾部
    n = Node(i)
    p.insertAfter(n)
    p = n

p = head
#遍历链表节点，插入新节点，删除前后节点
while p:
    if p.data == 3:
        p.deleteRight()
        p.deleteLeft()
        p.insertBefore(Node(2.5))
        p.insertAfter(Node(3.5))
        break
    else:
        p = p.right

#正向遍历链表并输出每个节点的值
p = head
while p:
    print(p.data, end='-->')
    tail = p
    p = p.right
print('None')

#反向遍历链表并输出每个节点的值
p = tail
while p.data != 'HEAD':
    print(p.data, end='-->')
    p = p.left
print('HEAD')
