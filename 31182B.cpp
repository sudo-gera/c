#include "string.h"
using s=String;
ima{
	{
		s q("111");
		s w(3,'1');
		test(q==w,"True");
		test(q[0],"1");
		test(q[1],"1");
		test(q[2],"1");
		test(q.length(),"3");
		test(s("112233").rfind("33"),"4")
		test(q+=q,"111111")
		stringstream ss;
		ss=stringstream(" 1 ");
		ss>>q;
		test(q,"1");
		ss=stringstream("2");
		ss>>q;
		test(q,"2");
		ss=stringstream("3 ");
		ss>>q;
		test(q,"3");
		ss=stringstream(" 4");
		ss>>q;
		test(q,"4");
		ss=stringstream(" 55 ");
		ss>>q;
		test(q,"55");
		ss=stringstream("66");
		ss>>q;
		test(q,"66");
		ss=stringstream("77 ");
		ss>>q;
		test(q,"77");
		ss=stringstream(" 88");
		ss>>q;
		test(q,"88");
		s e;
		e.push_back('1');
		test(e,1)

		_rand
	}
	// {
	// 	s q;
	// 	stringstream ss;
	// 	str a,d;
	// 	for (auto w:range(10000)){
	// 		d="";
	// 		for (auto e:range(20)){
	// 			d+="0 "[rand()%2];
	// 		}
	// 		ss<<d;
	// 		ss>>q;
	// 		ss<<d;
	// 		ss>>a;
	// 		if (!(a.c_str()==q)){
	// 			print('-',d,'-',a,'-',q)
	// 		}
	// 	}

	// }
	// {
	// 	s q;
	// 	for (auto w:range(1'000'00)){
	// 		q+="122";
	// 	}
	// 	q+="3";
	// 	s e;
	// 	for (auto w:range(1'000'00)){
	// 		e+="122";
	// 	}
	// 	e+="3";
	// 	test(q.find(e),q.length()-e.length());
	// 	q="";
	// 	for (auto w:range(1'000'000)){
	// 		q.push_back(0);
	// 	}
	// }
}
