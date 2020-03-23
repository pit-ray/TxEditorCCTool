#include "../cc_include/current_path.hpp"
    
#include <iostream>
using namespace std ;

void CurrentPath::EraseCommandName( const char* argv_0 ) {
    str = argv_0 ;

    for( const auto& it, str.find( '\\' ) ) {

    }
    auto pos = str.find_last_of( '/' ) ;
    if( pos == std::string::npos ) {
        pos = str.find_last_of( '\\' ) ;
    }
    
    str.erase( pos + 1 ) ;
    str.replace( '\\', '/' ) ;

    cout << str << endl ;
}