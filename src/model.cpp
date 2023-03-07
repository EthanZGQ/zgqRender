#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() , textures_(),normals_(){
    std::fstream file(filename);
    if(!file.is_open()){
        std::cout << "error! can't open the file !" ;
    }
    std::vector<Vec3f> verts_;
    std::string line;
    int v = 0 , vt = 0 , vn = 0 , f = 0;
    while(!file.eof()){
        std::getline(file , line);
        std::istringstream iss(line);
        char trash;
        if(line[0] == '#') continue;
        else if(line.compare(0,2,"v ") == 0){
            iss>>trash;
            Vec3f temp;
            iss >> temp.x >> temp.y >> temp.z;
            verts_.push_back(temp);
            ++v;
        }
        else if(line.compare(0 , 2 , "vt")==0){
            iss >> trash >> trash;
            Vec2f temp;
            iss >> temp.x >> temp.y;
            textures_.push_back(temp);
            ++vt;
        }
        else if(line.compare(0,2,"vn")==0){
            iss >> trash >>trash;
            Vec3f temp ;
            iss >> temp.x >> temp.y >>temp.z;
            normals_.push_back(temp);
            ++vn;
        }
        else if(line.compare(0 ,2 ,"f ") == 0){
            std::vector<std::vector<int>> temp(3 , std::vector<int>());
            iss >> trash;
            for(int i = 0 ; i < 3 ; i++){
                int mem;
                iss >> mem;
                temp[0].push_back(mem);
                iss >> trash;
                iss >>mem;
                temp[1].push_back(mem);
                iss>>trash;
                iss >>mem;
                temp[2].push_back(mem);
            }
            faces_.push_back(temp);
            ++f;
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

const std::vector<std::vector<int>> & Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

Vec2f texture(int i){
    return textures_[i];
}

Vec3f normal(int i){
    return normals_[i];
}
