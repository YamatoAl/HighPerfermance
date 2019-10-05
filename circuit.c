#include <mpi.h>
#include <stdio.h>
#define EXTRACT_BIT(n, i) ( ( n & ( 1 << i ) ) ? 1 : 0 )

int main(int argc, char *argv[]){
	int i;
	int id;
	int p;
	int global_solutions;
	int solutions;
	double time;
	double percent;
	int check_circuit(int, int);
	
	MPI_Init(&argc,&argv);
	MPI_Barrier(MPI_COMM_WORLD);
	time=-MPI_Wtime();
	percent=-MPI_Wtick();
	int world_rank,world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);		
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	for (i = 0; i < 65535; i++)
	{
		solutions += check_circuit(id, i);
	}
	
	MPI_Reduce(&solutions,&global_solutions,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	time+=MPI_Wtime();
	printf("Time %f\n",time);
	percent+=MPI_Wtick();
	printf("Precision %f\n");
	
	fflush(stdout);
	MPI_Finalize();
	
	return 0;
}

int check_circuit(int id, int z){
	int v[16];
	int i;
	
	for (i = 0; i < 16; i ++)
		v[i] = EXTRACT_BIT(z, i);
	
	if 
	( 
	(v[0] || v[1]) && ( !v[1] || !v[3] ) && ( v[2] || v[3] ) &&
	(!v[3] || !v[4]) && (v[4] || !v[5]) &&
	(v[5] || !v[6] ) && (v[5] || v[6]) &&
	(v[6] || !v[15]) && (v[7] || !v[8]) &&
	(!v[7] || !v[13]) && (v[8] || v[9]) &&
	(v[8] || !v[9]) && (!v[9] || !v[10]) &&
	(v[9] || v[11]) && (v[10] || v[11]) &&
	(v[12] || v[13]) && (v[13] || !v[14]) &&
	(v[14] || v[15])
	)
	{
		printf("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", id,
		v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8],
		v[9], v[10], v[11], v[12], v[13], v[14], v[15]
		);
		fflush(stdout);
		return 1;
	}
//	fflush(stdout);
	return 0;
}