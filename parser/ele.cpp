#include "ele.h"

SFBool::SFBool( bool val):val(val){}

SFString::SFString( std::string val ):val(val){}

SFInt::SFInt(int val):val(val){}

SFFloat::SFFloat(float val):val(val){}

SFVec2f::SFVec2f(float x, float y):x(x),y(y){}

SFVec3f::SFVec3f(float x, float y, float z):x(x),y(y),z(z){}

SFVec4f::SFVec4f(float , float , float , float):x(x),y(y),z(z),w(w){}

NodeType Node::type(){
    return UNKONW_NODE;
}

NodeType Texture::type(){
    return TEXTURE;
}

NodeType Material::type(){
    return MATERIAL;
}

// group
Group::~Group(){
    std::vector<Node*>::iterator begin = this->children.begin();
    std::vector<Node*>::iterator end = this->children.end();
    while( begin < end ){
        std::vector<Node *>::iterator tmp = begin;
        begin += 1;
        Node * node = *tmp;
        delete node;
    }
    this->children.clear();
}

NodeType Group::type(){
    return GROUP;
}

// coordinate

Coordinate::~Coordinate(){
    std::vector<SFVec3f*>::iterator begin = this->point.begin();
    std::vector<SFVec3f*>::iterator end = this->point.end();
    while( begin < end ){
        std::vector<SFVec3f *>::iterator tmp = begin;
        begin += 1;
        SFVec3f * vec = *tmp;
        delete vec;
    }
    this->point.clear();
}

NodeType Coordinate::type(){
    return COORDINATE;
}

// texture coordinate

TextureCoordinate::~TextureCoordinate(){
    std::vector<SFVec2f*>::iterator begin = this->point.begin();
    std::vector<SFVec2f*>::iterator end = this->point.end();
    while( begin < end ){
        std::vector<SFVec2f *>::iterator tmp = begin;
        begin += 1;
        SFVec2f * vec = *tmp;
        delete vec;
    }
    this->point.clear();
}

NodeType TextureCoordinate::type(){
    return TEXTURE_COORDINATE;
}

// normal

Normal::~Normal(){
    std::vector<SFVec3f*>::iterator begin = this->vec.begin();
    std::vector<SFVec3f*>::iterator end = this->vec.end();
    while( begin < end ){
        std::vector<SFVec3f *>::iterator tmp = begin;
        begin += 1;
        SFVec3f * vec = *tmp;
        delete vec;
    }
    this->vec.clear();
}

NodeType Normal::type(){
    return NORMAL;
}

// indexed face set

IndexedFaceSet::~IndexedFaceSet(){
    delete this->coord;
    delete this->texCoord;
    delete this->normal;
}

NodeType IndexedFaceSet::type(){
    return INDEXED_FACE_SET;
}


// transform

Transform::~Transform(){
    delete this->translation;
    delete this->rotation;
    delete this->scale;
}

NodeType Transform::type(){
    return TRANSFORM;
}

// Appearance

Appearance::~Appearance(){
    delete this->texture;
    delete this->material;
}

NodeType Appearance::type(){
    return APPEARANCE;
}

NodeType Viewport::type(){
    return VIEWPORT;
}

NodeType NavigationInfo::type() {
    return NAVIGATIONINFO;
}

// Shape

Shape::~Shape(){
    delete this->appearance;
    delete this->geometry;
}

NodeType Shape::type(){
    return SHAPE;
}

// Scene

Scene::~Scene(){
    delete this->viewport;
    delete this->shape;
}

NodeType Scene::type(){
    return SCENE;
}

// tools
// 保留关键字
std::vector<std::string> reservedKeyWord = {
    "DEF" , "EXTERNPROTO" , "FALSE" , "IS" , "NULL" , "PROTO" , "ROUTE" ,
    "TO" , "TRUE" , "USE" , "eventIn" , "eventOut" , "exposedField" , "field"
};

// 子节点类型
std::vector<std::string> nodeType = {
    "Anchor" , "LOD" , "Sound" , "Background" , "NavigationInfo" , "SpotLight" , 
    "Billboard" , "NormalInterpolator" , "SphereSensor" , "Collision" , "OrientationInterpolator", "Switch"
    "ColorInterpolator" , "PlaneSensor" , "TimeSensor" , "CoordinateInterpolator" , "PointLight" , "TouchSensor" , 
    "CylinderSensor" , "PositionInterpolator" , "Transform" , "DirectionalLight" , "ProximitySensor" , "Viewpoint" , 
    "Fog" , "ScalarInterpolator" , "VisibilitySensor" , "Group" , "Script" , "WorldInfo" , 
    "Inline" , "Shape" ,"PROTO","NavigationInfo"
};

//group node type
std::vector<std::string> groupNodeType = {
    "Anchor" , "Billboard" , "Collision" , "Group" , "Transform"
};

// geometry node type
std::vector<std::string> geometryNodeType = {
    "Box","Cone","Cylinder","ElevationGrid","Extrusion","IndexedFaceSet",
    "IndexedLineSet","PointSet","Sphere","Text"
};

// properties node type 
std::vector<std::string> NodePropType = {
    "Coordinate", "Color" , "Normal" , "TextureCoordinate" ,
};

bool isAnnotation( std::string str ){
    return ( str.size() > 0 ) && ( str.at(0) == '#' );
}

bool isKeyWord( std::string name ){
    for(int i = 0 ; i < reservedKeyWord.size() ; ++ i){
        std::string item = reservedKeyWord.at( i );
        if(item == name){
            return true;
        }
    }
    return false;
}

bool isNodeType( std::string name ){
    for(int i = 0 ; i < nodeType.size() ; ++ i){
        std::string item = nodeType.at( i );
        if(item == name){
            return true;
        }
    }
    return false;
}
