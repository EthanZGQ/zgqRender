#include"tool.h"

void Tools::line(int x0 , int y0 , int x1 , int y1 , TGAImage & img , TGAColor & color){
    bool steep = false;
    if(std::abs(y1 - y0) > std::abs(x1 - x0)){
        steep = true;
        std::swap(x0 , y0);
        std::swap(x1 , y1);
    }
    if(x0 > x1){
    std::swap(x0 , x1);
    std::swap(y0 , y1);
    }
    int error = 0;
    int dx = x1 - x0;
    int dy = 2*(std::abs(y1 - y0));
    int postion = y1 - y0 >0 ? 1: -1;
    int y = y0;
    for(int x = x0 ; x <= x1 ;++x){
        if(steep){
            img.set(y , x ,color );
        }
        else img.set(x , y ,color);
        error += dy;
        if(error >= dx){
            error -= 2*dx;
            y += postion;
        }
    }

}


void Tools::triangle(Vec2i pts[],Vec3f world_coords[], TGAImage& img , TGAColor  color , std::vector<float> & zBuffer){
    Vec2i ptMax(0,0) , ptMin(img.get_width() - 1 , img.get_height() - 1);
    for(int i = 0 ; i < 3 ;++i){
        ptMax.x = std::max(ptMax.x , pts[i].x);
        ptMax.y = std::max(ptMax.y , pts[i].y);

        ptMin.x = std::min(ptMin.x , pts[i].x);
        ptMin.y = std::min(ptMin.y , pts[i].y);
    }
    if(ptMin.x < 0) ptMin.x = 0;
    if(ptMin.y < 0) ptMin.y = 0;
    if(ptMax.x > img.get_width() -1) ptMax.x = img.get_width() -1;
    if(ptMax.y > img.get_height() -1) ptMax.y = img.get_height() -1;

    for(int i = ptMin.y ; i <= ptMax.y;++i){
        for(int j = ptMin.x ; j <= ptMax.x ;++j){
            Vec3f re = barycentric(pts , Vec2i(j , i));
            if(re.x < 0 || re.y < 0 || re.z < 0) continue;
            float nowDepth = re.x * world_coords[0].z + re.y *world_coords[1].z + re.z * world_coords[2].z;
            if( nowDepth > zBuffer[i*img.get_height() + j] ){
                zBuffer[i*img.get_height() + j] = nowDepth;
                img.set(j , i ,color);
            }
        }

    }
    
}

void Tools::triangle(Vec3f pts[] , TGAImage & img , TGAColor color , std::vector<float> &zBuffer , TGAImage & texture , float intensity){
    Vec2i screen_coords[3];
    int height = img.get_height() , width = img.get_width();
    for(int  i = 0 ; i < 3 ;++i){
        screen_coords[i].x = static_cast<int>((pts[i].x + 1)*width/2);
        screen_coords[i].y = static_cast<int>((pts[i].y + 1)*width/2);
    }
    Vec2i ptMax(0,0) , ptMin(img.get_width() - 1 , img.get_height() - 1);
    for(int i = 0 ; i < 3 ;++i){
        ptMax.x = std::max(ptMax.x , pts[i].x);
        ptMax.y = std::max(ptMax.y , pts[i].y);

        ptMin.x = std::min(ptMin.x , pts[i].x);
        ptMin.y = std::min(ptMin.y , pts[i].y);
    }
    if(ptMin.x < 0) ptMin.x = 0;
    if(ptMin.y < 0) ptMin.y = 0;
    if(ptMax.x > img.get_width() -1) ptMax.x = img.get_width() -1;
    if(ptMax.y > img.get_height() -1) ptMax.y = img.get_height() -1;

    for(int i = ptMin.y ; i <= ptMax.y;++i){
        for(int j = ptMin.x ; j <= ptMax.x ;++j){
            Vec3f re = barycentric(pts , Vec2i(j , i));
            if(re.x < 0 || re.y < 0 || re.z < 0) continue;
            float nowDepth = re.x * pts[0].z + re.y *pts[1].z + re.z * pts[2].z;
            if( nowDepth > zBuffer[i*img.get_height() + j] ){
                zBuffer[i*img.get_width() + j] = nowDepth;
                TGAColor color[3];
                for(int i = 0 ; i < 3 ;++i){
                    color[0] = texture.get(static_cast<int>(pts[0]:))
                }
                img.set(j , i ,color);
            }
        
        }
    }

inline Vec3f Tools::barycentric(Vec2i *pts, Vec2i && P) {
    Vec3f u = Vec3f(pts[2].x-pts[0].x, pts[1].x-pts[0].x, pts[0].x-P.x)^Vec3f(pts[2].y-pts[0].y, pts[1].y-pts[0].y, pts[0].y-P.y);
    /* `pts` and `P` has integer value as coordinates
       so `abs(u[2])` < 1 means `u[2]` is 0, that means
       triangle is degenerate, in this case return something with negative coordinates */
    if (std::abs(u.z)<1) return Vec3f(-1,1,1);
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
}



inline Vec3f barycentric(Vec3f pts[] , Vec2i P){
    Vec3f temp = Vec3f(pts[2].x - ptr[0].x , ptr[1].x - ptr[0].x , ptr[0].x - P.x)^Vec3f(pts[2].y - ptr[0].y , ptr[1].y - ptr[0].y , ptr[0].y - P.y);
    if(temp.z < 1) return Vec3f(-1, 1,1);
    return Vec3f(1.0 - (temp.x + temp.y)/temp.z , temp.y/temp.z , temp.x/temp.z);

}
