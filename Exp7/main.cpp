#include <opencv2/opencv.hpp>

#include <iostream>
#include "Matrix.h"
#include "Image.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "1000" << endl;
    Image img1("scene1_fg.jpg");
    Image img2("scene1_bg.jpg");
    img1.Show("const img1");
    img2.Show("const img2");

    Image sub = (img1 - img2);
    sub.Show("const sub");

    Image sum = (img1 + img2);
    sum.Show("const sum");

    Image product = sum * 2;
    product.Show("const product*2");

    product = (-product);
    product.Show("-product");

    Image bw = sub.gray2bw(30);
    bw.Show("const bw");
    while(true)
    {
       int num;
       cout << "ÇëÑ¡Ôñ²Ù×÷²½Öè£º " << endl;
       cout << "1:Í¼ÏñÎ¢(µ÷ÁÁ) " << endl;
       cout << "2:Í¼ÏñÎ¢(µ÷°µ) " << endl;
       cout << "3:Í¼Ïñ(´ó·ù¶Èµ÷ÁÁ) " << endl;
       cout << "4:Í¼Ïñ(´ó·ù¶Èµ÷°µ) " << endl;
       cout << "5:ÍË³ö" << endl;
       cin >> num;
       if(num > 0 && num < 5)
       {
          switch(num)
          {
             case 1:
               {
                  for(int i = 0; i <10; ++i, ++img1);
                  img1.Show("img1");
                  break;
               }
             case 2:
               {
                  for(int i = 0; i <10; ++i, --img1);
                  img1.Show("img2");
                  break;
               }
             case 3:
               {
                  img1 = img1 + 30;
                  img1.Show("img3");
                  break;
               }
             case 4:
               {
                  img1 = img1 - 30;
                  img1.Show("img4");
                  break;
               }
             default:
                  break;
          }
          cout << endl;
       }
       else
         break;
    }

    return 0;
}


