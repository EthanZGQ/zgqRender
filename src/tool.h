#include"tgaimage.h"
#include<algorithm>
#include"geometry.h"
class Tools{

public:
    static void line(int x0 , int y0 , int x1 , int y1 , TGAImage & img , TGAColor & color);
    static void triangle(Vec2i pts[],TGAImage& img , TGAColor  color);
    static inline Vec3f barycentric(Vec2i *pts , Vec2i && P);
};
