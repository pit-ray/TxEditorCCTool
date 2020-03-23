#include "../cc_include/ccx_parser.hpp"

#include <stdexcept>
#include <iostream>

using namespace std ;

/*
オプションは
bold="to_ccitems_name:{true or false}"
初期値を与える。
対応するオプションがなかった時のため

*/


const map<string, CCItems> CCXParser::to_ccitems =
{
    { "Text",           CCItems::TEXT },
    { "Back",           CCItems::BACK },
    { "SelText",        CCItems::SEL_TEXT },
    { "SelBack",        CCItems::SEL_BACK },
    { "LineEnd",        CCItems::LINE_END },
    { "EOF",            CCItems::EOF_MK },
    { "Tab",            CCItems::TAB },
    { "HalfSpace",      CCItems::HALF_SPACE },
    { "FullSpace",      CCItems::FULL_SPACE },
    { "Link",           CCItems::LINK },
    { "Quote",          CCItems::QUOTE },
    { "Bracket",        CCItems::BRACKET },
    { "Number",         CCItems::NUMBER },
    { "CurrentBack",    CCItems::CURRENT_BACK },
    { "CurrentUnder",   CCItems::CURRENT_UNDER },
    { "CurrentColumn",  CCItems::CURRENT_COLUMN },
    { "EvenLineBack",   CCItems::EVEN_LINE_BACK },
    { "DigitLine",      CCItems::DIGIT_LINE },
    { "RapLine",        CCItems::RAP_LINE },
    { "LineNum",        CCItems::LINE_NUM },
    { "LineNumChanged", CCItems::LINE_NUM_CHANGED },
    { "Ruler",          CCItems::RULER },
    { "Cursor",         CCItems::CURSOR },
    { "CursorIME",      CCItems::CURSOR_IME },//////////////
    { "NoteLine",       CCItems::NOTE_LINE },///////////////////
    { "CtrlCode",       CCItems::CTRL_CODE },////////////////
    { "HereDoc",        CCItems::HERE_DOC },
    { "DiffAdd",        CCItems::DIFF_ADD },
    { "DiffChange",     CCItems::DIFF_CHANGE },
    { "DiffDelete",     CCItems::DIFF_DELETE },
    { "BookMark",       CCItems::BOOK_MARK },//////////////
    { "MiniMap",        CCItems::MINI_MAP },//////////////
    { "FindStr",        CCItems::FIND_STR },
    { "FindStr1",       CCItems::FIND_STR1 },
    { "FindStr2",       CCItems::FIND_STR2 },
    { "FindStr3",       CCItems::FIND_STR3 },
    { "FindStr4",       CCItems::FIND_STR4 },
    { "FindStr5",       CCItems::FIND_STR5 },
    { "Keyword1",       CCItems::KEYWORD1 },
    { "Keyword2",       CCItems::KEYWORD2 },
    { "Keyword3",       CCItems::KEYWORD3 },
    { "Keyword4",       CCItems::KEYWORD4 },
    { "Keyword5",       CCItems::KEYWORD5 },
    { "Keyword6",       CCItems::KEYWORD6 },
    { "Keyword7",       CCItems::KEYWORD7 },
    { "Keyword8",       CCItems::KEYWORD8 },
    { "Keyword9",       CCItems::KEYWORD9 },
    { "Keyword10",      CCItems::KEYWORD10 },
    { "Regex1",         CCItems::REGEX1 },
    { "Regex2",         CCItems::REGEX2 },
    { "Regex3",         CCItems::REGEX3 },
    { "Regex4",         CCItems::REGEX4 },
    { "Regex5",         CCItems::REGEX5 },
    { "Regex6",         CCItems::REGEX6 },
    { "Regex7",         CCItems::REGEX7 },
    { "Regex8",         CCItems::REGEX8 },
    { "Regex9",         CCItems::REGEX9 },
    { "Regex10",        CCItems::REGEX10 },
    { "SQString",       CCItems::SQ_STR },
    { "DQString",       CCItems::DQ_STR },
    { "AspXml",         CCItems::ASP_XML },
    { "Tag",            CCItems::TAG },
    { "Option",         CCItems::OPTION },
    { "Section",        CCItems::SECTION },
    { "Key",            CCItems::KEY },
    { "Label",          CCItems::LABEL },
    { "Comment",        CCItems::COMMENT }
} ;

const map<CCOpts, string> CCXParser::to_ccopts =
{
    { CCOpts::BOLD, "bold" },
    { CCOpts::CASE, "case" },
    { CCOpts::SHOW, "show" },
    { CCOpts::UNDER, "under" }
} ;

const map<string, CCLangs> CCXParser::to_cclangs =
{
    { "Common", CCLangs::COMMON },
    { "HTML",   CCLangs::HTML },
    { "Perl",   CCLangs::PERL },
    { "PHP",    CCLangs::PHP },
    { "CSS",    CCLangs::CSS },
    { "Ruby",   CCLangs::RUBY },
    { "INI",    CCLangs::INI },
    { "BAT",    CCLangs::BAT },
    { "CPP",    CCLangs::CPP },
    { "Java",   CCLangs::JAVA },
    { "JS",     CCLangs::JS },
    { "VB",     CCLangs::VB },
    { "HSP",    CCLangs::HSP },
    { "Delphi", CCLangs::DELPHI },
    { "All",    CCLangs::ALL }
} ;

const map<string, ColorType> CCXParser::color_type =
{
    { "none", ColorType::NONE },
    { "own",  ColorType::OWN },
    { "main", ColorType::MAIN },
    { "sub",  ColorType::SUB },
    { "pale", ColorType::PALE }
} ;


const CCItems CCXParser::ToCCItems( const string name ) const noexcept
{
    try {
        return to_ccitems.at( name ) ;
    }
    catch( out_of_range& e ) {
        cout << "<CCXParser::ToCCItems> " ;
        cout << e.what() << " out_of_range exception " ;
        cout << "<key> " << name << " (type is std::string)" << endl ;
        return CCItems::error ;
    }
}

const string CCXParser::CCOptsTo( const CCOpts index ) const noexcept
{
    try {
        return to_ccopts.at( index ) ;
    }
    catch( out_of_range& e ) {
        cout << "<CCXParser::CCOptsTo> " ;
        cout << e.what() << " out_of_range exception " ;
        cout << "<key> " << to_string( static_cast<size_t>( index ) ) << " (type is CCOpts)" << endl ;
        return string( "" ) ;
    }
}

const CCLangs CCXParser::ToCCLangs( const string name ) const noexcept
{
    try {
        return to_cclangs.at( name ) ;
    }
    catch( out_of_range& e ) {
        cout << "<CCXParser::ToCCLangs> " ;
        cout << e.what() << " out_of_range exception " ;
        cout << "<key> " << name << " (type is std::string)" << endl ;
        return CCLangs::error ;
    }
}

const ColorType CCXParser::ToColorType( const string name ) const noexcept
{
    try {
        return color_type.at( name ) ;
    }
    catch( out_of_range& e ) {
        cout << "<CCXParser::ToColorType> " ;
        cout << e.what() << " out_of_range exception " ;
        cout << "<key> " << name << " (type is std::string)" << endl ;
        return ColorType::error ;
    }
}