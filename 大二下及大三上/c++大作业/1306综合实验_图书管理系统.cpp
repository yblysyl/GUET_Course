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
 			return "��¼�ţ�"+dengluhao+"������"+shuming+" ��������"+zuozheming+"����ţ�"+fenleihao+"���浥λ�� "+danwei+"����ʱ�䣺 "+shijian+"�۸� "+jiage;
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
		list<Imformation> wenjian(list<Imformation> list1){  // �½���Ϣ ���� 
			Imformation a;
			cout<<"������ͼ����Ϣ"<<endl; 
			cout<<"�����¼��"<<endl; 
			cin>>a.dengluhao;
			cout<<"��������"<<endl; 
			cin>>a.shuming; 
			cout<<"����������"<<endl; 
			cin>>a.zuozheming;
			cout<<"��������"<<endl; 
			cin>>a.fenleihao;
			cout<<"����ʱ��"<<endl; 
			cin>>a.shijian;
			cout<<"������浥λ"<<endl; 
			cin>>a.danwei;
			cout<<"����۸�"<<endl; 
			cin>>a.jiage;
			  list1.push_front(a);   //���б�ͷ����Ԫ�أ� 
			  this->wenjianshuchu(list1);//���ñ��淽��������ĵ�ʵ���ļ��� 
			  return  list1;
		}
	list<Imformation>	wenjianshuru(){//���ļ��ж������� 
		list<Imformation> list1;
    ifstream readFile("Test.txt");//�ļ����� 
    while(!readFile.eof()){//�ж��Ƿ���� 
    	Imformation a;
    	readFile>>a.dengluhao>>a.shuming>>a.zuozheming>>a.fenleihao>>a.danwei>>a.shijian>>a.jiage;
    	list1.push_front(a);
	}
    readFile .close();
    return list1;
	}
 	
	 void wenjianshuchu(list<Imformation> list1){//���ļ��б������� 
		ofstream OutFile("Test.txt");
		cout << "mylist contains:";
		for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){//���õ���������ѭ�� 
		Imformation a=*it;
   		 //string aaa="This is a Test12!";
   		 if(it==list1.begin()){//
    		OutFile << a.shuchu();
			}
		else OutFile <<" "+a.shuchu(); //<< OutFile 
		}
	 	OutFile.close();	
		 }
	 
	 
	 void liulanquanbu(list<Imformation> list1){  //������� 
	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){//
		Imformation a=*it;
		cout<<a.shuchu2()<<endl;	
	 	}
	}
	
	
	
	 void chaxun(list<Imformation> list1){//��ѯ�Ӳ˵� 
	 	string temp;
	 	int tuichubianliang=1;
	 		while(tuichubianliang){
 		cout<<"��ѡ���ѯ��ʽ"<<endl;
 		cout<<"0,�˳�"<<endl; 
 		cout<<"1����������ѯ"<<endl;
 		cout<<"2������������ѯ"<<endl;
 		int a;
 		cin>>a;
 		
 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:
            	cout<<"����Ҫ��ѯ����"<<endl; 
            	cin>>temp;
            	shumingchaxun(temp,list1) ; //
              //  System.out.println("null");
                break;
            case 2:
            	cout<<"����Ҫ��ѯ������"<<endl; 
            	cin>>temp;
               zuozhemingchaxun(temp,list1) ;//
                break;
            default:
                cout<<"�������"<<endl;
        }
		  
	 }
	 	
	 
	}
	void shumingchaxun(string sm,list<Imformation> list1){//������ѯ 
	 	bool chadao=false;
	 	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){//
		Imformation a=*it;
		if(a.shuming==sm ) {
				cout<<a.shuchu2()<<endl;	
				chadao=true;
		}
	 	}
		 if(!chadao)cout<<"�޽��"<<endl;	
	 }

	void zuozhemingchaxun(string sm,list<Imformation> list1){//��������ѯ 
	 	bool chadao=false;
	 	for (list<Imformation>::iterator it = list1.begin(); it != list1.end(); ++it){
		Imformation a=*it;
		if(a.zuozheming==sm ) {
				cout<<a.shuchu2()<<endl;	
				chadao=true;
		}
	 	}
		 if(!chadao)cout<<"�޽��"<<endl;	
	 }
	 
	 
	 list<Imformation> shanchu(list<Imformation> list1){
	 	string temp;
	 	int tuichubianliang=1;
	 		while(tuichubianliang){
 		cout<<"��ѡ��ɾ����ʽ"<<endl;
 		cout<<"0,�˳�"<<endl; 
 		cout<<"1������¼��ɾ��"<<endl;
 		cout<<"2������������ɾ��"<<endl;
 		cout<<"3��������������ɾ��"<<endl;
 		cout<<"4�������������ɾ��"<<endl;
 		int a;
 		cin>>a;
 		
 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:
            	cout<<"����Ҫɾ���鼮�ĵ�¼��"<<endl; 
            	cin>>temp;
            	shanchu(temp,list1,a) ; 
              //  System.out.println("null");
                break;
            case 2:
            	cout<<"����Ҫ����ɾ���鼮������"<<endl; 
            	cin>>temp;
               shanchu(temp,list1,a) ; 
                break;
                case 3:
            	cout<<"����Ҫ����ɾ���鼮��������"<<endl; 
            	cin>>temp;
               shanchu(temp,list1,a) ; 
                break;
                case 4:
            	cout<<"����Ҫ����ɾ���ķ����"<<endl; 
            	cin>>temp;
               shanchu(temp,list1,a); 
                break;
            default:
                cout<<"�������"<<endl;
        }
        list1=this->wenjianshuru();
		  
	 }
	 return list1;
}
	 void shanchu(string sm,list<Imformation> list1,int b){//����b��ֵ���в�ͬ��ʽ�ġ�ɾ�� 
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
			cout<<"ɾ���쳣"<<endl;
			return ; 
		}
		if(panduan==sm ) {
	 	it=list1.erase(it);//ɾ������ 
		cout<<a.shuchu()<<endl;
				chadao=true;
				continue;//�����˴�ѭ�� 
		}
		++it;
	 	}
		 if(!chadao)cout<<"�޿�ɾ������"<<endl;
		 this->wenjianshuchu(list1); 
	 }
	 
	 
	 
	 
	 list<Imformation> xiugai(list<Imformation> list1){//�޸Ĳ˵� 
	 	string temp;
	 	int tuichubianliang=1;
	 		while(tuichubianliang){
 		cout<<"��ѡ�����"<<endl;
 		cout<<"0,�˳�"<<endl; 
 		cout<<"1������¼���޸���Ϣ"<<endl;
 		int a;
 		cin>>a;

 		 switch (a) {
 		 	case 0:
              tuichubianliang=0;
                break;
            case 1:{ 
            	cout<<"����Ҫ�޸��鼮�ĵ�¼��"<<endl; 
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
		 if(!chadao)cout<<"�޿��޸�Ԫ��"<<endl;
                break; 
                } 
            default:
                cout<<"�������"<<endl;
        }
        list1=this->wenjianshuru();
		  
	 }
	 return list1;
}
	 
	 
 	 
		 
void	denglu() {
	Guanliyuan c1; 
	bool xunhuan=true;
	while(xunhuan){
		cout<<"�������˺�"<<endl;
		cin>>c1.zhanghao;
		cout<<"����������"<<endl;
		cin>> c1.mima;
		if(c1.zhanghao=="123"&&c1.mima=="123"){
			xunhuan=false;
		cout<<"��ӭ����Ա��¼"<<endl;	
		}else  cout<<"�˺Ż��������"<<endl;
	}
		
	}
	
	
	
	
	
	
	
	 
 };
 int main()
 {
 	fangfa fangf;//������ ���ò������� 
 	int tuichubianliang=1;
 	list<Imformation> my_list;//�б�������ʱ�洢������Ϣ 
 	my_list = fangf.wenjianshuru();
 	fangf.denglu();
 	
 	while(tuichubianliang){
 		cout<<"��ѡ�����"<<endl;
 		cout<<"0,�˳�"<<endl; 
 		cout<<"1�����"<<endl;
 		cout<<"2��¼��"<<endl;
 		cout<<"3����ѯ"<<endl;
 		cout<<"4��ɾ��"<<endl;
 		cout<<"5���޸�"<<endl;
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
                cout<<"�������"<<endl;
        }
		  
	 }
 	
   

 }
