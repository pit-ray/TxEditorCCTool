#ifndef ENUM_ARRAY_HPP
#define ENUM_ARRAY_HPP

#include <iterator>
#include <array>
#include <algorithm>

/*C++11にて追加されたenum classを
std::arrayのインデックスとして扱うためのクラス。

enum class側の条件としては、
列挙型::size
を登録すること。
*/

template <typename enum_t, typename data_t>
class enum_array
{
private:
    std::array<data_t, static_cast<std::size_t>( enum_t::size )> ar ;

public:
    const data_t& operator [] ( const enum_t index ) const {
        return ar.at( static_cast<std::size_t>( index ) ) ;
    }
    data_t& operator [] ( const enum_t index ) {
        return ar.at( static_cast<std::size_t>( index ) ) ;
    }


    auto begin() noexcept {
        return ar.begin() ;
    }

    auto end() noexcept {
        return ar.end() ;
    }

    enum_t Index( const data_t it_data ) {
        auto it = std::find( ar.begin(), ar.end(), it_data ) ;
        if( it == ar.end() ) return enum_t::error ;

        std::size_t index = std::distance( ar.begin(), it ) ;
        return static_cast<enum_t>( index ) ;
    }

    bool operator == ( const enum_array<enum_t, data_t> obj ) const {
        return ( ar == obj.ar ) ;
    }

} ;

#endif