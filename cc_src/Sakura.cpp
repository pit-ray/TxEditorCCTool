#include "../cc_include/Sakura.hpp"
#include "../cc_include/fstream_encode.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>

using namespace std ;

const string Sakura::ItemCCX = "resrc/item/Sakura.ccx" ;

Sakura::Sakura()
{
    InitItemName( ItemCCX ) ;
}

void Sakura::Save( string file_name )
{
    for( auto lang_index : output_file_type ) {

        const auto& text_main_color = GetAppropriateInputColor( CCItems::TEXT, lang_index ) ;
        const auto& text_sub_color  = GetAppropriateInputColor( CCItems::BACK, lang_index ) ;
        const auto& back_main_color = GetAppropriateInputColor( CCItems::BACK, lang_index ) ;
        const auto& back_sub_color  = GetAppropriateInputColor( CCItems::EVEN_LINE_BACK, lang_index ) ;

        auto unique_file_name = file_name ;

        //拡張子を外す
        CorrectExtension( unique_file_name, "" ) ;
        unique_file_name += "_" + ToLangName( lang_index ) ;
        CorrectExtension( unique_file_name, ".col" ) ;

        //サクラエディタは1行目にコメントを必要とするので、fstreamを用いる
        ofstream ofs( unique_file_name ) ;

        //さくらエディタは、bom付きUTF-8を用いる
        fstream_encode::utf8_to_utf8bom( ofs ) ;

        ofs << "; テキストエディタ色設定 Ver3" << endl << endl ;
        ofs << "[SakuraColor]" << endl ;

        for( const auto& item_index : CCItems() ) {
            Item<Color> item_color ;
            try {
                item_color = color[item_index].at( lang_index ) ;
            }
            catch( out_of_range& ) {
                //項目が他言語、特有のものならば、その言語のものを使う
                item_color = color[item_index].begin()->second ;
            }

            if( item_color.OName().empty() ) continue ;
            array<string, 5> put_str ;

            //サクラエディタは、文字色と背景色が分かれているので、どの色を使うのかタイプを用いて決める
            ColorType text_color_type, back_color_type ;
            try { text_color_type = text_ct.at( item_index ) ; }
            catch( out_of_range& ) {
                text_color_type = ColorType::MAIN ;
            }
            try { back_color_type = back_ct.at( item_index ) ; }
            catch( out_of_range& ) {
                back_color_type = ColorType::MAIN ;
            }

            auto coloraa = color[CCItems::KEYWORD1][CCLangs::CPP] ;

            switch( text_color_type ) {
                case ColorType::NONE:
                    put_str[2] = "000000" ;
                    break ;
                case ColorType::OWN:
                    put_str[2] = GetAppropriateInputColor( item_index, lang_index).Hex() ;
                    break ;
                case ColorType::MAIN:
                    put_str[2] = text_main_color.Hex() ;
                    break ;
                case ColorType::SUB:
                    put_str[2] = text_sub_color.Hex() ;
                    break ;
                case ColorType::PALE:
                    put_str[2] = item_color.Data().PaleHex() ;
                    break ;
                default:
                    put_str[2] = item_color.Data().Hex() ;
                    break ;
            }

            switch( back_color_type ) {
                case ColorType::NONE:
                    put_str[3] = "000000" ;
                    break ;
                case ColorType::OWN:
                    put_str[3] = GetAppropriateInputColor( item_index, lang_index ).Hex() ;
                    break ;
                case ColorType::MAIN:
                    put_str[3] = back_main_color.Hex() ;
                    break ;
                case ColorType::SUB:
                    put_str[3] = back_sub_color.Hex() ;
                    break ;
                case ColorType::PALE:
                    put_str[3] = item_color.Data().PaleHex() ;
                    break ;
                default:
                    put_str[3] = item_color.Data().Hex() ;
                    break ;
            }

            try { put_str[0] = option[CCOpts::SHOW].at( item_index ).at( lang_index ).Data().ToStr() ; }
            catch( out_of_range& ) { put_str[0] = "0" ; }

            try { put_str[1] = option[CCOpts::BOLD].at( item_index ).at( lang_index ).Data().ToStr() ; }
            catch( out_of_range& ) { put_str[1] = "0" ; }

            try { put_str[4] = option[CCOpts::UNDER].at( item_index ).at( lang_index ).Data().ToStr() ; }
            catch( out_of_range& ) { put_str[4] = "0" ; }

            string put_value ;
            for( size_t i = 0 ; i < put_str.size() ; i ++ ) {
                put_value += put_str[i] ;

                if( i != ( put_str.size() - 1 ) ) put_value += "," ;
            }

            ofs << item_color.OName() << "=" << put_value << endl ;
        }
    }
}

void Sakura::Load( string file_name )
{
    CorrectExtension( file_name, ".col" ) ;
    try {
        boost::property_tree::ptree pt ;
        ifstream ifs( file_name, std::ios::in ) ;
        fstream_encode::utf8bom_to_utf8( ifs ) ;
        boost::property_tree::ini_parser::read_ini( ifs, pt ) ;

        for( const auto& i_key : pt.get_child( "SakuraColor" ) ) {
            const auto& key = static_cast<string>( i_key.first ) ;
            auto value = i_key.second.get_value<string>() ;

            try {
                const auto& item_index_vec = name_to_enum[key].second ;

                //要素数が5であることは保証されている
                vector<string> splited_val ;
                boost::split( splited_val, value, boost::is_any_of( "," ) ) ;

                bool show_flag = ( splited_val[0] == "1" ) ? true : false ;
                bool bold_flag = ( splited_val[1] == "1" ) ? true : false ;
                bool under_flag = ( splited_val[4] == "1" ) ? true : false ;

                for( const auto& item_index : item_index_vec ) {
                    for( const auto& lang_index : CCLangs() ) {
                        auto& citem_r = color[item_index].at( lang_index ) ;
                        bool is_own_text_ct, is_own_back_ct ;

                        try { is_own_text_ct = ( text_ct.at( item_index ) == ColorType::OWN ) ; }
                        catch( out_of_range& ) {
                            is_own_text_ct = false ;
                        }
                        try { is_own_back_ct = ( back_ct.at( item_index ) == ColorType::OWN ) ; }
                        catch( out_of_range& ) {
                            is_own_back_ct = false ;
                        }

                        if( is_own_text_ct && !is_own_back_ct ) {
                            citem_r.SetData( Color( splited_val[2] ) ) ;
                        }
                        if( !is_own_text_ct && is_own_back_ct ) {
                            citem_r.SetData( Color( splited_val[3] ) ) ;
                        }

                        //予め、ccxファイルから読み込んだリストにないオプションは、スキップする。
                        try { option[CCOpts::SHOW].at( item_index ).at( lang_index ).SetData( show_flag ) ; }
                        catch( out_of_range& ) {}

                        try { option[CCOpts::BOLD].at( item_index ).at( lang_index ).SetData( bold_flag ) ; }
                        catch( out_of_range& ) {}

                        try { option[CCOpts::UNDER].at( item_index ).at( lang_index ).SetData( under_flag ) ; }
                        catch( out_of_range& ) {}
                    }
                }
            }
            catch( out_of_range& e ) {
                cout << "<Sakura::Load> " << e.what() << " out_of_range exception" << endl ;
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