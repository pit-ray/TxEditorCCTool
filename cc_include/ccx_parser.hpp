#ifndef CCX_PARSER_HPP
#define CCX_PARSER_HPP

#include "constants.hpp"
#include <map>
#include <string>

class CCXParser
{
private:
    static const std::map<std::string, CCItems> to_ccitems ;
    static const std::map<CCOpts, std::string>  to_ccopts ;
    static const std::map<std::string, CCLangs> to_cclangs ;
    static const std::map<std::string, ColorType> color_type ;

public:
    const CCItems ToCCItems( const std::string name ) const noexcept ;
    const std::string CCOptsTo( const CCOpts index ) const noexcept ;
    const CCLangs ToCCLangs( const std::string name ) const noexcept ;
    const ColorType ToColorType( const std::string name ) const noexcept ;

    CCXParser() = default ;
    CCXParser( const CCXParser& ) = delete ;
    CCXParser& operator = ( const CCXParser& ) = delete ;

} ;

#endif // CCX_PARSER_HPP
