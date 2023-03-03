#include<iostream>
#include"tgaimage.h"

int main(){
    std::cout << "Hello World!" << std::endl;
    TGAImage img(256,256,TGAImage::RGB);
    TGAColor color(255,0,255,255);
    img.set(128,128,color);
    img.write_tga_file("first.tga");
    std::cout << "convert complete!"<<std::endl;
    return 0;
}



