#include "../cc_include/TextEditor.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <iostream>

using namespace std ;

color_map_t TextEditor::color ;
opt_map_t   TextEditor::option ;

bool TextEditor::first_flag = true ;
bool TextEditor::second_flag = false ;

std::vector<CCLangs> TextEditor::output_file_type ;

extern string CurrentPath ;

const map<CCLangs, string> TextEditor::to_langname =
{
    { CCLangs::COMMON,  "common" },
    { CCLangs::HTML,    "html" },
    { CCLangs::PERL,    "perl" },
    { CCLangs::PHP,     "php" },
    { CCLangs::CSS,     "css" },
    { CCLangs::RUBY,    "ruby" },
    { CCLangs::INI,     "ini" },
    { CCLangs::BAT,     "bat" },
    { CCLangs::CPP,     "cpp" },
    { CCLangs::JAVA,    "java" },
    { CCLangs::JS,      "js" },
    { CCLangs::VB,      "vb" },
    { CCLangs::HSP,     "hsp" },
    { CCLangs::DELPHI,  "delphi" }
} ;
const string TextEditor::ToLangName( const CCLangs index ) const noexcept
{
    try {
        return to_langname.at( index ) ;
    }
    catch( out_of_range& e ) {
        cout << "<TextEditor::ToLangName> " ;
        cout << e.what() << " out_of_range exception " ;
        cout << "<key> " << to_string( static_cast<size_t>( index ) ) << " ( type is CCLangs )" << endl ;
        return string( "" ) ;
    }
}

TextEditor::TextEditor() :
    name_to_enum(),
    color_code()
{}

void TextEditor::ParseItemTag( const CCLangs lang_index, tinyxml2::XMLElement* first_item_elem )
{

    if( first_item_elem == nullptr ) return ;
    //それぞれのタグ解析
    for( auto i_item = first_item_elem ;
            i_item != nullptr ;
            i_item = i_item->NextSiblingElement() ) {
        
        //ここは、テキストGetText()でカンマを区切り文字とし、
        //複数のインデックスを扱う。vectorで詰め込んで、insert時にforループで回す。
        auto p_text = i_item->GetText() ;
        if( p_text == nullptr ) continue ;
        string original_text( p_text ) ;

        vector<string> item_index_svec ;
        boost::split( item_index_svec, original_text, boost::is_any_of( "," ) ) ;

        vector<CCItems> item_index_vec ;
        for( const auto& i_str : item_index_svec ) {
            item_index_vec.push_back( CCXParser::ToCCItems( i_str ) ) ;
        }

        auto p_item_name = i_item->Attribute( "name" ) ;
        if( p_item_name == nullptr ) continue ;
        string item_name( p_item_name ) ;

        //オプションがあるか
        //項目名と初期値を格納する
        //オプションの場合は、初期値がある程度決まっているので、ccxから初期値を与える
        map<CCOpts, pair<string, bool>> opt_name_map ;
        for( const auto& opt_index : CCOpts() ) {
            const auto& s_atb_name = CCXParser::CCOptsTo( opt_index ) ;

            const auto p_text = i_item->Attribute( s_atb_name.c_str() ) ;
            if( p_text == nullptr ) continue ;

            string str_text( p_text ) ;
            if( str_text.empty() ) continue ;

            vector<string> splited_str ;
            //boostのsplitを用いて:で分割する
            boost::split( splited_str, str_text, boost::is_any_of( ":" ) ) ;

            bool init_is( false ) ;
            
            if( splited_str[1] == "true" ) {
                init_is = true ;
            }
            string opt_name = splited_str[0] ;
            if( opt_name.empty() ) {
                opt_name = item_name ;
            }

            opt_name_map.insert( make_pair( opt_index, make_pair( opt_name, init_is ) ) ) ;
        }

        for( auto it = item_index_vec.begin() ;
             it != item_index_vec.end() ;
             it ++ ) {
            auto text_index( ColorType::error ) ;
            auto back_index( ColorType::error ) ;

            //text属性があるとき、そのカラータイプを保存
            auto p_text_ct = i_item->Attribute( "text" ) ;
            if( p_text_ct != nullptr ) {
                text_index = ToColorType( string( p_text_ct ) ) ;
            }

            //back属性があるとき、 そのカラータイプを保存
            auto p_back_ct = i_item->Attribute( "back" ) ;
            if( p_back_ct != nullptr ) {
                back_index = ToColorType( string( p_back_ct ) ) ;
            }

            if( text_index == ColorType::OWN && back_index == ColorType::OWN ) {
                //どちらもownのときは、重複しないようにして入れる
                text_ct.insert( make_pair( *it, text_index ) ) ;
                back_ct.insert( make_pair( *++it, back_index ) ) ;
                continue ;
            }

            if( text_index != ColorType::error ) {
                text_ct.insert( make_pair( *it, text_index ) ) ;
            }
            if( back_index != ColorType::error ) {
                back_ct.insert( make_pair( *it, back_index ) ) ;
            }
        }
        //入力する側は、関係する項目すべてに同期させる必要があるが、
        //出力する側は、自分の項目のみ分かればよい。
        for( const auto& item_index : item_index_vec ) {
            auto& r_color = color[item_index][lang_index] ;
            if( first_flag ) {
                r_color.SetIName( item_name ) ;
            }
            //出力名は、重複してはいけないので、先頭のものだけセットする
            else if( item_index == item_index_vec.front() ) {
                r_color.SetOName( item_name ) ;
            }

            if( !opt_name_map.empty() ) {
                
                for( const auto& onm_pair : opt_name_map ) {
                    const auto& opt_index = onm_pair.first ;
                    const auto& opt_name  = onm_pair.second.first ;
                    const bool& opt_is    = onm_pair.second.second ;

                    auto& r_option = option[opt_index][item_index][lang_index] ;

                    if( first_flag ) {
                        r_option.SetData( sbool( opt_is ) ) ;
                        r_option.SetIName( opt_name ) ;
                        name_to_enum.insert( make_pair( opt_name, make_pair( lang_index, item_index_vec ) ) ) ;
                    }
                    else {
                        r_option.SetData( sbool( opt_is ) ) ;
                        r_option.SetOName( opt_name ) ;
                    }
                }
            }

            if( !first_flag ) break ;
        }

        if( first_flag ) {
            name_to_enum.insert( make_pair( item_name, make_pair( lang_index, item_index_vec ) ) ) ;
        }
    }

}

void TextEditor::InitItemName( const string file_name )
{
    //3回目以降の呼び出しは、既存の出力用の項目を消す
    if( !second_flag ) ClearOutputItem() ;

    tinyxml2::XMLDocument doc ;
    const auto full_path = CurrentPath + file_name ;

    auto error_id = doc.LoadFile( full_path.c_str() ) ;

    //なにかしらエラーを吐かれた場合は、強制終了する。
    if( error_id != tinyxml2::XMLError::XML_SUCCESS ) {
        cout << "<TextEditor::InitItemName> " << "tinyxml2::XMLDocument::LoadFile(" << full_path << ") " ;
        cout << "XMLError:" << to_string( static_cast<int>( error_id ) ) << endl ;
        return ;
    }
    //langタグ解析
    for( auto i_lang = doc.FirstChildElement( "lang" ) ;
        i_lang != nullptr ;
        i_lang = i_lang->NextSiblingElement( "lang" ) ) {
        
        //name属性があるかどうか確認する。
        auto p_lang_name = i_lang->Attribute( "name" ) ;
        if( p_lang_name == nullptr ) continue ;
        string lang_name( p_lang_name ) ;
        
        const auto& lang_index = CCXParser::ToCCLangs( lang_name ) ;

        //CCLangs::Allのときは、全ての言語に対して行う
        if( lang_index == CCLangs::ALL ) {
            for( auto li : CCLangs() ) {
                if( first_flag ) output_file_type.push_back( CCLangs::COMMON ) ;
                ParseItemTag( li, i_lang->FirstChildElement( "item" ) ) ;
            }
        }
        else {
            if( first_flag ) output_file_type.push_back( lang_index ) ;
            ParseItemTag( lang_index, i_lang->FirstChildElement( "item" ) ) ;
        }
    }
    //最初の呼び出しだけ、trueになるようにする
    if( first_flag ) {
        first_flag = false ;
        second_flag = true ;
    }
    if( second_flag ) {
        second_flag = false ;
    }
}

void TextEditor::ClearOutputItem()
{
    for( auto& lang_map : color ) {
        ClearOName( lang_map ) ;
    }

    for( auto& i_opt : option ) {
        for( auto& item_map : i_opt ) {
            ClearOName( item_map.second ) ;
        }
    }
}

void TextEditor::InitColorCode( const string file_name ) 
{
    tinyxml2::XMLDocument doc ;
    const auto full_path = CurrentPath + file_name ;

    auto error_id = doc.LoadFile( full_path.c_str() ) ;

    //なにかしらエラーを吐かれた場合は、強制終了する。
    if( error_id != tinyxml2::XMLError::XML_SUCCESS ) {
        cout << "<TextEditor::InitColorCode> " << "tinyxml2::XMLDocument::LoadFile(" << full_path << ") " ;
        cout << "XMLError:" << to_string( static_cast<int>( error_id ) ) << endl ;
        return ;
    }
    auto root = doc.FirstChildElement( "ColorCode" ) ;

    for( auto i_code = root->FirstChildElement( "Code" ) ;
        i_code != nullptr ;
        i_code = i_code->NextSiblingElement( "Code" ) ) {

        //name属性がそんざいしないばあいは　、次のループへ
        const auto& name_str_c = i_code->Attribute( "name" ) ;
        if( name_str_c == nullptr ) {
            continue ;
        }
        string code_s = name_str_c ;

        //テキストが記載されていない場合は、 colorのコンストラクタのデフォルト値を用いる。
        const auto& color_str_c = i_code->GetText() ;
        if( color_str_c == nullptr ) continue ;

        Color temp_color( string( color_str_c ) ) ;
        color_code.insert( make_pair( code_s, Color( string( color_str_c ) ) ) ) ;
    }
}

void TextEditor::CorrectExtension( string& file_name, const string dot_extension )
{
    file_name = CurrentPath + file_name ;
    auto dot_pos = file_name.find( "." ) ;

    //ファイル名に拡張子がないときは、拡張子を付けて終了する
    if( dot_pos == string::npos ) {
        file_name += dot_extension ;
        return ;
    }

    //ドット以降は削除する
    file_name.erase( dot_pos ) ;
    file_name += dot_extension ;
}