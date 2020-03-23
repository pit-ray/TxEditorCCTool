#ifndef ITEM_HPP
#define ITEM_HPP

#include "color.hpp"
#include "enum_array.hpp"

#include <string>

template <typename data_t>
class Item
{
private:
    data_t      data ;
    std::string i_name ;
    std::string o_name ;
    bool inputed_flag ;

public:
    explicit Item( const data_t& data_obj = data_t() ) :
        data( data_obj ),
        i_name( "" ),
        o_name( "" ),
        inputed_flag( false )
    {}

    void SetData( const data_t& data_obj ) {
        data = data_obj ;
    }
    const data_t Data() const {
        return data ;
    }

    void SetIName( const std::string& item_name ) {
        i_name = item_name ;
        inputed_flag = true ;
    }
    void SetOName( const std::string& item_name ) {
        o_name = item_name ;
    }

    const std::string IName() const {
        return i_name ;
    }
    const std::string OName() const {
        return o_name ;
    }

    //共通項目かどうか確かめるために用いる。
    const bool IsInputed() const {
        return inputed_flag ;
    }

    bool operator == ( const Item<data_t>& obj ) const {
        return ( i_name == obj.i_name &&
                 o_name == obj.o_name &&
                 data == obj.data ) ;
    }

    Item<data_t>& operator = ( const Item<data_t>& rhs ) {
        this->data          = rhs.data ;
        this->i_name        = rhs.i_name ;
        this->o_name        = rhs.o_name ;
        this->inputed_flag  = rhs.inputed_flag ;

        return *this ;
    }
} ;
#endif