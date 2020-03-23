#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

class Color
{
private:
    unsigned char r ;
    unsigned char g ;
    unsigned char b ;

    std::string ToHex( const unsigned char value ) const ;
public:
    explicit Color( unsigned char r_value = 0, unsigned char g_value = 0, unsigned char b_value = 0 ) ;
    explicit Color( const std::string hex ) ;


    unsigned char R() const { return r ; }
    unsigned char G() const { return g ; }
    unsigned char B() const { return b ; }

    std::string Hex() const ;

    std::string HashHex() const ;

    //格納されている色を淡くした色を返す関数
    std::string PaleHex() const ;

    bool operator == ( const Color& obj ) const {
        return ( r == obj.R() && g == obj.G() && b == obj.B() ) ;
    }
} ;

#endif