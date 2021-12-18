#include "pony/pony.hpp"
#ifndef DEBUG
#define int int64_t
#endif
#define _main Micro
#define intmain Micro
#define ima Micro
// #define Micro using namespace std;signed main(signed _argc,char**_argv)
#define Micro using namespace std;signed main()
#define _rand srand(time(0));
#define sysargv auto argv=std::vector<std::string>(_argv,_argv+_argc);
#define let auto
#define var auto
#define TO_STR(...) #__VA_ARGS__
#define MACRO_TO_STR(...) TO_STR(__VA_ARGS__)
using namespace std;
#define print(...) print(__VA_ARGS__);
#define write(...) write(__VA_ARGS__);
#define def auto
