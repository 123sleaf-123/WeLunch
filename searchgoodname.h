#include<stdio.h>
#include<string.h>

int searchGoodName(char* s1,char* s2){
	char*p;
	if(strlen(s1)>strlen(s2)){
		if((p=strstr(s1,s2))==NULL)//��s1����s2 
			return 0;
			else
			return 1;
	}else{
		if((p=strstr(s2,s1))==NULL)
			return 0;
			else
			return 1;
	}//�Ҷ̴����ж��Ƿ����Ӵ�,�����1���������0 
} 
