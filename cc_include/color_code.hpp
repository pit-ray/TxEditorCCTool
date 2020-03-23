#ifndef COLOR_CODE_HPP
#define COLOR_CODE_HPP

#include "tinyxml2.h"

#include "color.hpp"

#include <string>
#include <map>
#include <utility>

//色コードを扱う場合、継承する
class ColorCode
{
public:
    //<色コード, 16進数カラー値(#なし)>
    using colorcode_map_t = std::map<std::string, Color> ;

private:
    colorcode_map_t colorcode_map ;

public:

    void LoadColorCodeXML( const std::string filename ) 
    {
        tinyxml2::XMLDocument doc ;
        doc.LoadFile( filename.c_str() ) ;
        auto root = doc.FirstChildElement( "ColorCode" ) ;

        for( auto i_code = root->FirstChildElement( "Code" ) ;
            i_code != nullptr ;
            i_code = i_code->NextSiblingElement( "Code" ) ) {

            //name属性がそんざいしないばあいは　、次のループへ
            const auto name_str_c = i_code->Attribute( "name" ) ;
            if( name_str_c == nullptr ) {
                continue ;
            }
            std::string code_s = name_str_c ;

            //テキストが記載されていない場合は、 colorのコンストラクタのデフォルト値を用いる。
            const auto code_str_c = i_code->GetText() ;
            Color color ;
            if( code_str_c != nullptr ) {
                color = Color( std::string( code_str_c ) ) ;
            }

            colorcode_map.insert( std::make_pair( code_s, color ) ) ;
        }
    }
    Color CodeToColor( const std::string colorcode ) const {
        return colorcode_map.at( colorcode ) ;
    }
} ;
#endif
