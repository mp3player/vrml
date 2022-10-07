#ifndef _WRL_HPP_
#define _WRL_HPP_



#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#include "ele.h"

using namespace std;

namespace WRL {

struct Parser{

    static vector<string> read( string );

    static string readString ( string & , int & , char = ' ' );

    static int parseInt( string str );

    static float parseFloat( string str );

    static Node * createNode( string );

    static Node * parseNode( vector<string> & , int & , string);

    static Node * parseNode( vector<string> & , int & );

    static Texture * parseTexture( vector<string> & , int &);

    static Material * parseMaterial ( vector<string> & , int & );
    
    static Group * parseGroup ( vector<string> & , int &);

    static vector<Node *> parseChildren ( vector<string> & , int & );

    static ImageTexture * parseImageTexture ( vector<string> & , int &);
    
    static Coordinate * parseCoordinate ( vector<string> & , int &);
    
    static TextureCoordinate * parseTextureCoordinate ( vector<string> & , int & );
    
    static Normal * parseNormal ( vector<string> & , int & );
    
    static IndexedFaceSet * parseIndexedFaceSet ( vector<string> & , int & );
    
    static Transform * parseTransform ( vector<string> & , int &);
    
    static Appearance * parseAppearance ( vector<string> & , int & );
    
    static Viewport * parseViewport ( vector<string> & , int & );
    
    static Shape * parseShape ( vector<string> & , int & );

    static Scene * parseScene( vector<string> & , int & );

    static void parse( string );

};

}

#endif