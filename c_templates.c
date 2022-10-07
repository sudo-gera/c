#if SELF_INCLUDE==1

	#define CAT_(x,y) x##y
	#define CAT(x,y) CAT_(x,y)
	struct CAT(vector_,T){
		T*vector;
	};

#endif
#if SELF_INCLUDE==2

	#define CAT_(x,y) x##y
	#define CAT(x,y) CAT_(x,y)
	struct CAT(set_,T){
		T*set;
	};

#endif
#if SELF_INCLUDE==0

	#define T int
	#define SELF_INCLUDE 1
	#include __FILE__
	#undef T
	#undef SELF_INCLUDE


	#define T double
	#define SELF_INCLUDE 1
	#include __FILE__
	#undef T
	#undef SELF_INCLUDE


	#define T int
	#define SELF_INCLUDE 2
	#include __FILE__
	#undef T
	#undef SELF_INCLUDE


	#define T double
	#define SELF_INCLUDE 2
	#include __FILE__
	#undef T
	#undef SELF_INCLUDE


#endif

