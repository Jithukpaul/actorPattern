#include<iostream>
#include<future>
#include<vector>
#include<chrono>
#include<unistd.h>
#include<queue>
#include<string>

using namespace std;	

class actor
{
string res;
public:
	queue<int> mailbox1;queue<int> mailbox2;
	queue<string> result;
	int s=0;
	string fact(int a)
	{
		int fa=1;
		for(int i=2;i<=a;i++){
			fa*=i;
		}
		string b="fact("+to_string(a)+")=" +to_string(fa)+"\n";
		return b;
	}
	string sum(int a)// for showing the behaviour (i.e:it can set designate what to do with the next message )
	{
		sleep(3);
		s+=a;
		string b="sum(prev+"+to_string(a)+")=" +to_string(s)+"\n";
		return b;
	}
	void thr(actor* r)//thread for the factr
	{
		cout<<"thread created for fact:\n";
		do{
			sleep(3);
			if(r->mailbox1.size()>0){	
			auto f= bind(&actor::fact,r,r->mailbox1.front());							
			future<string> result_future= async(launch::async,f);
			cout<<"ans:"<<result_future.get();
			r->mailbox1.pop();
			}
		}while(true);
	}
	//----------------------------------
	void thr1(actor* r1){//thread to find the sum
		cout<<"thread created for sum:\n";
		do{
			sleep(3);
			if(r1->mailbox2.size()>0){	
			auto f= bind(&actor::sum,r1,r1->mailbox2.front());							
			future<string> result_future1= async(launch::async,f);
			cout<<"ans:"<<result_future1.get();
			r1->mailbox2.pop();
			}
		}while(true);
	}
};
int main()//Main thread spawns two new thread 
{
	actor r,r1;
	int choice, temp;
	cout<<"Enter the option:- 0:fact, 1:sum\n";
	thread thread_obj(bind(&actor::thr,r,&r));
	thread thread_obj1(bind(&actor::thr1,r1,&r1));
	while(true)
	{		
		cin>>choice;
		cin>>temp;
		if(!choice)
			r.mailbox1.push(temp);
		else
			r1.mailbox2.push(temp);
		for(;r.result.size()!=0;)
		{
			cout<<r.result.front();
			r.result.pop();
		}
	} 
	return 0;
}
