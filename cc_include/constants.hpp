#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <type_traits>

//enum classを範囲forで扱えるようにするマクロ
#define GENERATE_ENUM_ITERATOR(ENUM_T)\
inline ENUM_T operator ++( ENUM_T& x ) { return x = static_cast<ENUM_T>( std::underlying_type<ENUM_T>::type( x ) + 1 ) ; }\
inline ENUM_T operator *( ENUM_T x ) { return x ; }\
inline ENUM_T begin( ENUM_T ) { return static_cast<ENUM_T>( 0 ) ; }\
inline ENUM_T end( ENUM_T ) { return static_cast<ENUM_T>( std::underlying_type<ENUM_T>::type( ENUM_T::iterator_end ) + 1 ) ; }

enum class CCItems : int
{
    /*
     * 読み込み時のとき、類似するものには別で入れる。
     * 連続するもので、データが一つの場合、色をどんどん薄くする手法をとる。
     * 
    */
    //文字関係
    TEXT,
    BACK,
    SEL_TEXT,
    SEL_BACK,
    LINE_END,
    EOF_MK,
    TAB,
    HALF_SPACE,
    FULL_SPACE,
    LINK,
    QUOTE,
    BRACKET,
    NUMBER,

    //行や列
    CURRENT_BACK,
    CURRENT_UNDER,
    CURRENT_COLUMN,
    EVEN_LINE_BACK,

    RAP_LINE,
    DIGIT_LINE,

    LINE_NUM,
    LINE_NUM_CHANGED,
    RULER,

    CURSOR,
    CURSOR_IME,

    NOTE_LINE,

    //その他
    CTRL_CODE,
    HERE_DOC,

    DIFF_ADD,
    DIFF_CHANGE,
    DIFF_DELETE,

    BOOK_MARK,
    MINI_MAP,

    //多数項目
    FIND_STR,
    FIND_STR1,
    FIND_STR2,
    FIND_STR3,
    FIND_STR4,
    FIND_STR5,

    KEYWORD1,
    KEYWORD2,
    KEYWORD3,
    KEYWORD4,
    KEYWORD5,
    KEYWORD6,
    KEYWORD7,
    KEYWORD8,
    KEYWORD9,
    KEYWORD10,

    REGEX1,
    REGEX2,
    REGEX3,
    REGEX4,
    REGEX5,
    REGEX6,
    REGEX7,
    REGEX8,
    REGEX9,
    REGEX10,

    //コーディング系
    SQ_STR,
    DQ_STR,

    ASP_XML,
    TAG,
    OPTION,
    SECTION,
    KEY,
    LABEL,
    COMMENT,

    //Info
    size,
    iterator_end = COMMENT,
    error = -1,
} ;
GENERATE_ENUM_ITERATOR( CCItems ) ;

enum class CCOpts : int
{
    BOLD,
    CASE,
    SHOW,
    UNDER,

    size,
    iterator_end = UNDER,
    error = -1,
} ;
GENERATE_ENUM_ITERATOR( CCOpts ) ;

enum class CCLangs : int
{
    COMMON,
    HTML,
    PERL,
    PHP,
    CSS,
    RUBY,
    INI,
    BAT,
    CPP,
    JAVA,
    JS,
    VB,
    HSP,
    DELPHI,

    size,
    ALL, //全ての言語に対して行う

    iterator_end = DELPHI,
    error = -1,
} ;
GENERATE_ENUM_ITERATOR( CCLangs ) ;

enum class CCTextEditor : int
{
    TeraPad,
    Sakura,

    size,
    error = -1,
} ;

enum class ColorType : int
{
    NONE,
    OWN,
    MAIN,
    SUB,
    PALE,

    size,
    iterator_end = PALE,
    error = -1,
} ;

#endif
