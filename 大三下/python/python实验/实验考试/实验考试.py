import csv

class QuadraticEquation:
    def __init__(self,a=1,b=1,c=1):
        self.a=a
        self.b=b
        self.c=c
    def getroot(self):
        dict1={}
        panduan=self.b**2-4*self.a*self.c
        self.x1=(-self.b+panduan**0.5)/(2*self.a)
        self.x2=(-self.b-panduan**0.5)/(2*self.a)
        dict1['x1']=(-self.b+panduan**0.5)/(2*self.a)
        dict1['x2']=(-self.b-panduan**0.5)/(2*self.a)
        if panduan >0:
            dict1['state']=1
        elif panduan==0:
            dict1['state']=0
        else:
            dict1['state']=2
        return dict1
    def outputresult(self,result):
        print("{}x+{}x**2+{}=0".format(self.a,self.b,self.c),end=" ")
        if result['state']==0:
            print("has two equal roots x1=x2=%.3f" %result['x1'])
        elif result['state']==1:
            print("has two inequal real roots:x1=%.3f,x2=%.3f" %(result['x1'],result['x2']))
        elif result['state']==2:
            print("has two complex roots x1={:.3f},x2={:.3f}".format(result['x1'],result['x2']))



def wenjian():
    with open('shiyanwenjian.csv', newline='') as csvfile:
        with open("result.txt", 'w', encoding='utf-8')as csvfile2:
            spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
            for row in spamreader: 
                equation=QuadraticEquation(float(row[0]),float(row[1]),float(row[2]))
                result=equation.getroot()
                csvfile2.write(row[0]+','+row[1]+','+row[2]+','+"{:.3f},{:.3f}\n".format(equation.x1,equation.x2))
            csvfile2.close()
            csvfile.close()
wenjian()
print("接下来通过输入")
while True:
    try:
        a,b,c=eval(input('please input three float number:空格隔开'))
        equation=QuadraticEquation(a,b,c)
    except:
        equation=QuadraticEquation() 
    result=equation.getroot()  
    equation.outputresult(result) #调用对象的方法更友好地显示结果
    if input('continue(y/n)?').lower()!='y':
        break

