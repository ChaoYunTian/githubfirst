#include <iostream>

#include "Image.h"

using namespace std;

int main(int argc, char* argv[])
{
    Matrix m(160000,1);
    for (int i = 0; i < 160000; i++)
    {
        m.At(i, 0) = i%256;
    }

    m.Reshape(400, 400);

    Image img(m);

    img.Show("Matrix");

    Matrix d = m.MajorDiagonal();

    Image *p = new Image(d);

    p->Show("pImage");

    p->Reshape(20,20);

    p->Show("pImageReshaped");

    Image im("Fruits.jpg");

    im.Resize(200, 200);

    im.Show("Resized Image");


    im.Rotate(120);

    im.Show("Rotated Image");


    Image img1("Fruits.jpg");

    img1.Show("Image2");

    Image img2("Word.jpg");

    img2.Show("Image1");

    //两图片相加

    Image img_add(Add(img1, img2)) ;

    img_add.Show("Add");


   //两图片相减

    Image img_sub(Sub(img1, img2));

    img_sub.Show("Sub");


   //图片的转置

    Image img3("lena.jpg");

    img3.Transpose();

    img3.Show("Transpose");


     //在右边拼接图片；

    Image img4("Airplane.jpg");

    Image img5("Baboon.jpg");

    img4.Cat(img5,1);

    img4.Show("CATRight");


    //在下面拼接图片

    Image img6("Airplane.jpg");

    Image img7("Baboon.jpg");

    img6.Cat(img7,2);

    img6.Show("CATDown");

    return 0;
}


