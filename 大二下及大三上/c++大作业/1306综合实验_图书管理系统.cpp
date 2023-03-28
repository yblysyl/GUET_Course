#include<iostream>
#include<string>
#include<list>
#include<fstream>
#include<sstream>
#include <vector>
using namespace std;

class Imformation
{
	public:
	    string	dengluhao;
	    string  shuming;
	    string  zuozheming;
	    string  fenleihao;
	    string  danwei;
	    string  shijian;
	    string  jiage;
	public:
		string shuchu(){
 			return dengluhao+" "+shuming+" "+zuozheming+" "+fenleihao+" "+danwei+" "+shijian+" "+jiage;
 				///cout<<a.dengluhao<<" "<<a.shuming<<" "<<a.zuozheming<<" "<<a.fenleihao<<" "<<a.danwei<<" "<<a.shijian<<" "<<a.jiage<<endl; 
		 }
		 string shuchu2(){
 			return "登录号："+dengluhao+"书名："+shuming+" 作者名："+zuozheming+"分类号："+fenleihao+"出版单位： "+danwei+"出版时间： "+shijian+"价格 "+jiage;
 				///cout<<a.dengluhao<<" "<<a.shuming<<" "<<a.zuozheming<<" "<<a.fenleihao<<" "<<a.danwei<<" "<<a.shijian<<" "<<a.jiage<<endl; 
		 }
 		
}; 
 
 
 class Guanliyuan
 {
 	public:
 		string zhanghao;
 		string mima;
 };
 
 class fangfa
 {
 	public:
		list<Imformation> wenjian(list<Imformation> list1){  // 新建信息 函数 
			Imformation a;
			cout<<"请输入图书信息"<<endl; 
			cout<<"输入登录号"<<endl; 
			cin>>a.dengluhao;
			cout<<"输入书名"<<endl; 
			cin>>a.shuming; 
			cout<<"输入作者名"<<endl; 
			cin>>a.zuozheming;
			cout<<"输入分类号"<<endl; 
			cin>>a.fenleihao;
			cout<<"输入时间"<<endl; 
			cin>>a.shijian;
			cout<<"输入出版单位"<<endl; 
			cin>>a.danwei;
			cout<<"输入价格"<<endl; 
			cin>>a.jiage;
			  list1.push_front(a);   //在列表头插入元素； 
			  this->wenjianshuchu(list1);//调用保存方法保存更改到实体文件中 
			  return  list1;
		}
	list<Imformation>	wenjianshuru(){//从文件中读出数据 
		list<Imformation> list1;
    ifstream readFile("Test.txt");//文件对象 
    while(!readFile.eof()){//判断是否读完 
    	Imformation a;
    	readFile>>a.dengluhao>>a.shuming>>a.zuozheming>>a.fenleihao>>a.danwei>>a.shijian>>a.jiage;
    	list1.push_front(a);
	}
    readFile .close();
    return list1;
	}
 	
	 void wenjianshuchu(list<Imformation> list1){//向文件中保存数据 
		ofstream OutFile("Test.txt");
		cout << "mylist contains:";
		for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){//调用迭代器进行循环 
		Imformation a=*it;
   		 //string aaa="This is a Test12!";
   		 if(it==list1.begin()){//
    		OutFile << a.shuchu();
			}
		else OutFile <<" "+a.shuchu(); //<< OutFile 
		}
	 	OutFile.close();	
		 }
	 
	 
	 void liulanquanbu(list<Imformation> list1){  //遍历浏览 
	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){//
		Imformation a=*it;
		cout<<a.shuchu2()<<endl;	
	 	}
	}
	
	
	
	 void chaxun(list<Imformation> list1){//查询子菜单 
	 	string temp;
	 	int tuichubianliang=1;
	 		while(tuichubianliang){
 		cout<<"请选择查询方式"<<endl;
 		cout<<"0,退出"<<endl; 
 		cout<<"1，按书名查询"<<endl;
 		cout<<"2，按作者名查询"<<endl;
 		int a;
 		cin>>a;
 		
 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:
            	cout<<"输入要查询书名"<<endl; 
            	cin>>temp;
            	shumingchaxun(temp,list1) ; //
              //  System.out.println("null");
                break;
            case 2:
            	cout<<"输入要查询作者名"<<endl; 
            	cin>>temp;
               zuozhemingchaxun(temp,list1) ;//
                break;
            default:
                cout<<"输入错误"<<endl;
        }
		  
	 }
	 	
	 
	}
	void shumingchaxun(string sm,list<Imformation> list1){//书名查询 
	 	bool chadao=false;
	 	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){//
		Imformation a=*it;
		if(a.shuming==sm ) {
				cout<<a.shuchu2()<<endl;	
				chadao=true;
		}
	 	}
		 if(!chadao)cout<<"无结果"<<endl;	
	 }

	void zuozhemingchaxun(string sm,list<Imformation> list1){//作者名查询 
	 	bool chadao=false;
	 	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){
		Imformation a=*it;
		if(a.zuozheming==sm ) {
				cout<<a.shuchu2()<<endl;	
				chadao=true;
		}
	 	}
		 if(!chadao)cout<<"无结果"<<endl;	
	 }
	 
	 
	 list<Imformation> shanchu(list<Imformation> list1){
	 	string temp;
	 	int tuichubianliang=1;
	 		while(tuichubianliang){
 		cout<<"请选择删除方式"<<endl;
 		cout<<"0,退出"<<endl; 
 		cout<<"1，按登录号删除"<<endl;
 		cout<<"2，按书名批量删除"<<endl;
 		cout<<"3，按作者名批量删除"<<endl;
 		cout<<"4，按分类号批量删除"<<endl;
 		int a;
 		cin>>a;
 		
 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:
            	cout<<"输入要删除书籍的登录号"<<endl; 
            	cin>>temp;
            	shanchu(temp,list1,a) ; 
              //  System.out.println("null");
                break;
            case 2:
            	cout<<"输入要批量删除书籍的书名"<<endl; 
            	cin>>temp;
               shanchu(temp,list1,a) ; 
                break;
                case 3:
            	cout<<"输入要批量删除书籍的作者名"<<endl; 
            	cin>>temp;
               shanchu(temp,list1,a) ; 
                break;
                case 4:
            	cout<<"输入要批量删除的分类号"<<endl; 
            	cin>>temp;
               shanchu(temp,list1,a); 
                break;
            default:
                cout<<"输入错误"<<endl;
        }
        list1=this->wenjianshuru();
		  
	 }
	 return list1;
}
	 void shanchu(string sm,list<Imformation> list1,int b){//根据b的值进行不同方式的·删除 
	 	bool chadao=false;
	 	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ){
		Imformation a=*it;
		string panduan;
		if(b==1){
			panduan=a.dengluhao;
		}else if(b==2){
			panduan=a.shuming;
		}else if(b==3){
			panduan=a.zuozheming; 
		}else if(b==4){
		panduan=a.fenleihao;
		}else {
			cout<<"删除异常"<<endl;
			return ; 
		}
		if(panduan==sm ) {
	 	it=list1.erase(it);//删除调用 
		cout<<a.shuchu()<<endl;
				chadao=true;
				continue;//跳出此次循环 
		}
		++it;
	 	}
		 if(!chadao)cout<<"无可删除对象"<<endl;
		 this->wenjianshuchu(list1); 
	 }
	 
	 
	 
	 
	 list<Imformation> xiugai(list<Imformation> list1){//修改菜单 
	 	string temp;
	 	int tuichubianliang=1;
	 		while(tuichubianliang){
 		cout<<"请选择操作"<<endl;
 		cout<<"0,退出"<<endl; 
 		cout<<"1，按登录号修改信息"<<endl;
 		int a;
 		cin>>a;

 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:{ 
            	cout<<"输入要修改书籍的登录号"<<endl; 
            	cin>>temp;
				bool chadao=false;
	 			for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){
					Imformation a=*it;
					if(a.dengluhao==temp ) {
					list1.erase(it);
					list1=this->wenjian(list1);
					chadao=true;
					break;
					}
	 			}
		 if(!chadao)cout<<"无可修改元素"<<endl;
                break; 
                } 
            default:
                cout<<"输入错误"<<endl;
        }
        list1=this->wenjianshuru();
		  
	 }
	 return list1;
}
	 
	 
 	 
		 
void	denglu() {
	Guanliyuan c1; 
	bool xunhuan=true;
	while(xunhuan){
		cout<<"请输入账号"<<endl;
		cin>>c1.zhanghao;
		cout<<"请输入密码"<<endl;
		cin>> c1.mima;
		if(c1.zhanghao=="123"&&c1.mima=="123"){
			xunhuan=false;
		cout<<"欢迎管理员登录"<<endl;	
		}else  cout<<"账号或密码错误"<<endl;
	}
		
	}
	
	
	
	
	
	
	
	 
 };
 int main()
 {
 	fangfa fangf;//方法类 调用操作方法 
 	int tuichubianliang=1;
 	list<Imformation> my_list;//列表，用来暂时存储所有信息 
 	my_list = fangf.wenjianshuru();
 	fangf.denglu();
 	
 	while(tuichubianliang){
 		cout<<"请选择操作"<<endl;
 		cout<<"0,退出"<<endl; 
 		cout<<"1，浏览"<<endl;
 		cout<<"2，录入"<<endl;
 		cout<<"3，查询"<<endl;
 		cout<<"4，删除"<<endl;
 		cout<<"5，修改"<<endl;
 		int a;
 		cin>>a;
 		
 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:
            	fangf.liulanquanbu(my_list);
              //  System.out.println("null");
                break;
            case 2:
               my_list=fangf.wenjian(my_list);
                break;
            case 3:
                fangf.chaxun(my_list);
                break;
                case 4:
               my_list=fangf.shanchu(my_list);
                break;
                case 5:
               my_list=fangf.xiugai(my_list);
                break;
            default:
                cout<<"输入错误"<<endl;
        }
		  
	 }
 	
   

 }
