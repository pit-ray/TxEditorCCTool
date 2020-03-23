#include "../cc_include/ccio.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std ;
ccio::ccio() :
    CCXParser(),
    color(),
    option(),
    name_to_enum(),
    color_code()
{}

//サクラエディタ
void ccio::Save_Sakura( const string file_name )
{
}

void ccio::Load_Sakura( const string file_name )
{
}