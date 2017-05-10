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

	char* xy=karatsuba(x,y);
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

		char* a=malloc(sizeof(char)*(nl-ns/2+1));//+1: '\0'
		char* b=malloc(sizeof(char)*(ns/2)+1);//+1: '\0'
		char* c=malloc(sizeof(char)*(ns-ns/2+1));//+1: '\0'
		char* d=malloc(sizeof(char)*(ns/2+1));//+1: '\0'
		char* ac=malloc(sizeof(char)*(nl+ns+2));//+1: can be (nl+ns+1) digits after multiplication; +1:'\0'
		char* bd=malloc(sizeof(char)*(ns/2+ns/2+2));//+1: can be (nl+ns+1) digits after multiplication; +1:'\0'
		char* abcd=malloc(sizeof(char)*returnSize+1);//allocate a little bit more

		//get a,c,b,d
		int i;
		for(i=0;i<=nl-ns/2-1;i++){
			a[i]=l[i];
		}		
		a[i]='\0';

		for(i=0;i<=ns-ns/2-1;i++){
			c[i]=s[i];
		}		
		c[i]='\0';
		
		for(i=0;i<=ns/2-1;i++){
			b[i]=l[nl-ns/2+i];
			d[i]=s[ns-ns/2+i];
		}
		b[i]='\0';
		d[i]='\0';

		//get ac=a*c, bd=b*d
		char* temp_ac=karatsuba(a,c);
		char* temp_bd=karatsuba(b,d);
		strcpy(ac,temp_ac);
		strcpy(bd,temp_bd);
		free(temp_ac);
		free(temp_bd);

		//get ab=a+b, cd=c+d, ab_cd=(a+b)*(c+d)
		char* ab=stringSum(a,b);
		char* cd=stringSum(c,d);
		char* ab_cd=karatsuba(ab,cd);
		free(ab);free(cd);

		//get ab_cd_ac=ab_cd=(a+b)*(c+d)-ac
		char* ab_cd_ac=stringSubtract(ab_cd,ac);
		free(ab_cd);

		//get abcd=ab_cd=(a+b)*(c+d)-ac-bd
		char* temp_abcd=stringSubtract(ab_cd_ac,bd);
		strcpy(abcd,temp_abcd);
		free(ab_cd_ac);

		int lac=strlen(ac);
		int labcd=strlen(temp_abcd);

		for(i=0;i<=(ns/2+ns/2-1);i++){
			ac[lac+i]='0';
		}
		ac[lac+i]='\0';

		for(i=0;i<=(ns/2-1);i++){
			abcd[labcd+i]='0';
		}	
		abcd[labcd+i]='\0';

		//get result=[10^(ns/2+ns/2)*a*c]+ [10^(ns/2)*(a+b)*(c+d)-ac-bd] + [b*d]
		char* temp_ac_abcd=stringSum(ac,abcd);
		char* result=stringSum(temp_ac_abcd,bd);
		free(temp_ac_abcd);
		free(temp_abcd);

		free(a);free(b);free(c);free(d);free(ac);free(bd);free(abcd);

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
		char* newresult=malloc(sizeof(char)*(returnSize-1));
		int j;
		for(j=0;j<=returnSize-2;j++){
			newresult[j]=result[j+1];
		}
		free(result);
		return newresult;
	}
	else return result;
}

char* stringSubtract(char* x, char* y){//if x and y have same length, x should be greater than y
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
		char* newresult=malloc(sizeof(char)*(returnSize-1));
		int j;
		for(j=0;j<=returnSize-2;j++){
			newresult[j]=result[j+1];
		}
		free(result);
		return newresult;
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
	else{ 
		char* newresult=malloc(sizeof(char)*(returnSize-1));
		int j;
		for(j=0;j<=returnSize-2;j++){
			newresult[j]=result[j+1];
		}
		free(result);
		return newresult;
	}
}



