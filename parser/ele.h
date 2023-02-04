#ifndef _ELE_HPP_
#define _ELE_HPP_

#include <vector>
#include <map>
#include <string>
#include <sstream>

enum DataType {
    UNKONW_DATA , BOOL , STRING , INTEGER , FLOAT , VEC2f ,VEC3f , VEC4F
};

// basic data type
struct Data {

};

struct SFBool : Data {
    bool val;
    SFBool(bool=false);
};

struct SFString : Data {
    std::string val;
    SFString( std::string = "" );
};

struct SFInt : Data {
    int val;
    SFInt(int=0);
};

struct SFFloat : Data {
    float val;
    SFFloat(float=0);
};

struct SFVec2f : Data {
    float x , y = 0.0f;
    SFVec2f(float=0 , float=0 );
};

struct SFVec3f : Data {
    float x , y , z;
    SFVec3f(float=0 , float=0 , float=0 );
};

struct SFVec4f : Data {
    float x ,y , z,w;
    SFVec4f(float=0 , float=0 , float=0 , float=0);
};

// ------------------------------------------------------------------
// node [name]
// basic node

enum NodeType {
    UNKONW_NODE ,TEXTURE , MATERIAL , GROUP , IMAGE_TEXTURE , COORDINATE ,
    TEXTURE_COORDINATE , NORMAL , INDEXED_FACE_SET , TRANSFORM , APPEARANCE , VIEWPORT ,
    SHAPE , SCENE , NAVIGATIONINFO
};

struct Node {
    std::vector<SFString> annotations = std::vector<SFString>();
    SFString name;
    virtual NodeType type();
};

struct Texture : Node{
    NodeType type();
};

struct Material : Node {
    SFFloat ambientIntensity ;
    SFVec3f diffuseColor;
    SFVec3f specularColor;
    SFFloat shininess;
    NodeType type();
};

struct Group : Node {
    std::vector<Node *> children;

    ~Group();
    NodeType type();
};

struct ImageTexture : Texture {
    SFString url ;
    SFBool repeatS;
    SFBool repeatT;
};

struct Coordinate : Node {
    std::vector<SFVec3f *> point = std::vector<SFVec3f *>();
    ~Coordinate();
    NodeType type();
};

struct TextureCoordinate : Node {
    std::vector<SFVec2f *> point;
    ~TextureCoordinate();
    NodeType type();
};

struct Normal : Node {
    std::vector<SFVec3f *> vec;
    ~Normal();
    NodeType type();
};

struct IndexedFaceSet : Node {
    SFBool ccw;
    SFBool solid;
    SFBool convex;
    SFFloat creaseAngle;
    Coordinate * coord;
    std::vector<SFInt> coordIndex = std::vector<SFInt>();

    TextureCoordinate * texCoord;
    std::vector<SFInt> texCoordIndex = std::vector<SFInt>();

    Normal * normal;
    std::vector<SFInt> normalIndex;

    ~IndexedFaceSet();

    NodeType type();
};

// transform node
struct Transform : Node {
    SFVec3f * translation;
    SFVec3f * rotation;
    SFVec3f * scale;
    std::vector< Node * > children = std::vector< Node * >();

    ~Transform();
    NodeType type();
};

struct NavigationInfo : Node {
    SFBool headlight;
    SFFloat speed;
    std::vector<SFString> _type = std::vector<SFString>();
    NodeType type();
};

// contain texture and material 
struct Appearance : Node {
    Texture * texture;
    Material * material;


    ~Appearance();
    NodeType type();
};

struct Viewport : Node {
    NodeType type();
};

struct Shape : Node {
    Appearance * appearance;
    IndexedFaceSet * geometry;

    ~Shape();
    NodeType type();
};

struct Scene : Node {
    
    Transform * transform;
    NavigationInfo * info;
    Viewport * viewport;
    Shape * shape;

    ~Scene();
    NodeType type();
};


bool isAnnotation( std::string );

bool isKeyWord ( std::string );

bool isNodeType ( std::string );

#endif