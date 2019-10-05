#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc,char *argv[]){

       int rank,nproc;

        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&nproc);

        int n=88888888;

        int* judge = (int *) malloc (n*4);
        int* reJudge = (int *) malloc (n*4);


        memset(judge,0,(n+1)*4);
        memset(reJudge,0,(n+1)*4);

        double  start = -MPI_Wtime();
        int localPrime;
        int prime=2;

        for(int i =2+rank;;i+=nproc){
            if(i>n){
                i=n;
            }
            if(judge[i]==1){
                     continue;
            }else{
                  localPrime =i;
                  MPI_Reduce(&localPrime,&prime,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
                  MPI_Bcast(&prime,1,MPI_INT,0,MPI_COMM_WORLD);
                  if(prime*prime>n){
                       break;
                  }
                  if(prime!=localPrime){
                        i-=nproc;
                  }

                  for(int j =prime*prime;j<n;j+=prime){
                       judge[j]=1;


                  }
            }

        }

        start += MPI_Wtime();
        int global_count=0;
        int count=0;
        for(int i =2+rank;i<n;i+=nproc){
              if(judge[i]==0){
                   count++;
              }
        }
        printf("number cpu:%d  %d\n",rank,count);
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Reduce(&count,&global_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
        if(rank==0){


         printf("%d %lf\n",global_count,start);
        }
        MPI_Finalize();

}
