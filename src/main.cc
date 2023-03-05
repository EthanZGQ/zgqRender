#include<iostream>
#include"tgaimage.h"
#include"tool.h"
#include"model.h"
#include<string>
#include<memory>
#include<stdlib.h>
int main(){
    std::cout << "Hello World!" << std::endl;
    int width = 512 , height = 512;
    TGAImage img(width,height,TGAImage::RGB);
    TGAColor color(255,0,255,255);
    Vec3f light(0,0,-1);
    auto mol = std::make_unique<Model>( "../obj/african_head.obj");
    Vec2i x[3] = {Vec2i(0,0), Vec2i(30, 0), Vec2i(0, 40)};
    //std::cout <<mol->nverts();
    //Tools::line(0,0,128,128,img,color);
    //img.write_tga_file("first.tga");
    //for(int i = 0 ; i < mol->nfaces() ;++i){
        //std::vector<int> temp = mol->face(i);
        //for(int j = 0 ; j < 3 ;++j){
            //auto v0 = mol->vert(temp[j]);
            //auto v1 = mol->vert(temp[(j+1)%3]);
            //int x0 = static_cast<int>((v0.x + 1)*width/2);
            //int y0 = static_cast<int>((v0.y + 1)* height/2);
            //int x1 = static_cast<int>((v1.x + 1)*width/2);
            //int y1 = static_cast<int>((v1.y + 1)* height/2);
            //Tools::line(x0 , y0 , x1 , y1 , img , color);
        //}
    //}
    for (int i=0; i<mol->nfaces(); i++) {
        std::vector<int> face = mol->face(i);
        Vec2i screen_coords[3];
        Vec3f world_c[3];
        for (int j=0; j<3; j++) {
            Vec3f world_coords = mol->vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x+1.)*width/2., (world_coords.y+1.)*height/2.);
            world_c[j] = world_coords;
        }
        Vec3f n = (world_c[0] - world_c[1])^(world_c[1] - world_c[2] );
        n.normalize();
        float intensity= n * light;
        Tools::triangle(screen_coords, img, TGAColor(intensity*255, intensity*255, intensity*255, 255));
    }
    img.flip_vertically();
    img.write_tga_file("lightHead.tga");
    std::cout << "convert complete!"<<std::endl;
    return 0;
}



