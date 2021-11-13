#include<stdio.h>
#include "h"
#undef for

µ{
	for(int g=0;g<9;++g){
		print(g);printf("\x02\x03%i\x01",__LINE__);
	}
}