#include "wrl.h"

using namespace WRL;

const char _WHITE_SPACE_ = '\0';
const char _NEW_LINE_ = '\r';
const char _ENTER_ = '\n';
const char _TABLE_ = '\t';
const char _SPACE_ = ' ';
const char _QUOTE_ = '"';
const char _SHARP_ = '#';
const char _COMMA_ = ',';

std::vector<std::string> Parser::read( std::string fileName ){

    std::vector<std::string> list = std::vector<std::string>();
    std::ifstream file( fileName , std::ios::in );
    std::stringstream ss ;
    ss << file.rdbuf();
    std::string content = ss.str();
    file.close();

    std::string val;
    int index = 0;
    int k = 0;
    bool valid = false;
    while( index < content.size() ){
        char c = content.at( index );
        std::string val;
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

            case _COMMA_ : {

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
    // list.erase( list.end() - 1 );
    return list;   
}

std::string Parser::readString ( std::string & content , int & index , char end){
    if(end == _QUOTE_) index += 1;
    char c = content.at( index );

    std::function< bool(char , char) > assertion = []( char c , char t){

        if(t == _WHITE_SPACE_){
            return  c != _SPACE_ && 
                    c != _ENTER_ && 
                    c != _TABLE_ &&
                    c != _NEW_LINE_ &&
                    c != _COMMA_ ;
        }
        
        return c != t;
    };
    
    std::string val = "";
    while( assertion( c , end ) ){
        if(c != _NEW_LINE_ && c != _ENTER_ ) 
            val += c;
        index += 1;
        c = content.at( index );
    }
    return val;
}

int Parser::parseInt( std::string str ){
    std::stringstream ss ;
    ss << str ;
    int val ;
    ss >> val;
    return val;
}

float Parser::parseFloat( std::string str ){
    std::stringstream ss ;
    ss << str ;
    float val ;
    ss >> val;
    return val;
}

Node * Parser::parseNode( std::vector<std::string> & list, int & index, std::string type){
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
    }else if( type == "NavigationInfo" ){
        node = Parser::parseNavigationInfo( list ,index );
    }else if( type == "Transform"){
        node = Parser::parseTransform( list , index );
    }else if( type == "Shape"){
        node = Parser::parseShape( list , index );
    }else{
        node = Parser::parseNode( list , index );
    }
    return node;
}

Node * Parser::parseNode( std::vector<std::string> & list , int & index){
    // std::cout << "* parse Node *" << std::endl;

    std::string item = list.at( index );
    std::string name ;
    std::string type ;
// std::cout << item << std::endl;
    Node * node;
    while( item.at(0) == '#' ){
        index += 1;
        item = list.at( index );
    }

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

Texture * Parser::parseTexture( std::vector<std::string> & list , int & index  ){
    return nullptr;
}

Material * Parser::parseMaterial ( std::vector<std::string> & list, int & index){
    // TODO : start with Appearance , need to skip the type flag
    // skip : name Type + {
    std::cout << "* parse Viewport *" << std::endl;
    index += 3;
    std::string name = list.at( index );
    Material * material = new Material();
    while( name != "}" ){
        if(name == "ambientIntensity"){
            index += 1;
            std::string value = list.at( index );
            material->ambientIntensity = SFFloat( parseFloat( value ) );
        }else if( name == "diffuseColor" ){
            std::string xValue = list.at( index + 1 );
            std::string yValue = list.at( index + 2 );
            std::string zValue = list.at( index + 3 );

            float x = parseFloat( xValue) , y = parseFloat( yValue ) , z = parseFloat( zValue );
            index += 3;
            material->diffuseColor = SFVec3f(x , y , z);
        }else if( name == "specularColor" ){
            std::string xValue = list.at( index + 1 );
            std::string yValue = list.at( index + 2 );
            std::string zValue = list.at( index + 3 );

            float x = parseFloat( xValue) , y = parseFloat( yValue ) , z = parseFloat( zValue );
            index += 3;
            material->specularColor = SFVec3f(x , y , z);
        }else if( name == "shininess" ){
            index += 1;
            std::string value = list.at( index );
            material->shininess = SFFloat( parseFloat( value ) );
        }
        index += 1;
        name = list.at( index );
    }
    return material;
}

Group * Parser::parseGroup ( std::vector<std::string> & list , int & index){
    std::cout << "* parse Group *" << std::endl;
    // TODO : start with Group , need to skip the type flag
    // [name]Group { children [ ] ... }
    
    
    //TODO : check out if the name contain name character
    std::string name ;
    std::string type ;
    std::string str = list.at( index );

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
    std::string item = list.at( index );

    Group * group = new Group();
    while( item != "}" ){
        if(item == "children"){
            index += 1;
            std::vector<Node *> children = Parser::parseChildren( list , index );
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

std::vector<Node *> Parser::parseChildren ( std::vector<std::string> & list , int & index ){
    // TODO : start with children , need to skip the type flag
    // children [ ]
    // skip the character : children + [
    index += 2;
    std::string name = list.at( index );
    
    std::vector<Node *> children = std::vector<Node *>();

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

ImageTexture * Parser::parseImageTexture ( std::vector<std::string> & list , int & index ){
    std::cout << "* parse ImageTexture *" << std::endl;
    // TODO : start with ImageTexture , need to skip the type flag
    // ImageTexture { url path  repeatS true repeatT false }
    
    // skip : Type + {
    index += 2;
    std::string name = list.at( index );

    ImageTexture * iTex = new ImageTexture();
    while( name != "}" ){
        if(name == "url"){
            index += 1;
            std::string url = list.at( index );
            iTex->url = url;
        }else if(name == "repeatS"){
            index += 1;
            std::string repeatS = list.at( index );
        }else if(name == "repeatT"){
            index += 1;
            std::string repeatT = list.at( index );
        }
        // go to next property
        index += 1;
        name = list.at( index );
    }

    // don't skip the end character : }
    return iTex;
}

Coordinate * Parser::parseCoordinate ( std::vector<std::string> & list , int & index ){
    std::cout << "* parse Coordinate *" << std::endl;
    // TODO : start with Coordinate , need to skip the type flag
    

    // skip : Type + {
    index += 2;
    std::string name = list.at( index );

    Coordinate * coord = new Coordinate();
    while( name != "}" ){
        if( name == "point" ){
            // collect point value 
            // skip "point" & "[""
            std::vector<float> values = std::vector<float>();
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

TextureCoordinate * Parser::parseTextureCoordinate ( std::vector<std::string> & list , int & index ){
    std::cout << "* parse TextureCoordinate *" << std::endl;
    // TODO : start with TextureCoordinate , need to skip the type flag

    // skip : Type {
    index += 2;
    std::string name = list.at( index );
    
    TextureCoordinate * coord = new TextureCoordinate();

    while( name != "}" ){
        if( name == "point" ){
            // collect point value 
            // skip "point" & "[""
            std::vector<float> values = std::vector<float>();
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
                    vec->y = values.at( i * 2 + 1 );

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

Normal * Parser::parseNormal ( std::vector<std::string> & list , int & index ){
    std::cout << "* parse Normal *" << std::endl;
    // TODO : start with Normal , need to skip the type flag
    
    // skip : Type + {
    index += 2;
    std::string name = list.at( index );

    Normal * normal = new Normal();
    while( name != "}" ){
        if( name == "std::vector" ){
            // collect point value 
            // skip "point" & "[""
            std::vector<float> values = std::vector<float>();
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

IndexedFaceSet * Parser::parseIndexedFaceSet ( std::vector<std::string> & list , int & index ){
    std::cout << "* parse IndexedFaceSet *" << std::endl;
    // TODO : start with IndexedFaceSet , need to skip the type flag
    
    // skip : Type + {
    index += 2;
    std::string name = list.at( index );
    IndexedFaceSet * faceSet = new IndexedFaceSet();
    while( name != "}" ){

        if( name == "solid" ){
            index += 1;
            std::string value = list.at( index );
            bool bValue = (value == "TRUE") ? true : false;
            faceSet->solid = SFBool( bValue );
        }else if ( name == "ccw" ){
            index += 1;
            std::string value = list.at( index );
            bool bValue = (value == "TRUE") ? true : false;
            faceSet->solid = SFBool( bValue );
        }else if( name == "convex" ){
            index += 1;
            std::string value = list.at( index );
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
            int i = 0;
            index += 2;
            std::string str = list.at( index );
            while( str != "]"){
                float value = Parser::parseInt( str );
                if(value != -1)
                    faceSet->coordIndex.push_back( value );

                index += 1;
                str = list.at( index );
            }
            // don't skip the end character : ]
        }else if( name == "texCoordIndex" ){
            // coordIndex [
            // skip : coordIndex + [
            index += 2;
            std::string str = list.at( index );
            while( str != "]"){
                float value = Parser::parseInt( str );
                if(value != -1)
                    faceSet->texCoordIndex.push_back( value );

                index += 1;
                str = list.at( index );
            }
            // don't skip the end character
        }else if( name == "creaseAngle" ){
            index += 1;
            std::string value = list.at( index );
            float fValue = parseFloat( value );
            faceSet->creaseAngle = SFFloat( fValue );
        }

        // go to next property
        index += 1;
        name = list.at( index );

    }
    
    return faceSet;
}

Transform * Parser::parseTransform ( std::vector<std::string> & list, int & index){
    std::cout << "* parse Transform *" << std::endl;
    // TODO : start with Transform , need to skip the type flag
    // Type + {

    index += 2;
    std::string name = list.at( index );

    Transform * transform = new Transform();
    while( name != "}" ){
        if( name == "scale"){
            float x = parseFloat( list.at( index + 1) );
            float y = parseFloat( list.at( index + 2) );
            float z = parseFloat( list.at( index + 3) );
            transform->scale = new SFVec3f( x, y , z);
            index += 3;
        }else if (name == "translation"){
            float x = parseFloat( list.at( index + 1) );
            float y = parseFloat( list.at( index + 2) );
            float z = parseFloat( list.at( index + 3) );
            transform->translation = new SFVec3f(x,y,z);
            index += 3;
        }else if( name == "children" ){
            std::vector< Node * > children = Parser::parseChildren( list , index );
            transform->children = children;
        }
        index += 1;
        name = list.at( index );
    }
    return transform;
}

Appearance * Parser::parseAppearance ( std::vector<std::string> & list , int & index ){
        std::cout << "* parse Appearance *" << std::endl;
    // TODO : start with Appearance , need to skip the type flag
    // skip : Type + {
    index += 2;
    std::string name = list.at( index );
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

Viewport * Parser::parseViewport ( std::vector<std::string> & list, int & index ){
    std::cout << "* parse Viewport *" << std::endl;
    // TODO : start with Viewport , need to skip the type flag
    // skip : Type + {
    index += 2;
    std::string name = list.at( index );
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

Shape * Parser::parseShape ( std::vector<std::string> & list , int & index ){
    std::cout << "* parse Shape *" << std::endl;
    // TODO : start with Shape , need to skip the type flag
    // skip : Type + {
    index += 2;
    std::string name = list.at( index );

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

Scene * Parser::parseScene( std::vector<std::string> & , int & ){
    return nullptr;
}

NavigationInfo * Parser::parseNavigationInfo( std::vector< std::string > & list , int & index ){
    std::cout << "* parse NavigationInfo *" << std::endl;
    // TODO : start with Appearance , need to skip the type flag
    // skip : Type + {

    index += 2;
    std::string name = list.at( index );
    NavigationInfo * info = new NavigationInfo();
    while( name != "}" ){
        if( name == "type" ){

        }else {

        }
        index += 1;
        name = list.at( index );
    }
    return info;
}

Scene* Parser::parse( std::string fileName ){
    std::vector<std::string> list = Parser::read( fileName );

    int index = 0;
    Scene * scene = new Scene();
    while( index < list.size() ){
        Node * node = Parser::parseNode( list , index );
        
        switch( node->type() ){

            case VIEWPORT : {
                scene->viewport = (Viewport*)node;
            }break;

            case NAVIGATIONINFO : {
                scene->info = (NavigationInfo *)node;
            }break;

            case TRANSFORM : {
                scene->transform = (Transform *)node;
            }break;

            case SHAPE : {
                scene->shape = (Shape*)node;
            }break;

        }

        // go to the next property
        index += 1;
    }

    // // write to file
    // std::cout << scene->shape->geometry->coord->point.size() << std::endl;
    // // write to file
    // std::cout << scene->shape->geometry->texCoord->point.size() << std::endl;
    // // write to file
    // std::cout << scene->shape->geometry->coordIndex.size() << std::endl;
    // // write to file
    // std::cout << scene->shape->geometry->texCoordIndex.size() << std::endl;

    return scene;
}

void Parser::store( std::string fileName, Scene * scene){
    std::ofstream file( fileName );
    
    IndexedFaceSet * faceSet = scene->shape->geometry;
    std::vector<SFVec3f *> coord = faceSet->coord->point ;
    std::vector<SFVec2f *> texCoord = faceSet->texCoord->point;
    std::vector<SFInt> coordIndex = faceSet->coordIndex;
    std::vector<SFInt> texCoordIndex = faceSet->texCoordIndex;

    std::cout << coord.size() << std::endl;
    std::cout << texCoord.size() << std::endl;
    std::cout << coordIndex.size() << std::endl;
    std::cout << texCoordIndex.size() << std::endl;

    // write coord
    file << "#coord" << std::endl;
    for(int i = 0 ; i < coord.size() ; ++ i){
        SFVec3f * vec = coord.at( i );
        std::string line = std::to_string( vec->x ) + " " + std::to_string( vec->y ) + " " + std::to_string( vec->z );
        file << line << std::endl;
    }
    
    file << "#texCoord" << std::endl;

    // write texCoord
    for(int i = 0 ; i < texCoord.size() ; ++ i){
        SFVec2f * vec = texCoord.at( i );
        std::string line = std::to_string( vec->x ) + " " + std::to_string( vec->y );
        file << line << std::endl;
    }

    file << "#coordIndex" << std::endl;

    // write coordIndex
    for(int i = 0 ; i < coordIndex.size() ; ++ i){
        SFInt value = coordIndex.at( i );
        file << std::to_string( value.val ) << std::endl;
    }
    
    file << "#texCoordIndex" << std::endl;
    
    // write texCoordIndex
    for(int i = 0 ; i < texCoordIndex.size() ; ++ i){
        SFInt value = texCoordIndex.at( i );
        file << std::to_string( value.val ) << std::endl;
    }

    file.close();
}
