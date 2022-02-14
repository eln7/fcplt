#include <string>
#include <list>
#include <map>

#include "eln_menu.h"


std::map< int, std::string > eln_main_menu;



void testing_stl(void)
{
    eln_main_menu[42] = "Fourty Two" ;
    eln_main_menu[111] = "Hello World" ;
    eln_main_menu.insert(std::make_pair(23, "Bye")) ;

    std::map<int, std::string>::iterator it = eln_main_menu.find(42) ;
    std::pair<int, std::string> keyvalue = *it ;    // We assume 42 does

    int key = keyvalue.first ;
    std::string  value = keyvalue.second ;
}

