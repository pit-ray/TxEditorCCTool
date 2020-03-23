#include "../cc_include/Color.hpp"

#include <sstream>
#include <cmath>
#include <cstdlib>
using namespace std ;

Color::Color( unsigned char r_value, unsigned char g_value, unsigned char b_value ) :
    r( r_value ),
    g( g_value ),
    b( b_value )
{}


Color::Color( string hex )
{
    if( hex.front() == '#' ) {
        hex.erase( 0, 1 ) ;
    }
    
    if( hex.length() == 6 ) {
        auto r_hex = hex.substr( 0, 2 ) ;
        auto g_hex = hex.substr( 2, 2 ) ;
        auto b_hex = hex.substr( 4, 2 ) ;
        r = static_cast<unsigned char>( strtol( r_hex.c_str(), nullptr, 16 ) ) ;
        g = static_cast<unsigned char>( strtol( g_hex.c_str(), nullptr, 16 ) ) ;
        b = static_cast<unsigned char>( strtol( b_hex.c_str(), nullptr, 16 ) ) ;
        return ;
    }

    //デフォルト引数で初期化
    Color() ;
}

string Color::ToHex( const unsigned char value ) const
{
    stringstream ss ;

    //unsigned char型をそのままストリームに入れると、文字として入力されてしまうので、
    //intにキャストすることで、文字コードとしてストリームに通す。
    ss << std::hex << static_cast<int>( value ) ;

    string hex_str = ss.str() ;

    //0の場合は1桁になってしまう
    if( value == 0 ) {
        hex_str = "0" + hex_str ;
    }

    return hex_str ;
}

string Color::Hex() const
{
    //メンバ変数r,g,bは、0から255までの値であることが保証されている。
    return( ToHex( r ) + ToHex( g ) + ToHex( b ) ) ;
}

string Color::HashHex() const
{
    return ( "#" + Hex() ) ;
}

string Color::PaleHex() const
{
    //加算して、オーバーフローした場合を考慮してint型を用いる
    const int pale = 204 ;

    const auto added_r = static_cast<int>( r ) + pale ;
    const auto added_g = static_cast<int>( g ) + pale ;
    const auto added_b = static_cast<int>( b ) + pale ;

    const auto vr = static_cast<unsigned char>( ( added_r > 255 ) ? 255 : added_r ) ;
    const auto vg = static_cast<unsigned char>( ( added_g > 255 ) ? 255 : added_g ) ;
    const auto vb = static_cast<unsigned char>( ( added_b > 255 ) ? 255 : added_b ) ;

    return ( ToHex( vr ) + ToHex( vg ) + ToHex( vb ) ) ;
}