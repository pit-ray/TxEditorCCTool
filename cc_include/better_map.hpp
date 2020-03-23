#ifndef BETTER_MAP_HPP
#define BETTER_MAP_HPP

#include <map>

template <typename Key, typename T>
class better_map : public std::map<Key, T>
{
public:
    //コンストラクタはmapのものを流用する。

    const T& create_noexist( const Key& key ) const noexcept {
        if( this->find( key ) == this->end() ) {
            this->insert
        }
    }

} ;

#endif //BETTER_MAP_HPP