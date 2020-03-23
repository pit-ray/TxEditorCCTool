#ifndef ENUMITEM_HPP
#define ENUMITEM_HPP

#include "item.hpp"

#include <map>
#include <string>
#include <vector>

template <typename Enum_t>
using item_init_t = std::map<Enum_t, std::string> ;

/*
ItemClassをEnumと対応させたデータ構造を扱えるクラス。
つまり、EnumからItemClassを呼び出せるので、範囲forで回すことができ、便利。
*/
template <typename Enum_t, typename Data_t>
class EnumItem
{
private:
    using data_obj_t = Item<Data_t> ;
    using item_map_t = std::map<Enum_t, data_obj_t> ;
    using name_map_t = std::map<std::string, Enum_t> ;

    item_map_t item ;
    name_map_t name ; //項目名->enumの変換用map

public:
    explicit EnumItem(){}
    void InitItem( item_init_t<Enum_t> enum_name_map ) {
        for( auto i_item : enum_name_map ) {
            auto item_enum = i_item.first ;
            auto item_name = i_item.second ;

            //簡易のプログラムを作り出すしかない。
            item.insert( std::make_pair( item_enum, data_obj_t( item_name ) ) ) ;

            name.insert( std::make_pair( item_name, item_enum ) ) ;
        }
    }

    //at関数で参照しないと、存在しないindexで参照した場合、新たに作成されてしまう。
    data_obj_t& operator [] ( const Enum_t index ) {
        return item.at( index ) ;
    }
    const data_obj_t operator [] ( const Enum_t index ) const {
        return item.at( index ) ;

    }

    //初期化時に登録した項目名が存在するかどうか。存在するときはtrue, 存在しない場合はfalseを返す。
    bool ExistItemName( const std::string item_name ) const {
        if( name.find( item_name ) != name.end() ) {
            return true ;
        }
        return false ;
    }

    /*初期化時にmapのsecond値として渡した、項目名から
      列挙型のインデックス番号を返す関数。

      存在しない場合は、(-1)を返す。
    */
    Enum_t NameToEnum( const std::string item_name ) const {
        if( ExistItemName( item_name ) ) {
            return name.at( item_name ) ;
        }
        return static_cast<Enum_t>( -1 ) ;
    }

    auto begin() {
        return item.begin() ;
    }

    auto end() {
        return item.end() ;
    }

    //このクラスは代入による変更を禁止する
    EnumItem& operator = ( const EnumItem& ) = delete ;
} ;

#endif
