//haven't been refined yet
//still have memory leak problem
//not free for some allocated memory

//karatsuba 
//can get the multiplication of two very "larger" numbers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MIN(X,Y) (((X)<(Y))?(X):(Y))
#define MAX(X,Y) (((X)>(Y))?(X):(Y))

char* karatsuba(char* , char* );
char* stringSum(char* , char* );
char* stringSubtract(char* , char* );
char* stringProd(char*, char* );

int main(){
	char* x="3141592653589793238462643383279502884197169399375105820974944592";
	char* y="2718281828459045235360287471352662497757247093699959574966967627";

//	char* x="31";
//	char* y="11";


	char* xy=malloc(sizeof(char)*(strlen(x)+strlen(y)+2));
	strcpy(xy,karatsuba(x,y));
	printf("x*y:\n%s\n",xy);
		

	free(xy);

	return 0;
}


char* karatsuba(char* x, char* y){
	int lengthx=strlen(x);
	int lengthy=strlen(y);
	char* l=((lengthx>=lengthy)?x:y);
	char* s=((lengthy<=lengthx)?y:x);
	int ns=MIN(lengthx,lengthy);
	int nl=MAX(lengthx,lengthy);

	if(ns==1){//b=d=0
		return stringProd(l,s);
	}
	else{
		int returnSize=nl+ns+1;

		char* a=malloc(sizeof(char)*(nl-ns/2+1));
		char* b=malloc(sizeof(char)*(ns/2)+1);
		char* c=malloc(sizeof(char)*(ns-ns/2+1));
		char* d=malloc(sizeof(char)*(ns/2+1));
		char* ac=malloc(sizeof(char)*(nl+ns+2));//+1
		char* bd=malloc(sizeof(char)*(ns/2+ns/2+2));
//		char* abcd=malloc(sizeof(char)*returnSize+1);
		char* power=malloc(sizeof(char)*(ns/2+2));
		char* power2=malloc(sizeof(char)*(ns/2+ns/2+2));

		int i;
		for(i=0;i<=ns/2-1;i++){
			power[i]='0';
		}
		power[i]='\0';
		for(i=0;i<=(ns/2+ns/2-1);i++){
			power2[i]='0';
		}
		power2[i]='\0';

		char* result=malloc(sizeof(char)*returnSize);
		result[returnSize-1]='\0';

		for(i=0;i<=nl-ns/2-1;i++){
			a[i]=l[i];
		}		
		a[i]='\0';
		
		for(i=0;i<=ns/2-1;i++){
			b[i]=l[nl-ns/2+i];
			d[i]=s[ns-ns/2+i];
		}
		b[i]='\0';
		d[i]='\0';

		for(i=0;i<=ns-ns/2-1;i++){
			c[i]=s[i];
		}		
		c[i]='\0';


		strcpy(ac,karatsuba(a,c));
		strcpy(bd,karatsuba(b,d));

		char* ab=malloc(sizeof(char)*(MAX(strlen(a),strlen(b))+1));
		strcpy(ab,stringSum(a,b));

		char* cd=malloc(sizeof(char)*(MAX(strlen(c),strlen(d))+1));
		strcpy(cd,stringSum(c,d));

		char* ab_cd=malloc(sizeof(char)*(strlen(ab)+strlen(cd)+1));
		strcpy(ab_cd,karatsuba(ab,cd));
		free(ab);free(cd);

		char* ab_cd_ac=malloc(sizeof(char)*(strlen(ab_cd)+1));
		strcpy(ab_cd_ac,stringSubtract(ab_cd,ac));
		free(ab_cd);

		char* abcd=malloc(sizeof(char)*(strlen(ab_cd_ac)+2));
		strcpy(abcd,stringSubtract(ab_cd_ac,bd));
		free(ab_cd_ac);

		int lac=strlen(ac);
		int labcd=strlen(abcd);

		for(i=0;i<=(ns/2+ns/2-1);i++){
			ac[lac+i]='0';
		}
		ac[lac+i]='\0';

		for(i=0;i<=(ns/2-1);i++){
			abcd[labcd+i]='0';
		}	
		abcd[labcd+i]='\0';

		result=stringSum(stringSum(ac,abcd),bd);


//		free(a);free(b);free(c);free(d);free(ac);free(bd);free(abcd);free(power);free(power2);

		return result;
	}
}

char* stringSum(char* x, char* y){
	int lengthx=strlen(x);
	int lengthy=strlen(y);

	int lengths=MIN(lengthx,lengthy);
	int lengthl=MAX(lengthx,lengthy);

	char* s=((lengthx<=lengthy)?x:y);
	char* l=((lengthx>lengthy)?x:y);

	int returnSize=MAX(lengthx, lengthy)+2;
	char* result=malloc(sizeof(char)*returnSize);
	result[returnSize-1]='\0';

	int i;
	int sum=0, temp=0;
	for(i=0;i<=returnSize-2;i++){
		if(i<=lengths-1){
			result[returnSize-2-i]=(s[lengths-1-i]-'0'+l[lengthl-1-i]-'0' + temp)%10 +'0';
			temp=(s[lengths-1-i]-'0'+l[lengthl-1-i]-'0' + temp)/10;
		}
		else if(i<=lengthl-1){
			result[returnSize-2-i]=(l[lengthl-1-i] - '0'+temp)%10 + '0';
			temp=(l[lengthl-1-i]-'0'+temp)/10;
		}
		else{
			result[returnSize-2-i]=temp+'0';
		}
	}

	if((result[0]=='0')&&(result[1]!='\0')){
		return result+1;
	}
	else return result;
}

char* stringSubtract(char* x, char* y){//if x and y have same length, x should greater than y
	int lengthx=strlen(x);
	int lengthy=strlen(y);
	char* s=((lengthy<=lengthx)?y:x);
	char* l=((lengthy>lengthx)?y:x);
	int lengths=MIN(lengthx,lengthy);
	int lengthl=MAX(lengthx,lengthy);
	int returnSize=MAX(lengthx, lengthy)+1;
	char* result=malloc(sizeof(char)*returnSize);
	result[returnSize-1]='\0';
	int i;
	int sub=0, temp=0;
	for(i=0;i<=lengthl-1;i++){
		if(i<=lengths-1){
			result[returnSize-2-i]=(l[lengthl-1-i]-s[lengths-1-i]-temp+10)%10 +'0';
			temp=((l[lengthl-1-i]-s[lengths-1-i]-temp)<0)?1:0;
		}
		else{
			result[returnSize-2-i]=(l[lengthl-1-i] - '0'-temp+10)%10 + '0';
			temp=((l[lengthl-1-i]-'0'-temp)<0)?1:0;
		}
	}

	if((result[0]=='0')&&(result[1]!='\0')){
		return result+1;
	}
	else return result;
}

char* stringProd(char* x, char* y){//suppose y only has 1 digit
	int lengthx=strlen(x);
	int returnSize=lengthx+1+1;
	char* result=malloc(sizeof(char)*returnSize);
	result[returnSize-1]='\0';
	int i;
	int prod=0, temp=0;
	for(i=0;i<=lengthx-1;i++){
		result[returnSize-2-i]=((x[lengthx-1-i]-'0')*(y[0]-'0')+temp)%10+'0';
		temp=((x[lengthx-1-i]-'0')*(y[0]-'0')+temp)/10;
	}
	if(temp>0){
		result[0]=temp+'0';
		return result;
	}
	else return result+1;
}



