#include<stdio.h>
#include<string.h>
int main()
{
char a[21];
gets(a);//输入字符串
int i;
for(i=0;i<=strlen(a);i++)//strlen(a),得到字符串的长度
{
     if(a[i]>='a'&&a[i]<='w'||a[i]>='A'&&a[i]<='W')
        a[i]=a[i]+4;
    else if(a[i]>='w'&&a[i]<='z'||a[i]>='W'&&a[i]<='Z')
        a[i]=a[i]-22;
}//输出字符串(a);
puts(a);
return 0;
}
