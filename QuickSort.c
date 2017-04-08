//count the comparision times of quick sort
//3 choices of pivot:
//fist element in the sub-array
//median-of-three
//last element in the sub-array

#include <stdio.h>
#include <stdlib.h>

unsigned long long int getCmpTimes(int* array, unsigned long long int length, int choiceofpivot){
	unsigned long long count=0;
	if(length==1){
		return 0;
	}
	count+=length-1;

	int leftid=0;
	int rightid=length-1;
	int pid=partition(array, leftid, rightid, choiceofpivot);//put pivot in the right position in the new partitioned array

	if(pid>0){
		count+=getCmpTimes(array, pid, choiceofpivot );
	}
	if(length-pid-1>0){
		count+=getCmpTimes(array+pid+1, length-pid-1, choiceofpivot);
	}
	return count;
}

int partition(int* array, int leftid, int rightid, int choiceofpivot){

	//if choose the left most as the pivot
	//nothing added


	//if choose the median as the pivot
	if(choiceofpivot==2){

		int middleid=rightid/2;
		if(((array[leftid]<array[rightid])&&(array[leftid]>array[middleid]))||((array[leftid]>array[rightid])&&(array[leftid]<array[middleid]))){
			//same as left most
		}
		else if(((array[middleid]<array[leftid])&&(array[middleid]>array[rightid]))||((array[middleid]>array[leftid])&&(array[middleid]<array[rightid]))){
			int tempp=array[middleid];
			array[middleid]=array[leftid];
			array[leftid]=tempp;
		}
		else{	
			int tempp=array[rightid];
			array[rightid]=array[leftid];
			array[leftid]=tempp;
		}

		}

	//if choose the right most as the pivot
	if(choiceofpivot==3){
		int tempp=array[rightid];
		array[rightid]=array[leftid];
		array[leftid]=tempp;
	}

//-----------------------------------------------------------------------
	int temp;
	int p=array[leftid];
	int i=leftid+1;
	int j=leftid+1;


	while(j<=rightid){
		if(array[j]<p){
			temp=array[i];
			array[i++]=array[j];
			array[j]=temp;	
		}
		j++;	
	}

	temp=array[leftid];
	array[leftid]=array[i-1];
	array[i-1]=temp;

	return i-1;

}

int main(){
	FILE *myFile;
    	myFile = fopen("QuickSort.txt", "r");
	int A[10000];

    	int i;
	for (i=0; i<10000;i++){
        	fscanf(myFile, "%d", &A[i]);
    	}

//	unsigned long long int count=getCmpTimes(A, 10000, 1);
//	printf("if choose the left most as the pivot: count=%llu\n",count);
//	unsigned long long int count=getCmpTimes(A, 10000, 2);
//	printf("if choose the median-of-three as the pivot: count=%llu\n",count);
	unsigned long long int count=getCmpTimes(A, 10000, 3);
	printf("if choose the right most as the pivot: count=%llu\n",count);
	return 0;
}

