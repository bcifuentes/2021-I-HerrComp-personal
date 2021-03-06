#include <iostream>
#include "mpi.h"


int main(int argn, char ** argv){
  MPI_Init(&argn,&argv);
  const int NPINGPONG =std::atoi(argv[1]);
  int pid;
  int np;
  
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int counter=0;
  for(int ii=0; ii<NPINGPONG;++ii){
    
    if (pid==0){
      MPI_Send(& counter,1,MPI_INT,1,0,MPI_COMM_WORLD);
      MPI_Recv(& counter, 1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    
    else {
      MPI_Recv(& counter, 1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      counter+=1;
      MPI_Send(& counter,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
  }

  
  if (pid==0){
    std::cout<<counter<<std::endl;
  }
  
  MPI_Finalize();
  return 0;
}
