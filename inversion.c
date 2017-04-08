#include <stdio.h>
#include <stdlib.h>

unsigned long long int sort_and_count(int *A, int sizeA);
unsigned long long int merge_and_count_split_inv(int *B, int *C, int sizeD);

int main(){
	FILE *myFile;
    	myFile = fopen("Array.txt", "r");
	int A[100000];

    	int i;
	for (i = 0; i < 100000; i++){
        	fscanf(myFile, "%d", &A[i]);
    	}

	unsigned long long int n_inv=sort_and_count(A,100000);	
	printf("number of inversion=%llu\n",n_inv);

	return 0;
}


unsigned long long int sort_and_count(int *A, int sizeA){
	if(sizeA==1){
		return 0;	
	}
	unsigned long long int x=0,y=0,z=0;
	int sizeB=sizeA-sizeA/2;
	int sizeC=sizeA/2;
	x=sort_and_count(A,sizeB);
	y=sort_and_count(A+sizeB,sizeC);
	z=merge_and_count_split_inv(A,A+sizeB,sizeA);

	return x+y+z;

	
}


unsigned long long int merge_and_count_split_inv(int *B, int *C, int sizeD){//size:length of B plus length of C
	unsigned long long int z=0;
	int iD=0;
	int iB=0;
	int iC=0;
	int sizeB=sizeD-sizeD/2;
	int sizeC=sizeD/2;
	int *D=malloc(sizeof(int)*sizeD);
	while((iB<sizeB)&&(iC<sizeC)){
		if(*(C+iC)<*(B+iB)){
			*(D+iD)=*(C+iC);
			z+=sizeB-iB;
			iC++;
			iD++;
		}
		else{
			*(D+iD)=*(B+iB);
			iB++;
			iD++;
		}
	}
	while(iB<sizeB){
		*(D+iD)=*(B+iB);
		iB++;
		iD++;
	}
	while(iC<sizeC){
		*(D+iD)=*(C+iC);
		iC++;
		iD++;
	}

	int j;
	for(j=0;j<sizeD;j++){
		B[j]=D[j];	
	}
	free(D);
	
	return z;


}

