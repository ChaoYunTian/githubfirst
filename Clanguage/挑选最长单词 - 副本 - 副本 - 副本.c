#include<stdio.h>
#include<string.h>
#define N 100
int max;
int longest(char str[])
{
	int i,length=0,count=0,L=strlen(str);
	for(i=0;i<=L;i++)
	{
		if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
		length++;
		else if(length!=0)
		{
			if(length>max)
			{
				max=length;
				count=i-max;
			}
			length=0;
		}
		else continue;
	}
	return count;
}
int main()
{
	char str[N];
	gets(str);
	int start=longest(str),i;
	for(i=start;i<start+max;i++)
	printf("%c",str[i]);
	return 0;
}
