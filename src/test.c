#include <stdio.h>
#include <string.h>

char *getsql(char *rtn,char *arraycmh[],int arraylen)
{
	strcpy(rtn,arraycmh[0]);
	int i;
	for(i=1;i<arraylen;i++)
	{
		strcat(rtn,arraycmh[i]);
	}
	return rtn;
}
int main(){
	char *sql="sql";
	char *sql2="sql2";
	char *arraycmh[333];
	arraycmh[0]=sql;
	arraycmh[1]=sql2;
	arraycmh[2]="sql3";
	char  rtn[50];
	getsql(rtn,arraycmh,3);
	printf("%s\n",rtn);
}
