#ifndef SBOOL_HPP
#define SBOOL_HPP

#include <string>

class sbool
{
private:
    bool is ;

public:
    sbool( const bool c_is = false ) : is( c_is ) {}

    bool operator == ( bool argis ) {
        return ( is == argis ) ;
    }
    bool operator != ( bool argis ) {
        return ( is != argis ) ;
    }

    friend bool operator == ( bool argis, sbool obj ) {
        return ( argis == obj.is ) ;
    }
    friend bool operator != ( bool argis, sbool obj ) {
        return ( argis != obj.is ) ;
    }

    std::string ToStr() const {
        return std::to_string( static_cast<int>( is ) ) ;
    }

    void ToTrue() {
        is = true ;
    }
    void ToFalse() {
        is = false ;
    }

    operator int() {
        return static_cast<int>( is ) ;
    }
    operator bool() {
        return is ;
    }
    operator std::string() {
        return ToStr() ;
    }
} ;


#endif
