#include<iostream>
#include<vector>
#include<ctime>

using namespace std;

void printC(vector<vector<int>> c){
	for(int i=0;i<c.size();i++){
		for(int j=0;j<c.size();j++){
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(){
	
	vector<vector<int>> A,B,C;
	vector<int> column1,column0;
	int matrixSize,blockNumber;
	double start,end;
	int f;
	
	cin>>matrixSize>>blockNumber;
	
	for(int i=0;i<matrixSize;i++){
		column1.push_back(1);
		column0.push_back(0);
	}
	for(int i=0;i<matrixSize;i++){
		A.push_back(column1);
		B.push_back(column1);
		C.push_back(column0);
	}
	
	cout<<"1.Loop-i-j-k"<<endl;
	start=clock();
	for(int i=0;i<matrixSize;i++){
		for(int j=0;j<matrixSize;j++){
			f=0;
			for(int k=0;k<matrixSize;k++){
				f+=A[i][k]*B[k][j];
			}
			C[i][j]=f;
		}
	}
	end=clock();
	cout<<"  "<<(end-start)/CLOCKS_PER_SEC<<" (s)"<<endl;
	
//	printC(C);
	
	C.clear();
	for(int i=0;i<matrixSize;i++){
		C.push_back(column0);
	}
	
	cout<<"2.Loop-reordering"<<endl;
	start=clock();
	for(int i=0;i<matrixSize;i++){
		for(int k=0;k<matrixSize;k++){
			f=A[i][k];
			for(int j=0;j<matrixSize;j++){
				C[i][j]+=f*B[k][j];
			}
		}
	}
	end=clock();
	cout<<"  "<<(end-start)/CLOCKS_PER_SEC<<" (s)"<<endl;
	
//	printC(C);
	
	C.clear();
	for(int i=0;i<matrixSize;i++){
		C.push_back(column0);
	}
	
	cout<<"3.Matrix-column"<<endl;
	start=clock();
	for(int i=0;i<matrixSize;i++){
		vector<int> BColumn;
		for(int j=0;j<matrixSize;j++)BColumn.push_back(B[j][i]);
		
		for(int j=0;j<matrixSize;j++){
			f=0;
			for(int k=0;k<matrixSize;k++){
				f+=A[j][k]*BColumn[k];
			}
			C[j][i]=f;
		}
	}
	end=clock();
	cout<<"  "<<(end-start)/CLOCKS_PER_SEC<<" (s)"<<endl;
	
//	printC(C);
	
	C.clear();
	for(int i=0;i<matrixSize;i++){
		C.push_back(column0);
	}
	
	cout<<"4.Block algorithm without copy"<<endl;
	if(matrixSize%blockNumber==0){
		start=clock();
		int blockSize=matrixSize/blockNumber;
		for(int ABlockColumn=0;ABlockColumn<blockNumber;ABlockColumn++){
			for(int ABlockRow=0;ABlockRow<blockNumber;ABlockRow++){
				vector<vector<int>> ABlock;
				for(int i=ABlockColumn*blockSize;i<(ABlockColumn+1)*blockSize;i++){
					vector<int> newColumn;
					for(int j=ABlockRow*blockSize;j<(ABlockRow+1)*blockSize;j++){
						newColumn.push_back(A[i][j]);
					}
					ABlock.push_back(newColumn);
				}
				
				for(int BBlockColumn=0;BBlockColumn<blockNumber;BBlockColumn++){
					vector<vector<int>> BBlock;
					for(int i=BBlockColumn*blockSize;i<(BBlockColumn+1)*blockSize;i++){
						vector<int> newColumn;
						for(int j=BBlockColumn*blockSize;j<(BBlockColumn+1)*blockSize;j++){
							newColumn.push_back(B[i][j]);
						}
						BBlock.push_back(newColumn);
					}
						
					for(int i=0;i<blockSize;i++){
						for(int j=0;j<blockSize;j++){
							f=0;
							for(int k=0;k<blockSize;k++){
								f+=ABlock[i][k]*BBlock[k][j];
							}
							C[ABlockColumn*blockSize+i][BBlockColumn*blockSize+j]+=f;
						}
					}
				}
			}
		}
		end=clock();
		cout<<"  "<<(end-start)/CLOCKS_PER_SEC<<" (s)"<<endl;
	}
	else cout<<"  Split failed"<<endl;
		
//		printC(C);

	C.clear();
	for(int i=0;i<matrixSize;i++){
		C.push_back(column0);
	}
	
	cout<<"4.Block algorithm without copy(ver1)"<<endl;
	if(matrixSize%blockNumber==0){
		start=clock();
		int blockSize=matrixSize/blockNumber;
		for(int ABlockColumn=0;ABlockColumn<blockNumber;ABlockColumn++){
			for(int ABlockRow=0;ABlockRow<blockNumber;ABlockRow++){
				
				for(int BBlockColumn=0;BBlockColumn<blockNumber;BBlockColumn++){
						
					for(int i=ABlockColumn*blockSize;i<(ABlockColumn+1)*blockSize;i++){
						for(int k=BBlockColumn*blockSize;k<(BBlockColumn+1)*blockSize;k++){
							f=0;
							for(int j=ABlockRow*blockSize;j<(ABlockRow+1)*blockSize;j++){
								f+=A[i][j]*B[j][k];
							}
							C[i][k]+=f;
						}
					}
				}
			}
		}
		end=clock();
		cout<<"  "<<(end-start)/CLOCKS_PER_SEC<<" (s)"<<endl;
		
//		printC(C);
	}
	else cout<<"  Split failed"<<endl;
	
	C.clear();
	for(int i=0;i<matrixSize;i++){
		C.push_back(column0);
	}
	
	cout<<"4.Block algorithm without copy(ver2)"<<endl;
	if(matrixSize%blockNumber==0){
		start=clock();
		int blockSize=matrixSize/blockNumber;
		for(int ABlockColumn=0;ABlockColumn<blockNumber;ABlockColumn++){
			for(int ABlockRow=0;ABlockRow<blockNumber;ABlockRow++){
				
				for(int BBlockColumn=0;BBlockColumn<blockNumber;BBlockColumn++){
						
					for(int i=ABlockColumn*blockSize;i<(ABlockColumn+1)*blockSize;i++){
						for(int k=BBlockColumn*blockSize;k<(BBlockColumn+1)*blockSize;k++){
							f=A[i][k];
							for(int j=ABlockRow*blockSize;j<(ABlockRow+1)*blockSize;j++){
								C[i][j]+=f*B[k][j];
							}
						}
					}
				}
			}
		}
		end=clock();
		cout<<"  "<<(end-start)/CLOCKS_PER_SEC<<" (s)"<<endl;
		
//		printC(C);
	}
	else cout<<"  Split failed"<<endl;
}