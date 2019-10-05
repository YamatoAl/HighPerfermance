//ACS105111

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<vector>
using namespace std;

bool Fix(int last_size,int now_prompt,vector<int> prompts,int product[]);
bool Fix1(int last_size,int now_prompt,vector<int> prompts,int product[]);
bool Fix0(int last_size,int now_prompt,vector<int> prompts,int product[]);

int  main(){
	
	vector<int> x_input[25];
	vector<int> y_input[25];
	string input,in_num;
	
	fstream file;
	char buffer[200];
	file.open("test1.txt",ios::in);
	if(!file){
		cout<<"File Error\n";
	}
	else{
		for(;!file.eof();){
			
			for(int i=0;i<25;i++){
				x_input[i].clear();
				y_input[i].clear();
			}
			
			for(int i=-1;i<50;i++){
				file.getline(buffer,sizeof(buffer));
				
				if(i==-1)continue;
//				cout<<input<<endl;
				
				istringstream delim(buffer);
				
				for(;delim>>in_num;){
					
					if(i<25)x_input[i].push_back(stoi(in_num));
					else y_input[i-25].push_back(stoi(in_num));
					
//					cout<<stoi(in_num)<<endl;
				}
			}
			
//			for(int i=0;i<25;i++){
//				cout<<y_input[i][3]<<endl;
//			}

			int product[25];
			for(int i=0;i<25;i++){
				product[i]=-1;
			}
//			cout<<x_input[0].size()<<endl;
			Fix(25,x_input[0].size(),x_input[0],product);
		} 
		file.close();
	}
	
}

bool Fix(int last_size,int now_prompt,vector<int> prompts,int product[]){
	bool a,b;
	
	if(last_size<0)return false;
	
//	cout<<"Fix("<<last_size<<","<<now_prompt<<")"<<endl;
	
	int new_product[25];
	for(int i=0;i<25;i++){
		new_product[i]=product[i];
	}
	
	a=Fix1(last_size,now_prompt,prompts,new_product);
	b=Fix0(last_size,now_prompt,prompts,new_product);

	return (a||b);
}

bool Fix1(int last_size,int now_prompt,vector<int> prompts,int product[]){
	
	if(last_size<=0)return false;
	
	int use_prompt=prompts[now_prompt-1];
	
	for(int i=last_size-1;;i--){
//		if(product[i]==0)return false;
		product[i]=1;
		use_prompt--;
		if(use_prompt==0)break;
		else if(i==0)return false;
	}
	if(now_prompt==1){
		for(int i=last_size-prompts[now_prompt-1]-1;i>=0;i--){
			product[i]=0;
		}
		for(int i=0;i<25;i++){
			cout<<product[i]<<" ";
		}
		cout<<endl;
		return true;
	}
	now_prompt--;
	last_size-=prompts[now_prompt]+1;
	product[last_size]=0;
	
	Fix(last_size,now_prompt,prompts,product);
}

bool Fix0(int last_size,int now_prompt,vector<int> prompts,int product[]){
	if(last_size==1)return false;
	
	last_size--;
	product[last_size]=0;
	
	Fix(last_size,now_prompt,prompts,product);
}
	