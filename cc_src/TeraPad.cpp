#include "../cc_include/TeraPad.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <algorithm>
#include <iostream>

using namespace std ;

const string TeraPad::ItemCCX = "resrc/item/TeraPad.ccx" ;
const string TeraPad::CodeCCX = "resrc/color_code/TeraPad.ccx" ;

TeraPad::TeraPad()
{
    InitItemName( ItemCCX ) ;
}
void TeraPad::Save( string file_name )
{
    boost::property_tree::ptree pt ;

    const string sect_name( "Color" ) ;

    boost::property_tree::ptree info ;
    for( const auto& item_index : CCItems() ) {
        for( const auto& i_pair : color[item_index] ) {
            const auto& lang_index = i_pair.first ;
            const auto& item_color = i_pair.second ;

            if( item_color.OName().empty() ) continue ;

            const auto& inputed_color = GetAppropriateInputColor( item_index, lang_index ) ;

            info.put( item_color.OName(), "$00" + inputed_color.Hex() ) ;

            //lang_indexは、colorから取得しているので、オプションがない場合は、スキップする。
            try {
                //オプションはオフがデフォルトなので、なかった場合はなにもしなくてもよい
                const auto& bold_opt = option[CCOpts::BOLD].at( item_index ).at( lang_index ) ;
                if( bold_opt.OName().empty() ) continue ;

                const auto& case_opt = option[CCOpts::CASE].at( item_index ).at( lang_index ) ;
                info.put( bold_opt.OName(), bold_opt.Data().ToStr() ) ;
                info.put( case_opt.OName(), case_opt.Data().ToStr() ) ;
            }
            catch( out_of_range& ) {
                continue ;
            }
        }
    }

    pt.add_child( sect_name, info ) ;

    CorrectExtension( file_name, ".tpc" ) ;

    try { boost::property_tree::ini_parser::write_ini( file_name, pt ) ; }
    catch( boost::property_tree::ini_parser_error& e ) {
        cout << e.what() << endl ;
        return ;
    }
    catch( boost::property_tree::ptree_bad_path& e ) {
        cout << e.what() << endl ;
        return ;
    }
}

void TeraPad::Load( string file_name )
{
    //TeraPad特有のカラーコードのリストを読み込む
    InitColorCode( CodeCCX ) ;
    CorrectExtension( file_name, ".tpc" ) ;

    try {
        boost::property_tree::ptree pt ;
        boost::property_tree::ini_parser::read_ini( file_name, pt ) ;

        for( const auto& i_key : pt.get_child( "Color" ) ) {
                const auto& key = static_cast<string>( i_key.first ) ;

            try {
                auto value = i_key.second.get_value<string>() ;

                //enum_arrayを回し、その項目名が該当するEnumItemを見つける。
                //そのうえで、CCLangsとCCItemsの番号を得る。
                const auto& lang_index = name_to_enum[key].first ;
                const auto& item_index_vec = name_to_enum[key].second ;

                //値の先頭が$のときは、16真数のRGB値を示している。
                if( value.front() == '$' ) {
                    value.erase( 0, 3 ) ;
                    for( const auto& item_index : item_index_vec ) {
                        color[item_index].at( lang_index ).SetData( Color( value ) ) ;
                    }
                    continue ;
                }

                //値が0か1のときは、オプションのbool値である。
                if( value == "1" || value == "0" ) {
                    bool is ;
                    if( value == "1" ) {
                        is = true ;
                    }
                    else {
                        is = false ;
                    }

                    //存在しなかった場合はout_of_range例外を発生させる。
                    for( const auto& item_index : item_index_vec ) {
                        //項目名が一致するオプションを探す
                        for( const auto& opt_index : { CCOpts::BOLD, CCOpts::CASE } ) {
                            auto& r_opt = option[opt_index].at( item_index ).at( lang_index ) ;
                            if( key != r_opt.IName() ) continue ;

                            r_opt.SetData( sbool( is ) ) ;
                        }
                    }
                    continue ;
                }

                //上記のifに当てはまらないものは、テキストエディター特有のカラーコードを用いている
                auto temp_color = color_code.at( value ) ;

                for( const auto& item_index : item_index_vec ) {
                    color[item_index].at( lang_index ).SetData( temp_color ) ;
                }
            }
            catch( out_of_range& e ) {
                cout << "<TeraPad::Load> " << e.what() << " out_of_range exception" ;
                cout << " key : " << key << endl ;
                continue ;
            }
        }
    }
    //boost関係の例外処理
    catch( boost::property_tree::ini_parser_error& e ) {
        cout << e.what() << endl ;
        return ;
    }
    catch( boost::property_tree::ptree_bad_path& e ) {
        cout << e.what() << endl ;
        return ;
    }
}
