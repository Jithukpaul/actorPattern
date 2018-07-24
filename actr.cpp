#include<iostream>
#include<future>
#include<vector>
#include<chrono>
#include<unistd.h>
#include<queue>
#include<string>
#include<cstdlib>

using namespace std;	
class actor1
{
	string res;int s=0;
public:
	queue<int> mailbox2;
	string sum(int a)// for showing the behaviour (i.e:it can set designate what to do with the next message )
	{
		sleep(3);
		s+=a;
		string b="sum(prev+"+to_string(a)+")=" +to_string(s)+"\n";
		return b;
	}
	void thr1(actor1* r){//thread to find the sum
		cout<<"thread created for sum:\n";
		do{
			sleep(3);
			if(r->mailbox2.size()>0){	
			auto f= bind(&actor1::sum,r,r->mailbox2.front());							
			future<string> result_future1= async(launch::async,f);
			cout<<"ans:"<<result_future1.get();
			r->mailbox2.pop();
			}
		}while(true);
	}

};
queue<string> result;
class actor
{
string res;
public:
	queue<int> mailbox1;
	string fact(int a)
	{
		int fa=1;
		for(int i=2;i<=a;i++){
			fa*=i;
		}
		string b="fact("+to_string(a)+")=" +to_string(fa)+"\n";
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
};
int main()//Main thread spawns two new thread 
{
	actor r;actor1 r1;
	int choice, temp;
	cout<<"Enter the option:- 0:fact, 1:sum, othervalue:exit\n";
	thread thread_obj(bind(&actor::thr,r,&r));
	thread thread_obj1(bind(&actor1::thr1,r1,&r1));
	while(true)
	{		
		cin>>choice;
		if(choice==0){
			cin>>temp;
			r.mailbox1.push(temp);
		}
		else if(choice==1){
			cin>>temp;
			r1.mailbox2.push(temp);
		}
		else{
			if(r.mailbox1.size()==0 && r1.mailbox2.size()==0 && result.size()==0)
				exit(0);
		}
		for(;result.size()!=0;)
		{
			cout<<result.front();
			result.pop();
		}
	} 
	return 0;
}
