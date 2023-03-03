#include<iostream>
#include"tgaimage.h"

int main(){
    std::cout << "Hello World!" << std::endl;
    TGAImage img(256,256,TGAImage::RGB);
    TGAColor color(255,0,255,255);
    for(int row = 0 ; row < 256 ;++row){
        for(int col = 0 ; col < 256 ; ++col){
            img.set(row,col,color);
        }
    }
    img.set(0,0,color);
    img.write_tga_file("first.tga");
    std::cout << "convert complete!"<<std::endl;
    return 0;
}



