#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200
int** read2dArray(FILE* p);
int countCrossing(int** table, int nedges, int degree[]);
void mergesort(int* array, int n);
int partition(int* array, int leftid, int rightid);
void printTable(int** table);

void mergesort(int* array, int length){
	if(length==1){
		return;
	}

	int pid=partition(array,0,length-1);
	if(pid>0){
		mergesort(array, pid);
	}
	if(length-pid-1>0){
		mergesort(array+pid+1, length-pid-1);
	}
}

int partition(int* array, int leftid, int rightid){
	//if choose the left most one as the pivot
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

int countCrossing(int** table, int nedges, int degree[]){
    int count=0, random, v1, v2;
    int nvertices=0;
    int n;
    for(n=0;n<N;n++){
	if(table[n][0]!=0){
		nvertices++;
	}
    }
//	printf("n vertices=%d\n",nvertices);

	clock_t t=clock();
	srand((unsigned) t);

    while(nvertices>2){
	//randomly pick one edge
	random=rand() % (2*nedges);
//	printf("\n\nrandom=%d\n",random);

	//find the corresponding edge table[i][j]
	int k=0, i=0, j=1;
	if(random==0){
		i=0;
		while(table[i][0]==0){
			i++;
		}
		j=1;

	}
	else{
		while((i<N)&&(k<random)){
			if(table[i][0]==0){
				i++;
				j=1;
			}
			else if(table[i][j]==0){
				i++;
				j=1;
			}
			else if(j<(1+N*(N-1)/2)){
				j++;
				k++;
			}
			else{
				j=1;
				i++;
				k++;
			}
		}

		if(i>=N){
			i--;
			if(table[i][0]==0){
				printf("error, not enough edges to find the random one\n");
				exit(-1);
			}
		}

		if(table[i][j]==0){
			i++;
			while((i<N-1)&&(table[i][0]==0)){
				i++;
			}
			j=1;
			while(table[i][j]==0){
				j++;
			}
		}
	}
	//now k==random, delete 1 edge (2 vertices)

	nedges--;
	v2=table[i][j];
	v1=table[i][0];

	if((v1==0)||(v2==0)){
		printf("error, edge 0 is chosen: v1=%d,v2=%d\n",v1,v2);
		exit(-1);
	}

	//delete that edge (v1,v2) (table[i][j])
	int end=degree[i];
	table[i][j]=table[i][end];
	table[i][end]=0;
	degree[i]--;

	//delete the same edge (v2,v1)
	for(i=0;i<N;i++){
		if(table[i][0]==v2){
			for(j=1;j<(1+N*(N-1)/2);j++){
				if(table[i][j]==v1){
					end=degree[i];
					table[i][j]=table[i][end];
					table[i][end]=0;
					degree[i]--;
					break;
				}
			}
		}
	}
//	printf("deleted 1 edge: (%d,%d) or (%d,%d)\n",v1,v2,v2,v1);
//	printTable(table);///////////////////////////////
//	printf("now nedges=%d\nbefore v2->v1 & delete self-loop\n",nedges);

	int temp=0;
	//change v2 to v1  and delete self-loop
	for(i=0;i<N;i++){
	    	if(table[i][0]==0){
			continue;
	    	}
		if((table[i][0]!=v2)&&(table[i][0]!=v1)){
			for(j=1;j<(1+N*(N-1)/2);j++){
				if(table[i][j]==v2){
					table[i][j]=v1;
				}
			}
		}
		else{//int the line of vertice v1 or v2:
			end=degree[i];
			while(((table[i][end]==v1)||(table[i][end]==v2))&&(end!=0)){
				table[i][end]=0;
				temp++;
				degree[i]--;
				end--;
			}
			if(end==0){
				table[i][0]=0;
				continue;
			}
			for(j=1;j<(1+N*(N-1)/2);j++){
				if((table[i][j]==v2)||(table[i][j]==v1)){
					if(j<end){
						table[i][j]=table[i][end];
						table[i][end]=0;
						degree[i]--;
						temp++;
						end--;
						while(((table[i][end]==v1)||(table[i][end]==v2))&&(end!=0)){
							table[i][end]=0;
							temp++;
							degree[i]--;
							end--;
						}
					}
				}
			}
			
		}

		mergesort(&table[i][1],degree[i]);
	}
	nedges-=temp/2;
//	printf("nedges-=temp/2: %d\n",nedges);////////////////////////////////////
//	printf("change v2 to v1,and deleted self-loop:\n");
//	printTable(table);///////////////////////////////
//	printf("delet %d edges, now nedges=%d\n",temp/2, nedges);

	//merge the line of v2 into v1
	if(degree[v1-1]==0){
		if(degree[v2-1]==0){
			printf("error\n");
			exit(-1);
		}
		else{
			//copy the whole v2 line to v1
			table[v1-1][0]=v1;
			for(j=1;j<(1+N*(N-1)/2);j++){
				table[v1-1][j]=table[v2-1][j];
				degree[v1-1]=degree[v2-1];
			}
			table[v2-1][0]=0;
			degree[v2-1]=0;
		}
	}
	else{
		if(degree[v2-1]==0){
			//v1 unchanged
		}
		else{
			int i1=v1-1, i2=v2-1, j1=1, j2=1;
			int* newv1row=malloc(sizeof(int)*(1+N*(N-1)/2));
			if(i1==N){i1--;}
			*newv1row=table[i1][0];
			k=1;

			while((j1<=degree[i1])&&(j2<=degree[i2])){
				if(table[i1][j1]<table[i2][j2]){
					*(newv1row+k)=table[i1][j1++];
					k++;
				}
				else{
					*(newv1row+k)=table[i2][j2++];
					k++;
				}
			}
			while(j1<=degree[i1]){
				*(newv1row+k)=table[i1][j1++];
				k++;
			}


			while(j2<=degree[i2]){
				*(newv1row+k)=table[i2][j2++];
				k++;
			}

			degree[i1]+=degree[i2];
			while(k<=(N*(N-1)/2)){
				*(newv1row+k)=0;
				k++;
			}

			for(k=0;k<(1+N*(N-1)/2);k++){
				table[i1][k]=*(newv1row+k);
			}
			free(newv1row);
			if(i2==N){i2--;}
			table[i2][0]=0;
			degree[i2]=0;
		}

	}

//	printf("aftere merge:\n");//////////////////
//	printTable(table);///////////////////////////////
//	printf("nedges:%d\n",nedges);////////////////////////

	nvertices=0;
	for(n=0;n<N;n++){
		if(table[n][0]!=0){
			nvertices++;
		}
        }

	//update the number of edges
	int tempdegree=0,temptotal=0;
	for(i=0;i<N;i++){
		if(table[i][0]!=0){
			for(j=1;j<(1+N*(N-1)/2);j++){
				if(table[i][j]!=0){
					tempdegree++;
				}
			}
			temptotal+=tempdegree;
			tempdegree=0;
		}
	}

	if(nedges!=temptotal/2){
		printf("error: nedges!=temptotal/2\n");
//		exit(-1);
	}
	nedges=temptotal/2;


    }




//    printf("finally:\n");
//    printTable(table);
    int i;
    for(i=0;i<N;i++){
	if(table[i][0]!=0){
		count+=degree[i];
	}
    }
    count/=2;
    return count;
}

int** read2dArray(FILE* p){//read value of vertices from file, set 0 if not exist(if deleted later, also set 0 later)
//	int table[N][N];
	int** table=malloc(sizeof(int*)*N);
	int i=0,j=0;
	for(i=0;i<N;i++){
		table[i]=malloc(sizeof(int)*(1+N*(N-1)/2));
	}
	i=0;
	char c;
	char vid[4];//assume maximum number of digit for each element is 3
	int vlen=0;

	while(i<N){
		c=getc(p);
		if((c!='\t')&&(c!='\n')){
			vid[vlen]=c;
			vlen++;
		}
		else {//=='\t' or '\n'
			vid[vlen]='\0';
			table[i][j]=atoi(vid);
			j++;
			vlen=0;

			if(c=='\n'){
				while(j<(1+N*(N-1)/2)){
					table[i][j]=0;
					j++;
				}
			i++;
			j=0;
			}
		}
		
	}	
	return table;
}

void printTable(int** table){
	int i, j;
	for(i=0;i<N;i++){
	    if(table[i][0]!=0){
		printf("%d: ",table[i][0]);
		for(j=1;j<(1+N*(N-1)/2);j++){
			if(table[i][j]!=0){
				printf("%d, ",table[i][j]);
			}
		}
		printf("\n");
	    }
	}
}


int main(){
	FILE* p=fopen("kargerMinCut.txt", "r");
//	FILE* p=fopen("testcase1.txt", "r");////////////////////////////////////
	if(p==NULL){
		printf("No such file.\n");
		return 1;
	}

	int nedges=0;
	int** table=read2dArray(p);

	int i,j;
	int degree[N];

	for(i=0;i<N;i++){
		degree[i]=0;
		for(j=0;j<(1+N*(N-1)/2);j++){
			if((j!=0)&&(table[i][j]!=0)){
				degree[i]++;
			}
		}
		nedges+=degree[i];
//		printf("degree[%d]=%d\n",i,degree[i]);

	}
	nedges/=2;

	//sort all rows(started from the second column)
	for(i=0;i<N;i++){
		mergesort(&table[i][1], degree[i]);
	}

	int count=countCrossing(table, nedges, degree);
//	printf("count=%d\n", count);
	printf("%d\n",count);



	for(i=0;i<N;i++){
		free(table[i]);
	}
	free(table);
	fclose(p);

	return 0;

}


