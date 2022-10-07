#ifndef _ELE_HPP_
#define _ELE_HPP_

#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

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
    string val;
    SFString(string="");
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

//------------------------------------------------------------------
// node [name]
// basic node

enum NodeType {
    UNKONW_NODE ,TEXTURE , MATERIAL , GROUP , IMAGE_TEXTURE , COORDINATE ,
    TEXTURE_COORDINATE , NORMAL , INDEXED_FACE_SET , TRANSFORM , APPEARANCE , VIEWPORT ,
    SHAPE , SCENE
};

struct Node {
    vector<SFString> annotations = vector<SFString>();
    SFString name;
    virtual NodeType type();
};

struct Texture : Node{
    NodeType type();
};

struct Material : Node {
    NodeType type();
};

struct Group : Node {
    vector<Node *> children;

    ~Group();
    NodeType type();
};

struct ImageTexture : Texture {
    SFString url ;
    SFBool repeatS;
    SFBool repeatT;
};

struct Coordinate : Node {
    vector<SFVec3f *> point = vector<SFVec3f *>();
    ~Coordinate();
    NodeType type();
};

struct TextureCoordinate : Node {
    vector<SFVec2f *> point;
    ~TextureCoordinate();
    NodeType type();
};

struct Normal : Node {
    vector<SFVec3f *> vec;
    ~Normal();
    NodeType type();
};

struct IndexedFaceSet : Node {
    SFBool ccw;
    SFBool solid;
    SFBool convex;
    Coordinate * coord;
    vector<SFInt> coordIndex;

    TextureCoordinate * texCoord;
    vector<SFInt> texCoordIndex;

    Normal * normal;
    vector<SFInt> normalIndex;

    ~IndexedFaceSet();

    NodeType type();
};

// transform node
struct Transform : Node {
    SFVec3f * translation;
    SFVec3f * rotation;
    SFVec3f * scale;

    ~Transform();
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
    
    Viewport * viewport;
    Shape * shape;

    ~Scene();
    NodeType type();
};


bool isAnnotation( string str );

bool isKeyWord (string );

bool isNodeType ( string );

#endif