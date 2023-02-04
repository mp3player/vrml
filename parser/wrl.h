#ifndef _WRL_HPP_
#define _WRL_HPP_

#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#include "ele.h"

namespace WRL {

struct Parser{

    static std::vector<std::string> read( std::string );

    static std::string readString ( std::string & , int & , char = ' ' );

    static int parseInt( std::string str );

    static float parseFloat( std::string str );

    static Node * parseNode( std::vector<std::string> & , int & , std::string);

    static Node * parseNode( std::vector<std::string> & , int & );

    static Texture * parseTexture( std::vector<std::string> & , int &);

    static Material * parseMaterial ( std::vector<std::string> & , int & );
    
    static Group * parseGroup ( std::vector<std::string> & , int &);

    static std::vector<Node *> parseChildren ( std::vector<std::string> & , int & );

    static ImageTexture * parseImageTexture ( std::vector<std::string> & , int &);
    
    static Coordinate * parseCoordinate ( std::vector<std::string> & , int &);
    
    static TextureCoordinate * parseTextureCoordinate ( std::vector<std::string> & , int & );
    
    static Normal * parseNormal ( std::vector<std::string> & , int & );
    
    static IndexedFaceSet * parseIndexedFaceSet ( std::vector<std::string> & , int & );
    
    static Transform * parseTransform ( std::vector<std::string> & , int &);
    
    static Appearance * parseAppearance ( std::vector<std::string> & , int & );
    
    static Viewport * parseViewport ( std::vector<std::string> & , int & );
    
    static Shape * parseShape ( std::vector<std::string> & , int & );

    static Scene * parseScene( std::vector<std::string> & , int & );

    static NavigationInfo * parseNavigationInfo( std::vector< std::string > & , int & );

    static Scene *  parse( std::string );

    static void store( std::string , Scene * );

};

}

#endif