#include "wrl.h"
#include <thread>
#include <chrono>

using namespace WRL;

#define _WHITE_SPACE_ '\0'
#define _NEW_LINE_ '\r'
#define _ENTER_ '\n'
#define _TABLE_ '\t'
#define _SPACE_ ' '
#define _QUOTE_ '"'
#define _SHARP_ '#'
#define _COMMA_ ','


vector<string> Parser::read( string fileName ){

    vector<string> list = vector<string>();
    ifstream file( fileName , ios::in );
    string content;

    char c = file.get();
    while( !file.eof() ){
        content += c;
        c = file.get();
    }
    file.close();

    string val;
    int index = 0;
    int k = 0;
    bool valid = false;
    while( index < content.size() ){
        char c = content.at( index );
        string val;
        switch( c ){
            case _SHARP_:{
                val = Parser::readString( content , index , _ENTER_ );
                valid = true;
            }break;

            case _QUOTE_ :{
                val = Parser::readString( content , index , _QUOTE_ );
                valid = true;
            }break;

            case _SPACE_:{

            }break;

            case _ENTER_:{

            }break;
            case _TABLE_:{
                
            }break;
            case _NEW_LINE_:{

            }break;

            default :{
                val = Parser::readString( content , index , _WHITE_SPACE_ );
                valid = true;
            }break;

        }
        index += 1;
        if(valid) list.push_back( val );
        valid = false;
    }
    return list;   
}


string Parser::readString ( string & content , int & index , char end){
    if(end == _QUOTE_) index += 1;
    char c = content.at( index );

    function< bool(char , char) > assertion = []( char c , char t){

        if(t == _WHITE_SPACE_){
            return  c != _SPACE_ && 
                    c != _ENTER_ && 
                    c != _TABLE_ &&
                    c != _NEW_LINE_ &&
                    c != _COMMA_ ;
        }
        
        return c != t;
    };
    
    string val = "";
    while( assertion( c , end ) ){
        if(c != _NEW_LINE_ && c != _ENTER_ ) 
            val += c;
        index += 1;
        c = content.at( index );
    }
    return val;
}

int Parser::parseInt( string str ){
    stringstream ss ;
    ss << str ;
    int val ;
    ss >> val;
    return val;
}

float Parser::parseFloat( string str ){
    stringstream ss ;
    ss << str ;
    float val ;
    ss >> val;
    return val;
}

Node * Parser::createNode( string type){
    Node * node;
    if(type == "Viewpoint"){
        node = new Viewport();
    }else if( type == "Shape" ){
        node = new Shape();
    }else if( type == "Appearance" ){
        node = new Appearance();
    }else if( type == "ImageTexture" ){
        node = new ImageTexture();
    }else if( type == "IndexedFaceSet" ){
        node = new IndexedFaceSet();
    }else if( type == "Coordinate" ){
        node = new Coordinate();
    }else if( type == "TextureCoordinate" ){
        node = new TextureCoordinate();
    }else if( type == "Group" ){
        node = new Group();
    }else{
        node = new Node();
    }
    return node;
}

Node * Parser::parseNode( vector<string> & list, int & index, string type){
    Node * node;
    if(type == "Viewpoint"){
        node = Parser::parseViewport( list , index );
    // }else if( type == "Shape" ){
        node = Parser::parseShape( list , index );
    }else if( type == "Appearance" ){
        node = Parser::parseAppearance( list , index );
    }else if( type == "ImageTexture" ){
        node = Parser::parseImageTexture( list , index );
    }else if( type == "IndexedFaceSet" ){
        node = Parser::parseIndexedFaceSet( list , index );
    }else if( type == "Coordinate" ){
        node = Parser::parseCoordinate( list , index );
    }else if( type == "TextureCoordinate" ){
        node = Parser::parseTextureCoordinate( list , index );
    }else if( type == "Group" ){
        node = Parser::parseGroup( list , index );
    }else{
        node = Parser::parseNode( list , index );
    }
    return node;
}

Node * Parser::parseNode( vector<string> & list , int & index){
    // std::cout << index << std::endl;
    string item = list.at( index );
    string name ;
    string type ;

    Node * node;
    while( item.at(0) == '#' ){
        index += 1;
        item = list.at( index );
    }
    // std::cout << index << std::endl;
    if( isKeyWord(item) ){

        if(item == "DEF"){
            
            name = list.at( index + 1); // name
            type = list.at( index + 2); // nodeType
            index += 2;
            node = Parser::parseNode( list , index , type );
            
        }

    }else if( isNodeType(item) ){
        type = item;
        node = Parser::parseNode( list , index , type );
    }else {
        name = item;
        index += 1;
        type = list.at( index );
        node = Parser::parseNode( list , index , type );
    }

    // don't skip the end character }
    node->name = name;
    return node;
}

// 解析的类型都是 Type {}

Texture * Parser::parseTexture( vector<string> & list , int & index  ){
    return nullptr;
}

Material * Parser::parseMaterial ( vector<string> & list, int & index){
    return nullptr;
}

Group * Parser::parseGroup ( vector<string> & list , int & index){
    std::cout << "* parse Group *" << std::endl;
    // TODO : start with Group , need to skip the type flag
    // [name]Group { children [ ] ... }
    
    
    //TODO : check out if the name contain name character
    string name ;
    string type ;
    string str = list.at( index );

    if( isNodeType(str) ){
        // have no name
        type = str;
    }else{
        name = str;
        index += 1;
        type = str.at( index );
    }

    // skip the character : [name]Group + {
    index += 1;
    string item = list.at( index );

    Group * group = new Group();
    while( item != "}" ){
        if(item == "children"){
            index += 1;
            vector<Node *> children = Parser::parseChildren( list , index );
            for( int i = 0 ; i < children.size() ; ++ i ){
                group->children.push_back( children.at( i ) );
            }
        }else if(item == "bboxCenter"){
            // do nothing
        }else if(item == "bboxSize") {
            // do nothing
        }
        
        index += 1;
        item = list.at( index );
    }
    // don't skip the }
    group->name = name;
    return group;
}

vector<Node *> Parser::parseChildren ( vector<string> & list , int & index ){
    // TODO : start with children , need to skip the type flag
    // children [ ]
    // skip the character : children + [
    index += 2;
    string name = list.at( index );
    
    vector<Node *> children = vector<Node *>();

    while( name != "]" ){
        Node * child = Parser::parseNode( list , index );
        children.push_back( child );
        index += 1;
        name = list.at( index );
    }
    // the position is at the position of ]
    // don't skip ]
    return children;
}

ImageTexture * Parser::parseImageTexture ( vector<string> & list , int & index ){
    std::cout << "* parse ImageTexture *" << std::endl;
    // TODO : start with ImageTexture , need to skip the type flag
    // ImageTexture { url path  repeatS true repeatT false }
    
    // skip : Type + {
    index += 2;
    string name = list.at( index );

    ImageTexture * iTex = new ImageTexture();
    while( name != "}" ){
        if(name == "url"){
            index += 1;
            string url = list.at( index );
            iTex->url = url;
        }else if(name == "repeatS"){
            index += 1;
            string repeatS = list.at( index );
        }else if(name == "repeatT"){
            index += 1;
            string repeatT = list.at( index );
        }
        // go to next property
        index += 1;
        name = list.at( index );
    }

    // don't skip the end character : }
    return iTex;
}

Coordinate * Parser::parseCoordinate ( vector<string> & list , int & index ){
    std::cout << "* parse Coordinate *" << std::endl;
    // TODO : start with Coordinate , need to skip the type flag
    

    // skip : Type + {
    index += 2;
    string name = list.at( index );

    Coordinate * coord = new Coordinate();
    while( name != "}" ){
        if( name == "point" ){
            // collect point value 
            // skip "point" & "[""
            vector<float> values = vector<float>();
            index += 2;
            name = list.at( index );
            while( name != "]"){
                float value = Parser::parseFloat(name);
                values.push_back(value);

                index += 1;
                name = list.at( index );
            }
            if(values.size() % 3 != 0){
                std::cout << "position count is wrong" << std::endl;
            }else{
                int size = values.size() ;
                for(int i = 0 ; i < size / 3 ; ++ i){
                    SFVec3f * vec = new SFVec3f;
                    vec->x = values.at( i * 3 + 0 );
                    vec->y = values.at( i * 3 + 1 );
                    vec->z = values.at( i * 3 + 2 );
                    
                    coord->point.push_back( vec );
                }
            }
            // don't skip the end character : ]
            
        }
        // go to next property
        index += 1;
        name = list.at( index );
    }

    // don't skip the end character : }
    return coord;
}

TextureCoordinate * Parser::parseTextureCoordinate ( vector<string> & list , int & index ){
    std::cout << "* parse TextureCoordinate *" << std::endl;
    // TODO : start with TextureCoordinate , need to skip the type flag

    // skip : Type {
    index += 2;
    string name = list.at( index );
    
    TextureCoordinate * coord = new TextureCoordinate();

    while( name != "}" ){
        if( name == "point" ){
            // collect point value 
            // skip "point" & "[""
            vector<float> values = vector<float>();
            index += 2;
            name = list.at( index );
            while( name != "]"){
                float value = Parser::parseFloat(name);
                values.push_back(value);

                index += 1;
                name = list.at( index );
            }
            if(values.size() % 2 != 0){
                std::cout << "uv count is wrong" << std::endl;
            }else{
                int size = values.size();
                for(int i = 0 ; i < size / 2 ; ++ i){
                    SFVec2f * vec = new SFVec2f();
                    vec->x = values.at( i * 2 + 0 );
                    vec->y = values.at( i + 2 + 1 );

                    coord->point.push_back( vec );
                }
            }

            // don't skip the end character ]
            
        }else{
            std::cout << "!!! ERROR" << std::endl;
        }
        // go to next property
        index += 1;
        name = list.at( index );
    }

    // don't skip the end character : }
    return coord;
}

Normal * Parser::parseNormal ( vector<string> & list , int & index ){
    std::cout << "* parse Normal *" << std::endl;
    // TODO : start with Normal , need to skip the type flag
    
    // skip : Type + {
    index += 2;
    string name = list.at( index );

    Normal * normal = new Normal();
    while( name != "}" ){
        if( name == "vector" ){
            // collect point value 
            // skip "point" & "[""
            vector<float> values = vector<float>();
            index += 2;
            name = list.at( index );
            while( name != "]"){
                float value = Parser::parseFloat(name);
                values.push_back(value);

                index += 1;
                name = list.at( index );
            }
            if(values.size() % 3 != 0){
                std::cout << "normal count is wrong" << std::endl;
            }
            // don't skip the end character : ]
        }
        // go to next property
        index += 1;
        name = list.at( index );
    }
    // don't skip the end character : }
    return normal;
}

IndexedFaceSet * Parser::parseIndexedFaceSet ( vector<string> & list , int & index ){
    std::cout << "* parse IndexedFaceSet *" << std::endl;
    // TODO : start with IndexedFaceSet , need to skip the type flag
    
    // skip : Type + {
    index += 2;
    string name = list.at( index );
    IndexedFaceSet * faceSet = new IndexedFaceSet();
    while( name != "}" ){
        if( name == "solid" ){
            index += 1;
            string value = list.at( index );
            bool bValue = (value == "TRUE") ? true : false;
            faceSet->solid = SFBool( bValue );
        }else if ( name == "ccw" ){
            index += 1;
            string value = list.at( index );
            bool bValue = (value == "TRUE") ? true : false;
            faceSet->solid = SFBool( bValue );
        }else if( name == "convex" ){
            index += 1;
            string value = list.at( index );
            bool bValue = (value == "TRUE") ? true : false;
            faceSet->convex = SFBool( bValue );
        }else if(name == "coord"){
            index += 1;
            Coordinate * coord = Parser::parseCoordinate(list , index );
            faceSet->coord = coord;
        }else if( name == "texCoord" ){
            index += 1;
            TextureCoordinate * texCoord = Parser::parseTextureCoordinate( list , index );
            faceSet->texCoord = texCoord;
        }else if( name == "coordIndex" ){
            // coordIndex [
            // skip : coordIndex + [
            index += 2;
            string str = list.at( index );
            while( str != "]"){
                float value = Parser::parseInt( str );
                faceSet->coordIndex.push_back( value );

                index += 1;
                str = list.at( index );
            }
            // don't skip the end character : ]
        }else if( name == "texCoordIndex" ){
            // coordIndex [
            // skip : coordIndex + [
            index += 2;
            string str = list.at( index );
            while( str != "]"){
                float value = Parser::parseInt( str );
                faceSet->texCoordIndex.push_back( value );

                index += 1;
                str = list.at( index );
            }
            // don't skip the end character
        }
        // go to next property
        index += 1;
        name = list.at( index );
    }
    return faceSet;
}

Transform * Parser::parseTransform ( vector<string> & , int &){
    return nullptr;
}

Appearance * Parser::parseAppearance ( vector<string> & list , int & index ){
        std::cout << "* parse Appearance *" << std::endl;
    // TODO : start with Appearance , need to skip the type flag
    // skip : Type + {
    index += 2;
    string name = list.at( index );
    Appearance * appearance = new Appearance();
    while( name != "}" ){
        if( name == "material" ){
            index += 1;
            Material * material = Parser::parseMaterial( list , index );
            appearance->material = material;
        }else if( name == "texture" ){
            ImageTexture * texture = Parser::parseImageTexture( list , index );
            appearance->texture = texture;
        }else if( name == "textureTransform" ){

        }
        // go to next property
        index += 1;
        name = list.at( index );
    }

    // don't skip the end character : }
    return appearance;
}

Viewport * Parser::parseViewport ( vector<string> & list, int & index ){
    std::cout << "* parse Viewport *" << std::endl;
    // TODO : start with Viewport , need to skip the type flag
    // skip : Type + {
    index += 2;
    string name = list.at( index );
    Viewport * viewport = new Viewport();
    while( name != "}" ){
        if( name == "" ){

        }else if( name == "" ){

        }
        // do to the next property
        index += 1;
        name = list.at( index );
    }
    // don't skip the end character : }
    return viewport;
}

Shape * Parser::parseShape ( vector<string> & list , int & index ){
        std::cout << "* parse Shape *" << std::endl;
    // TODO : start with Shape , need to skip the type flag
    // skip : Type + {
    index += 2;
    string name = list.at( index );

    Shape * shape = new Shape();
    while( name != "}" ){
        if( name == "appearance" ){
            index += 1;
            Appearance * appearance = Parser::parseAppearance( list , index );
            shape->appearance = appearance;
        }else if(name == "geometry"){
            index += 1;
            IndexedFaceSet * faceSet = Parser::parseIndexedFaceSet( list , index );
            shape->geometry = faceSet;
        }
        // go to the next property
        index += 1;
        name = list.at( index );
    }
    // don't skip the end character }
    return shape;
}

Scene * Parser::parseScene( vector<string> & , int & ){
    return nullptr;
}


void Parser::parse( string fileName ){
    vector<string> list = Parser::read( fileName );

    for(int i = 0 ; i < 30 ; ++ i){
        // std::cout << list.at( i ) << std::endl;
    }
    
    int index = 0;

    Scene * scene = new Scene();
    while( index < list.size() ){
        Node * node = Parser::parseNode( list , index );
        
        switch( node->type() ){
            case VIEWPORT : {
                scene->viewport = (Viewport*)node;
            }break;

            case SHAPE : {
                scene->shape = (Shape*)node;
            }break;
        }


        // go to the next content
        index += 1;
    }
    std::cout << scene->shape->geometry->coord->point.size() << std::endl;
    std::cout << scene->shape->geometry->texCoord->point.size() << std::endl;
    std::cout << scene->shape->geometry->coordIndex.size() << std::endl;
    std::cout << scene->shape->geometry->texCoordIndex.size() << std::endl;
    delete scene;
}