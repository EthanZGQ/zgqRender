#include"tgaimage.h"
#include<algorithm>
#include"geometry.h"
#include<vector>
class Tools{

public:
    static void line(int x0 , int y0 , int x1 , int y1 , TGAImage & img , TGAColor & color);
    static void triangle(Vec2i pts[],Vec3f  world_coords[] , TGAImage& img , TGAColor  color , std::vector<float> &zBuffer);
    static inline Vec3f barycentric(Vec2i *pts , Vec2i && P);
    static inline Vec3f barycentric(Vec3f pts[] , Vec2i P){
};
