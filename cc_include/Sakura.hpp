#ifndef SAKURA_HPP
#define SAKURA_HPP

#include "TextEditor.hpp"

class Sakura : public TextEditor
{
private:
    static const std::string ItemCCX ;

public:
    Sakura() ;

    void Save( std::string file_name ) override ;
    void Load( std::string file_name ) override ;
} ;
#endif //SAKURA_HPP