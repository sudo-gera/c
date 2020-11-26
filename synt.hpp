#ifdef replace_int
using ___main=old_int;
#else
using ___main=int;
#endif
#define end_main }
#define begin_main ___main main(___main _argc,char**_argv){\
	std::vector<std::string>argv;\
	{\
		___main g=0;\
		while g<_argc do\
		{\
			argv.push_back(_argv[g]);\
			g++;\
		}\
	}
#define let auto
#define var auto
#define in :
#define of :
#define while while(
#define do )
#define if if(
#define elif else if(
#define else else(
#define for for(auto 
#ifdef inf_included
	using long_int=inf;
#else
	using long_int=int_least64_t;
#endif
#define short_int int_least64_t
