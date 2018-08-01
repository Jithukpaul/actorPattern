#include<iostream>
#include<future>
#include<vector>
#include<chrono>
#include<unistd.h>
#include<queue>
#include<string>
#include<cstdlib>

using namespace std;	
	queue<string> res;
	int s=0;string cres,cres1;

	queue<int> mailbox2;
	string sum(int a)// for showing the behaviour (i.e:it can set designate what to do with the next message )
	{
		sleep(3);
		s+=a;
		string b="sum(prev+"+to_string(a)+")=" +to_string(s)+"\n";
		return b;
	}
	void thr1(){//thread to find the sum
		cout<<"thread created for sum:\n";
		do{
			sleep(3);
			if(mailbox2.size()>0){	
			//auto f= bind(&actor1::sum,r,r->mailbox2.front());							
			future<string> result_future1= async(launch::async,sum,mailbox2.front());
			//cout<<"ans:"<<result_future1.get();
			cres=result_future1.get();
			res.push(cres);
			mailbox2.pop();
			}
		}while(true);
	}

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
	void thr()//thread for the factr
	{
		cout<<"thread created for fact:\n";
		do{
			sleep(3);
			if(mailbox1.size()>0){	
			//auto f= bind(&actor::fact,r,r->mailbox1.front());							
			future<string> result_future= async(launch::async,fact,mailbox1.front());
			//cout<<"ans:"<<result_future.get();
			cres1=result_future.get();
			res.push(cres1);
			mailbox1.pop();
			}
		}while(true);
	}
void completion_dispatcher(){
	while(true){
		for(;res.size()!=0;){
			cout<<res.front();
			res.pop();
		}
	}
}
int main()//Main thread spawns two new thread 
{
	int choice, temp;
	cout<<"Enter the option:- 0:fact, 1:sum, othervalue:exit\n";
	thread thread_obj(thr);
	thread thread_obj1(thr1);
	thread compl_dtchr(completion_dispatcher);
	while(true)
	{		
		cin>>choice;
		if(choice==0){
			cin>>temp;
			mailbox1.push(temp);
		}
		else if(choice==1){
			cin>>temp;
			mailbox2.push(temp);
		}
		else{
			if(mailbox1.size()==0 && mailbox2.size()==0 )
				exit(0);
		}		
	} 
	return 0;
}

