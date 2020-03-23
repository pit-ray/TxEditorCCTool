#include "../cc_include/ccio.hpp"

#include <iostream>
#include <string>

using namespace std ;

#include <gflags/gflags.h>

DEFINE_string( fr, "", "input text-editor name" ) ;
DEFINE_string( to, "", "output text-editor name" ) ;
DEFINE_string( nm, "", "output file name" ) ;

//現在パスを参照するためのグローバル変数
string CurrentPath ;

//プロトタイプ宣言
TextEditor* GenerateTextEditor( string editor_name ) ;
string EraseCommandName( const char* argv_0 ) ;

int main( int argc, char* argv[] )
{
    gflags::ParseCommandLineFlags( &argc, &argv, true ) ;

    if( argc != 2 ) {
        cout << "[Error Log]" << endl << "Target file does not exist." << endl ;
        return 1 ;
    }

    //ファイル読み込みに用いるための現在パスを初期化
    CurrentPath = EraseCommandName( argv[0] ) ;

    string input_fname( argv[1] ) ;

    string output_fname( FLAGS_nm ) ;
    if( output_fname.empty() ) {
        output_fname = input_fname ;
    }

    //経過出力
    cout << "[Argument]" << endl ; 
    cout << "Input file name is " << "\"" << input_fname << "\"" << endl ;
    cout << "From " << FLAGS_fr << endl ;
    cout << "To " << FLAGS_to << endl ;
    cout << "Output file name is " << "\"" << output_fname << "\"" << endl ;

    cout << endl ;
    cout << "[Error Log]" << endl ;

    TextEditor* i( GenerateTextEditor( FLAGS_fr ) ) ;
    TextEditor* o( GenerateTextEditor( FLAGS_to ) ) ;

    if( i == nullptr || o == nullptr ) {
        delete i ;
        delete o ;
        return 1 ;
    }

    i->Load( input_fname ) ;
    o->Save( output_fname ) ;

    delete i ;
    delete o ;

    cout << endl << "[End]" << endl << endl ;

    return 0 ;
}


TextEditor* GenerateTextEditor( string editor_name ) {
    if( editor_name == "TeraPad" ) {
        return new TeraPad ;
    }
    else if( editor_name == "Sakura" ) {
        return new Sakura ;
    }
    else {
        cout << "<FlagError>" << editor_name << "is not supported." << endl ;
        return nullptr ;
    }
}

string EraseCommandName( const char* argv_0 ) {
    string path( argv_0 ) ;

    auto pos = path.find( '\\' ) ;
    while( pos != string::npos ) {
        path.replace( pos, 1, "/" ) ; //stringのコンストラクタを呼ぶために文字列として渡す

        pos = path.find( '\\' ) ;
    }

    path.erase( path.find_last_of( '/' ) + 1 ) ;

    return path ;
}