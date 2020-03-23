#ifndef MY_OFSTREAM_HPP
#define MY_OFSTREAM_HPP
#include <fstream>

namespace fstream_encode {
    void utf8_to_utf8bom( std::ofstream& rhs ) ;
    void utf8bom_to_utf8( std::ifstream& rhs ) ;
} ;

void fstream_encode::utf8_to_utf8bom( std::ofstream& rhs )
{
    static unsigned char bom[] = { 0xEF, 0xBB, 0xBF } ;
    rhs.write( reinterpret_cast<char*>( bom ), sizeof( bom ) ) ;
}

void fstream_encode::utf8bom_to_utf8( std::ifstream& rhs )
{
    static unsigned char bom[] = { 0xEF, 0xBB, 0xBF } ;
    unsigned char buffer ;

    for( const auto& b : bom ) {
        rhs.read( reinterpret_cast<char*>( &buffer ), sizeof( buffer ) ) ;
        if( buffer == b ) {
            continue ;
        }
        else {
            rhs.seekg( 0 ) ;
            return ;
        }
    }
}


#endif