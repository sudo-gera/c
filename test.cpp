#if SELF_INCLUDE==1
	#define CAT_(x,y) x##y
	#define CAT(x,y) CAT_(x,y)
	struct CAT(str_,T){
		
	};
#endif
#if SELF_INCLUDE==0

	#define T int
	#define SELF_INCLUDE 1
	#include "test.cpp"

	#define T int
	#define SELF_INCLUDE 1
	#include "test.cpp"




#endif
