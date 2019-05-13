#include<iostream>
#include<cstdlib>
#define N 10
using namespace std;

int main()
{
    int n,a[N],sum = 0,temp = 0;
    for(int i = 0; i < N; i++)
    {
        cin>>a[i];
    }
    for(int i = 0; i < N; i++)
    {
        if(a[i] == 1)
        {
            sum += 1;
        }
        else if(a[i] == 2)
        {
            int count = 1;
            sum += 2;
            for(int j = i; j < N ;j++)
            {
                if(a[j] == a[j + 1] && (j + 1) < N)
                {
                    count++;
                    sum += 2 * count;
                    temp = j + 1;
                }
                else
                {
                    temp = j;
                    break;
                }
            }
            i = temp;
        }
    }
    cout<< sum << endl;
    return 0;
}
