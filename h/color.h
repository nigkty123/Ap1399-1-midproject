#include <string>
#include <thread>
#include <chrono>
#include <sstream>

enum class ansi_color_code: int{
    black = 30,
    red=31,
    green=32,
    yellow=33,
    blue=34,
    magenta=35,
    cyan=36,
    white=37,
    bright_black = 90,
    bright_red=91,
    bright_green=92,
    bright_yellow=93,
    bright_blue=94,
    bright_magenta=95,
    bright_cyan=96,
    bright_white=97,
};

template<typename printable>
std::string print_as_color(printable const& value, ansi_color_code color){
    std::stringstream sstr;
    sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
    return sstr.str();
}
template<ansi_color_code color,typename printable>
std::string print_as_color(printable const& value){
    std::stringstream sstr;
    sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
    return sstr.str();
}
