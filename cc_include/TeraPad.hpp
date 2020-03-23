#ifndef TERAPAD_HPP
#define TERAPAD_HPP

#include "TextEditor.hpp"

class TeraPad : public TextEditor
{
private:
    static const std::string ItemCCX ;
    static const std::string CodeCCX ;

public:
    TeraPad() ;

    void Save( std::string file_name ) override ;
    void Load( std::string file_name ) override ;

    TeraPad& operator = ( const TeraPad& ) = delete ;
} ;

#endif //TERAPAD_HPP
