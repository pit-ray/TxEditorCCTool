#ifndef TEXTEDITOR_HPP
#define TEXTEDITOR_HPP

#include "Color.hpp"
#include "sbool.hpp"
#include "Item.hpp"
#include "ccx_parser.hpp"
#include "enum_array.hpp"
#include "constants.hpp"

#include "../lib/tinyxml2.h"

#include <utility>
#include <map>
#include <string>
#include <vector>
#include <exception>

using color_map_t = enum_array<CCItems, std::map<CCLangs, Item<Color>>> ;
using opt_map_t = enum_array<CCOpts, std::map<CCItems, std::map<CCLangs, Item<sbool>>>> ;

//TextEditorオブジェクトを生成する順番によって、InputかOutputか判別する。
//最初に作ったオブジェクトはInput
//2個目以降は、上書きされる形で、いくらでも生成できる。
class TextEditor : public CCXParser
{
private:
    static const std::map<CCLangs, std::string> to_langname ;

    static bool first_flag ;
    static bool second_flag ;

    void ParseItemTag( const CCLangs lang_index, tinyxml2::XMLElement* first_item_elem = nullptr ) ;
    void ClearOutputItem() ;

    template <typename data_t>
    void ClearOName( std::map<CCLangs, Item<data_t>>& lang_map ) {

        for( auto& i_lang : lang_map ) {
            auto& item_r = i_lang.second ;

            //出力項目名があるときは、｛出力固有の項目｝または｛入出力共通の項目｝のどちらか
            if( item_r.OName().empty() ) return ;

            if( item_r.IName().empty() ) {
                //出力固有の項目
                //要素の削除
                lang_map.erase( i_lang.first ) ;
            }
            else {
                //入出力共通の項目
                //項目名だけ消す
                item_r.SetOName( std::string( "" ) ) ;
            }
        }
    }

public:
    //データ群
    static color_map_t color ;
    static opt_map_t option ;

    static std::vector<CCLangs> output_file_type ;

    //項目名→{言語index, 項目index} 主に読み込み時に用いる。
    std::map<std::string, std::pair<CCLangs, std::vector<CCItems>>> name_to_enum ;
    std::map<std::string, Color> color_code ;

    std::map<CCItems, ColorType> text_ct ;
    std::map<CCItems, ColorType> back_ct ;

    void InitColorCode( const std::string file_name ) ;

    void InitItemName( const std::string file_name ) ;
    void CorrectExtension( std::string& file_name, const std::string dot_extension ) ;

    const Color GetAppropriateInputColor( const CCItems& item_index, const CCLangs& output_lang_index ) const {
        //以下の優先度に従い、データを取り出す
        //1.同じインデックス
        //2.COMMON
        //3.他の言語
        const auto& item_map = color[item_index] ;
        //ポインタは非const, データはconst
        const Item<Color>* p_item = nullptr ;

        try {
            p_item = &item_map.at( output_lang_index ) ;
        }
        catch( std::out_of_range& ) {
            //指定された言語が存在しない場合は、mapの先頭要素を代わりに入れる
            p_item = &item_map.begin()->second ;
        }

        if( p_item == nullptr ) return Color() ;

        if( p_item->IsInputed() ) {
            return p_item->Data() ;
        }

        if( const auto& common_item = item_map.at( CCLangs::COMMON ) ; common_item.IsInputed() ) {
            return common_item.Data() ;
        }

        for( const auto& i_item : item_map ) {
            if( !i_item.second.IsInputed() ) continue ;
            return i_item.second.Data() ;
        }

        return Color() ;
    }

    const std::string ToLangName( const CCLangs index ) const noexcept ;

    explicit TextEditor() ;
    virtual void Save( const std::string file_name ) {}
    virtual void Load( const std::string file_name ) {}

    TextEditor& operator = ( const TextEditor& ) = delete ;

    /*
     * 仮想デストラクタにしないと、
     * 派生クラスのアドレスを保持したこのクラスのポインタが
     * deleteされるとき、抽象クラス（基本クラス）のアドレスだけ解放される場合があり、
     * 動作が未定義になる可能性がある。
     * 
     * また、派生クラスのデストラクタにて、基本クラスのデストラクタが呼び出されるので、定義は必要。
     */
    virtual ~TextEditor() {} ;
} ;

#endif //TEXTEDITOR_HPP