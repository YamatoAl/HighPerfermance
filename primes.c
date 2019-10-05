#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>

bool num[100000000];
bool use_num[100000000];

int main(int argc,char *argv[]){
//	bool num[2000000];
//	bool num[100000];
//	bool use_num[100000];

	int i,j,n;
//  scanf("%d",&n);
	n=88888888;
	
	MPI_Init(&argc,&argv);

	int world_rank,world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);		
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		
    double use_time=-MPI_Wtime();
		
    for(i=2;i<=n;i++){
        num[i]=1;
		use_num[i]=1;
    }
	
	int prime=2;
	int use_prime;
	
    for(int i=2+world_rank;;i+=world_size){
        if(i>n){
            i=n;
        }
        if(use_num[i]==0){
                continue;
        }
		else{
            use_prime=i;
            MPI_Reduce(&use_prime,&prime,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
            MPI_Bcast(&prime,1,MPI_INT,0,MPI_COMM_WORLD);
            if(prime*prime>n){
                break;
            }
            if(prime!=use_prime){
                i-=world_size;
            }
			for(int j=prime*prime;j<n;j+=prime){
                use_num[j]=0;
            }
        }

    }

    use_time+=MPI_Wtime();

    int global_count=0;
    int count=0;
    for(int i =2+world_rank;i<n;i+=world_size){
		if(use_num[i]==1){
			count++;
		}
	}
    printf("number cpu:%d  %d\n",world_rank,count);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&count,&global_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(world_rank==0){
        printf("%d\n%lfs\n",global_count,use_time);
    }
    MPI_Finalize();

}
