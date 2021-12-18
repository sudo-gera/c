#include "h"

// def run(int q=-1){
// 	static int w=0;
// 	++w;
// 	print(q,w)
// 	if (w>1234){
// 		print("fast")
// 		return *(int*)nullptr;
// 	}
// 	if (q==-1){
// 		print("0")
// 		return *(int*)nullptr;
// 	}
// 	return 0;
// }


µ{
	const char * a[]={"","","","","\x1b[93mfast\x1b[0m\n","","","","","","","","","","","",""};
	int s[99999];
	for (int q=1;q<3;++q){
		write(q*2147483647,s[99*q],"\r                                    \r",a[q],'\r');
	}
	print("              \r\x1b[93mslow\x1b[0m")
	// run();
		
}


