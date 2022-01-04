#include <math.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

using longdouble=long double;

longdouble zero=0.000012345;

#define log {std::cerr<<__LINE__<<" "<<__PRETTY_FUNCTION__<<std::endl;}

#ifndef HOME
#define ic(...)

#define eic(...) __VA_ARGS__
#endif

struct Point{
	longdouble x,y;
	Point(){}
	Point(longdouble q,longdouble w):x(q),y(w){}
};

#if HOME
auto print_one(Point a){
	return str("Point(")+print_one(a.x)+", "+print_one(a.y)+")";
}
#endif

bool operator==(Point a,Point s){
	return abs(a.x-s.x)<zero and abs(a.y-s.y)<zero;
}

bool operator!=(Point a,Point s){
	return !(a==s);
}

class Line{
public:
	Point a,s;
	Line(Point _a,Point _s){
		a=_a;
		s=_s;
	}
	Line(longdouble k,longdouble b){
		*this=Line({0,b},{1,b+k});
	}
	Line(Point a,longdouble k){
		*this=Line(a,{a.x+1,a.y+k});
	}
};

///////////////////////////////////////////////////////////////////////////////

struct vect;

vect operator+(vect q,vect e);

struct vect{
	longdouble x=0,y=0;
	vect(){};
	vect(longdouble _x,longdouble _y):
		x(_x),
		y(_y)
	{}
	vect(Point _x,Point _y):
		x(_y.x-_x.x),
		y(_y.y-_x.y)
	{}
	vect(Point _y):
		x(_y.x),
		y(_y.y)
	{}
	longdouble abs(){
		// ic(x,y)
		return sqrt(x*x+y*y);
	}
	operator Point()const{
		return {x,y};
	}
	vect rotate(longdouble a){
		return vect(
			x*cosl(a)-y*sinl(a),
			y*cosl(a)+x*sinl(a)
		)+vect(1,1)+vect(-1,-1);
	}
	vect orotate(){
		return {-y,x};
	}
	Line to_line(Point q){
		return Line(q,vect(q)+*this);
	}
	longdouble coord_angle(){
		return atan2(y,x);
	}
	longdouble angle(vect e){
		// ic(*this,e)
		auto t=e.coord_angle()-coord_angle();
		if (t<3.141592653589793){
			t+=3.141592653589793*2;
		}
		if (t>3.141592653589793){
			t-=3.141592653589793*2;
		}
		return t;
	}
};

#if HOME
auto print_one(vect a){
	return str("vect(")+print_one(a.x)+", "+print_one(a.y)+")";
}
auto print_one(Line a){
	return str("Line(")+print_one(a.a)+", "+print_one(a.s)+")";
}
#endif

longdouble angle(vect q,vect e){
	return q.angle(e);
}

vect operator+(vect q,vect e){
	return {q.x+e.x,q.y+e.y};
}

vect operator-(vect q,vect e){
	return {q.x-e.x,q.y-e.y};
}

vect operator*(vect q,longdouble e){
	return {q.x*e,q.y*e};
}

vect operator*(longdouble q,vect e){
	return {q*e.x,q*e.y};
}

vect operator/(vect q,longdouble e){
	return {q.x/e,q.y/e};
}

vect operator/(longdouble q,vect e){
	return {q/e.x,q/e.y};
}

auto operator*(vect q,vect e){
	return q.x*e.x+q.y*e.y;
}

auto operator/(vect q,vect e){
	return q.x*e.y-q.y*e.x;
}

auto operator^(vect q,vect e){
	auto t=q/e;
	return t>0?1:t<0?-1:0;
}

///////////////////////////////////////////////////////////////////////////////

bool operator==(Line q,Line e){
	auto a=vect(q.a,q.s)/vect(q.a,q.s).abs();
	auto s=vect(e.a,e.s)/vect(e.a,e.s).abs();
	return (a-s).abs()<zero or (a+s).abs()<zero;
}

bool operator!=(Line q,Line w){
	return !(q==w);
}

class Shape{
public:
	virtual longdouble perimeter()=0;
	virtual longdouble area()=0;
	virtual bool isCongruentTo(const Shape&q);
	virtual bool isSimilarTo(const Shape&q);
	virtual bool containsPoint(const Point&q)=0;
	virtual void rotate(Point center, longdouble angle)=0;
	virtual void reflect(Point center)=0;
	virtual void reflect(Line axis)=0;
	virtual void scale(Point center, longdouble coefficient)=0;
	virtual ~Shape(){}
};

Point rotate(Point q,Point e,longdouble r){
	return e+vect(e,q).rotate(r);
}

Point scale(Point q,Point e,longdouble r){
	return e+vect(e,q)*r;
}

Point intersect(Line q,Line e){
	auto
		x1=q.a.x,
		y1=q.a.y,
		x2=q.s.x,
		y2=q.s.y,
		x3=e.a.x,
		y3=e.a.y,
		x4=e.s.x,
		y4=e.s.y;
	return{
		((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))
		/
		((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)),
		((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))
		/
		((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4))
	};

	// auto t=
	// 	(x1-x3)*(y3-y4)-(y1-y3)*(x3-x4)
	// 	/
	// 	()
}

Point reflect(Point q,Line e){
	// ic(q,e)
	return q-2*vect(
		intersect(
			vect(e.a,e.s).orotate().to_line(q),e
		),q
	);
}

class Polygon:public Shape{
public:
	std::vector<Point> vertices;
	size_t verticesCount(){
		return vertices.size();
	}
	const auto&getVertices()const{
		return vertices;
	}
	bool isConvex(){
		// ssize_t vs=vertices.size();
		// auto j=
		// 	vect(
		// 		vertices[vs-1],
		// 		vertices[0]
		// 	)^vect(
		// 		vertices[0],
		// 		vertices[1]
		// 	);
		// for (ssize_t w=0;w<ssize_t(vertices.size());++w){
		// 	if (((vect(
		// 			vertices[(w-1)%vs],
		// 			vertices[w]
		// 		)^vect(
		// 			vertices[w],
		// 			vertices[(w+1)%vs]
		// 		)))!=j){
		// 		return false;
		// 	}
		// }
		// return true;
		longdouble direction=0;
		for (size_t w=0;w<vertices.size();++w){
			direction+=angle(vect(vertices[w],vertices[(w+1)%vertices.size()]),vect(vertices[(w+1)%vertices.size()],vertices[(w+2)%vertices.size()]));
		}
		for (size_t w=0;w<vertices.size();++w){
			if (direction*angle(vect(vertices[w],vertices[(w+1)%vertices.size()]),vect(vertices[(w+1)%vertices.size()],vertices[(w+2)%vertices.size()]))<0){
				return false;
			}
		}
		return true;
	}
	Polygon(const std::vector<Point>&q):
		vertices(q.begin(),q.end())
	{}

	// template <typename...T>
	// Polygon(const T&...q)
	// 	:vertices({Point(q)...})
	// {}

	#define __rp__0(x) TO_REPEAT(x)
	#define __rp__1(x) __rp__0(x##0) SEP __rp__0(x##1)
	#define __rp__2(x) __rp__1(x##0) SEP __rp__1(x##1)
	#define __rp__3(x) __rp__2(x##0) SEP __rp__2(x##1)
	#define __rp__4(x) __rp__3(x##0) SEP __rp__3(x##1)
	#define __rp__5(x) __rp__4(x##0) SEP __rp__4(x##1)
	#define __rp__6(x) __rp__5(x##0) SEP __rp__5(x##1)
	#define __rp__7(x) __rp__6(x##0) SEP __rp__6(x##1)
	#define __rp__8(x) __rp__7(x##0) SEP __rp__7(x##1)
	#define __rp__9(x) __rp__8(x##0) SEP __rp__8(x##1)
	#define REPEAT(x) __rp__##x(0b)
	#define TO_REPEAT(x) Point q##x=Point(98765432123456789,98765432123456789)
	#define SEP ,
	Polygon(REPEAT(4)):
	#undef TO_REPEAT
	#define TO_REPEAT(x) q##x
		vertices({REPEAT(4)})
	#undef TO_REPEAT
	{
		while(vertices.size() and vertices[vertices.size()-1]==Point(98765432123456789,98765432123456789)){
			vertices.pop_back();
		}
	}
	#undef SEP

	longdouble perimeter() override {
		auto res=vect(vertices[vertices.size()-1],vertices[0]).abs();
		for (size_t w=1;w<vertices.size();++w){
			res+=vect(vertices[w-1],vertices[w]).abs();
		}
		return res;
	}
	longdouble area()override{
		// __gnu_cxx::rope<Point> ver(vertices.begin(),vertices.end());
		// longdouble direction=0;
		// for (size_t w=0;w<vertices.size();++w){
		// 	direction+=angle(vect(vertices[w],vertices[(w+1)%vertices.size()]),vect(vertices[(w+1)%vertices.size()],vertices[(w+2)%vertices.size()])) ;
			// ic(direction)
		// }
		// vector<Point> ver;
		// if (direction>0){
		// 	ver=vector<Point>(vertices.begin(),vertices.end());
		// }else{
		// 	ver=vector<Point>(vertices.rbegin(),vertices.rend());
		// }
		longdouble res=0;
		for (size_t w=2;w<vertices.size();++w){
			res+=vect(vertices[0],vertices[w-1])/vect(vertices[w-1],vertices[w]);
		}
		return abs(res)/2;
		// assert(0);
	}
	bool containsPoint(const Point&q)override{
		// longdouble direction=0;
		// for (size_t w=0;w<vertices.size();++w){
		// 	direction+=angle(vect(vertices[w],vertices[(w+1)%vertices.size()]),vect(vertices[(w+1)%vertices.size()],vertices[(w+2)%vertices.size()])) ;
		// 	ic(direction)
		// }
		// vector<Point> ver;
		// if (direction>0){
		// 	ver=vector<Point>(vertices.begin(),vertices.end());
		// }else{
		// 	ver=vector<Point>(vertices.rbegin(),vertices.rend());
		// }
		// for (size_t )
		assert(0);
		return size_t(&q-100);
	}
	void rotate(Point center, longdouble angle)override{
		for (auto&w:vertices){
			w=::rotate(w,center,angle);
		}
	}
	void reflect(Point center)override{
		for (auto&w:vertices){
			w=center-vect(center,w);
		}
	}
	void reflect(Line axis)override{
		for (auto&w:vertices){
			// w=w-2*vect(intersect(vect(axis.a,axis.s).orotate().to_line(w),axis),w);
			w=::reflect(w,axis);
		}
	}
	void scale(Point center, longdouble coefficient)override{
		for (auto&w:vertices){
			w=::scale(w,center,coefficient);
		}
	}
};



class Ellipse:public Shape{
public:
	longdouble a,b,c,e;
	Point f1,f2;
	Ellipse(Point _f1,Point _f2,longdouble d):f1(_f1),f2(_f2){
		a=d/2;
		c=vect(_f1,_f2).abs()/2;
		b=sqrt(a*a-c*c);
		e=c/a;
	}
	std::pair<Point,Point> focuses(){
		return {f1,f2};
	}
	std::pair<Line, Line> directrices(){
		auto p=vect(f1,f2).orotate();
		auto d=vect(f1,f2)/c/2*a/e;
		return {
			p.to_line(center()+d),
			p.to_line(center()-d)
		};
	}
	longdouble eccentricity(){
		return e;
	}
	Point center(){
		return (vect(f1)+vect(f2))/2;
	}
	longdouble perimeter(){
		return 4*(3.141592653589793*a*b+a-b)/(a+b);
	}
	longdouble area(){
		return a*b*3.141592653589793;
	}
	bool containsPoint(const Point&e){
		return vect(f1,e).abs()+vect(f2,e).abs()<=a*2;
	}
	void rotate(Point center, longdouble angle){
		f1=::rotate(f1,center,angle);
		f2=::rotate(f2,center,angle);
	}
	void reflect(Point center){
		f1=center-vect(center,f1);
		f2=center-vect(center,f2);
	}
	void reflect(Line axis){
		f1=f1-2*vect(intersect(vect(axis.a,axis.s).orotate().to_line(f1),axis),f1);
		f2=f2-2*vect(intersect(vect(axis.a,axis.s).orotate().to_line(f2),axis),f2);
	}
	void scale(Point center, longdouble coefficient){
		f1=::scale(f1,center,coefficient);
		f2=::scale(f2,center,coefficient);
	}
};

class Circle:
	public Ellipse{
public:
	Circle(Point q,longdouble d):
		Ellipse(q,q,d)
	{}
	longdouble radius(){
		return a;
	}
};

class Rectangle:
	public Polygon{
public:
	using Polygon::Polygon;
	Rectangle(Point q,Point e,longdouble f){
		if (f>1){
			auto s=vect(q,e)/(f*f+1)+vect(q,e).orotate()*f/(f*f+1);
			*this=Rectangle(Point(q),Point(q+s),Point(e),Point(e-s));
		}else{
			*this=Rectangle(q,e,1/f);
		}
	}
	std::pair<Line, Line> diagonals(){
		return {{vertices[0],vertices[2]},{vertices[1],vertices[3]}};
	}
	Point center(){
		return vect(vertices[0],vertices[1])/2+vect(vertices[1]+vertices[2])/2+vertices[0];
	}
};

class Square:
	public Rectangle{
public:
	using Rectangle::Rectangle;
	Circle circumscribedCircle(){
		return Circle(center(),vect(vertices[0],vertices[1]).abs()/sqrt(2.0));
	}
	Circle inscribedCircle(){
		return Circle(center(),vect(vertices[0],vertices[1]).abs()/2);
	}
};




class Triangle:
	public Polygon{
public:
	using Polygon::Polygon;
	Circle circumscribedCircle(){
		auto g=intersect(
			vect(vertices[0],vertices[1]).orotate().to_line(vertices[0]+vect(vertices[0],vertices[1])/2),
			vect(vertices[0],vertices[2]).orotate().to_line(vertices[0]+vect(vertices[0],vertices[2])/2)
		);
		return Circle(g,vect(g,vertices[0]).abs());
	}
	Circle inscribedCircle(){
		auto b1=vect(vertices[0],vertices[2]).rotate(
					vect(vertices[0],vertices[2]).angle(
						vect(vertices[0],vertices[1])
					)/2
			).to_line(vertices[0]);
		auto b2=vect(vertices[1],vertices[2]).rotate(
					vect(vertices[1],vertices[2]).angle(
						vect(vertices[1],vertices[0])
					)/2
			).to_line(vertices[1]);
		auto g=intersect(b1,b2);
		return Circle(g,vect(g,intersect(Line(vertices[0],vertices[1]),vect(vertices[0],vertices[1]).orotate().to_line(g))).abs());
	}
	Point centroid(){
		return (vertices[0]+vertices[1]+vertices[2])/3;
	}
	Point orthocenter(){
		return intersect(
			vect(vertices[0],vertices[1]).orotate().to_line(vertices[2]),
			vect(vertices[2],vertices[1]).orotate().to_line(vertices[0])
		);
	}
	Line EulerLine(){
		return Line(centroid(),orthocenter());
	}
	Circle ninePointsCircle(){
		return Circle(
			(orthocenter()+circumscribedCircle().center())/2,
			vect((orthocenter()+circumscribedCircle().center())/2,(vertices[0],vertices[1])/2).abs()
		);
	}
};

#if HOME
auto print_one(Polygon a){
	return str("pol(")+print_one(a.vertices)+")";
}
auto print_one(Rectangle a){
	return str("pol(")+print_one(a.vertices)+")";
}
auto print_one(Square a){
	return str("pol(")+print_one(a.vertices)+")";
}
auto print_one(Triangle a){
	return str("pol(")+print_one(a.vertices)+")";
}
#endif

template <typename T,typename Y>
bool simPolygon(T q,Y e){
	if (q.getVertices().size()!=q.getVertices().size()){
		return false;
	}
	if (q.getVertices().size()<3){
		return true;
	}

	ic(q)
	ic(e)

	size_t mw=0;
	longdouble m=vect(q.getVertices()[0],q.getVertices()[1]).abs();
	for (size_t w=0;w<q.getVertices().size();++w){
		auto t=vect(q.getVertices()[w],q.getVertices()[(w+1)%q.getVertices().size()]).abs();
		if (t>m){
			mw=w;
			m=t;
		}
	}
	{
		auto t=q;
		q.vertices.clear();
		q.vertices.insert(q.vertices.end(),t.vertices.begin()+mw,t.vertices.end());
		q.vertices.insert(q.vertices.end(),t.vertices.begin(),t.vertices.begin()+mw);
	}
	mw=0;
	m=vect(e.getVertices()[0],e.getVertices()[1]).abs();
	for (size_t w=0;w<e.getVertices().size();++w){
		auto t=vect(e.getVertices()[w],e.getVertices()[(w+1)%e.getVertices().size()]).abs();
		if (t>m){
			mw=w;
			m=t;
		}
	}
	{
		auto t=e;
		e.vertices.clear();
		e.vertices.insert(e.vertices.end(),t.vertices.begin()+mw,t.vertices.end());
		e.vertices.insert(e.vertices.end(),t.vertices.begin(),t.vertices.begin()+mw);
	}

	ic(q)
	ic(e)

	e.scale(e.getVertices()[0],
		eic(vect(q.getVertices()[0],q.getVertices()[1])).abs()/
		eic(vect(e.getVertices()[0],e.getVertices()[1])).abs()
		);

	ic(q)
	ic(e)

	auto tm=vect(e.getVertices()[0],q.getVertices()[0]);
	ic(tm)
	for (size_t w=0;w<e.getVertices().size();++w){
		e.vertices[w]=e.vertices[w]+tm;
	}

	ic(q)
	ic(e)

	auto an=angle(
		vect(e.getVertices()[0],e.getVertices()[1]),
		vect(q.getVertices()[0],q.getVertices()[1])
	);
	ic(an)

	e.rotate(e.getVertices()[0], an);

	ic(q)
	ic(e)

	bool res=0;

	res=res or eqPolygon(q,e);
	e.reflect(Line(e.getVertices()[0],e.getVertices()[1]));
	ic(q)
	ic(e)
	res=res or eqPolygon(q,e);
	e.reflect(vect(e.getVertices()[0],e.getVertices()[1]).orotate().to_line((e.getVertices()[0]+e.getVertices()[1])/2));
	ic(q)
	ic(e)
	res=res or eqPolygon(q,e);
	e.reflect(Line(e.getVertices()[0],e.getVertices()[1]));
	ic(q)
	ic(e)
	res=res or eqPolygon(q,e);


	return res;
}

bool isSimilarTo(const Shape&q,const Shape&e){
	if (auto w=dynamic_cast<const Polygon*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return simPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Rectangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return simPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Square*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return simPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Triangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return simPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return simPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Ellipse*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return abs(w->a*r->b-w->b*r->a)<zero;
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return abs(w->a*r->b-w->b*r->a)<zero;
		}
	}
	if (auto w=dynamic_cast<const Circle*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return abs(w->a*r->b-w->b*r->a)<zero;
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return abs(w->a*r->b-w->b*r->a)<zero;
		}
	}
	return false;
}

bool Shape::isSimilarTo(const Shape&q){
	return ::isSimilarTo(*this,q);
}

template <typename T,typename Y>
bool conPolygon(T q,Y e){
	if (q.getVertices().size()!=q.getVertices().size()){
		return false;
	}
	if (q.getVertices().size()<3){
		return true;
	}

	ic(q)
	ic(e)

	size_t mw=0;
	longdouble m=vect(q.getVertices()[0],q.getVertices()[1]).abs();
	for (size_t w=0;w<q.getVertices().size();++w){
		auto t=vect(q.getVertices()[w],q.getVertices()[(w+1)%q.getVertices().size()]).abs();
		if (t>m){
			mw=w;
			m=t;
		}
	}
	{
		auto t=q;
		q.vertices.clear();
		q.vertices.insert(q.vertices.end(),t.vertices.begin()+mw,t.vertices.end());
		q.vertices.insert(q.vertices.end(),t.vertices.begin(),t.vertices.begin()+mw);
	}
	mw=0;
	m=vect(e.getVertices()[0],e.getVertices()[1]).abs();
	for (size_t w=0;w<e.getVertices().size();++w){
		auto t=vect(e.getVertices()[w],e.getVertices()[(w+1)%e.getVertices().size()]).abs();
		if (t>m){
			mw=w;
			m=t;
		}
	}
	{
		auto t=e;
		e.vertices.clear();
		e.vertices.insert(e.vertices.end(),t.vertices.begin()+mw,t.vertices.end());
		e.vertices.insert(e.vertices.end(),t.vertices.begin(),t.vertices.begin()+mw);
	}

	ic(q)
	ic(e)

	auto tm=vect(e.getVertices()[0],q.getVertices()[0]);
	ic(tm)
	for (size_t w=0;w<e.getVertices().size();++w){
		e.vertices[w]=e.vertices[w]+tm;
	}

	ic(q)
	ic(e)

	auto an=angle(
		vect(e.getVertices()[0],e.getVertices()[1]),
		vect(q.getVertices()[0],q.getVertices()[1])
	);
	ic(an)

	e.rotate(e.getVertices()[0], an);

	ic(q)
	ic(e)

	bool res=0;

	res=res or eqPolygon(q,e);
	e.reflect(Line(e.getVertices()[0],e.getVertices()[1]));
	ic(q)
	ic(e)
	res=res or eqPolygon(q,e);
	e.reflect(vect(e.getVertices()[0],e.getVertices()[1]).orotate().to_line((e.getVertices()[0]+e.getVertices()[1])/2));
	ic(q)
	ic(e)
	res=res or eqPolygon(q,e);
	e.reflect(Line(e.getVertices()[0],e.getVertices()[1]));
	ic(q)
	ic(e)
	res=res or eqPolygon(q,e);


	return res;
}

bool isCongruentTo(const Shape&q,const Shape&e){
	if (auto w=dynamic_cast<const Polygon*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return conPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Rectangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return conPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Square*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return conPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Triangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return conPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return conPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Ellipse*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return abs(w->a-r->a)<zero;
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return abs(w->a-r->a)<zero;
		}
	}
	if (auto w=dynamic_cast<const Circle*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return abs(w->a-r->a)<zero;
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return abs(w->a-r->a)<zero;
		}
	}
	return false;
}

bool Shape::isCongruentTo(const Shape&q){
	return ::isCongruentTo(*this,q);
}

template <typename T,typename Y>
bool eqPolygon(const T&q,const Y&e){
	if (q.getVertices().size()!=q.getVertices().size()){
		return false;
	}
	if (q.getVertices().size()==0){
		return true;
	}
	for (size_t r=0;r<e.getVertices().size();++r){
		bool not_same=0;
		for (size_t w=0;w<q.getVertices().size();++w){
			if (q.getVertices()[w]!=e.getVertices()[(r+w)%e.getVertices().size()]){
				not_same=1;
			}
		}
		if (!not_same){
			return true;
		}
		not_same=0;
		for (size_t w=0;w<q.getVertices().size();++w){
			if (q.getVertices()[w]!=e.getVertices()[(e.getVertices().size()+r-w)%e.getVertices().size()]){
				not_same=1;
			}
		}
		if (!not_same){
			return true;
		}
	}
	return false;
}

bool operator==(const Shape&q,const Shape&e){
	if (auto w=dynamic_cast<const Polygon*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return eqPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Rectangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return eqPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Square*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return eqPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Triangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return eqPolygon(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return eqPolygon(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Ellipse*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return abs(w->a-r->a)<zero and (w->f1-r->f1).abs()<zero and (w->f2-r->f2).abs()<zero;
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return abs(w->a-r->a)<zero and (w->f1-r->f1).abs()<zero and (w->f2-r->f2).abs()<zero;
		}
	}
	if (auto w=dynamic_cast<const Circle*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return abs(w->a-r->a)<zero and (w->f1-r->f1).abs()<zero and (w->f2-r->f2).abs()<zero;
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return abs(w->a-r->a)<zero and (w->f1-r->f1).abs()<zero and (w->f2-r->f2).abs()<zero;
		}
	}
	return false;
}

bool operator!=(const Shape&q,const Shape&e){
	return !(q==e);
}


auto readfile_(FILE*q){
	std::string s;
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(q)) != EOF) { // standard C I/O file reading loop
		s+=c;
	}
	return s;
}

auto replace_(std::string q,std::string w,std::string e){
	std::string res;
	uint64_t a=0;
	while (a<uint64_t((q).size())){
		if (q.find(w,a)==a){
			res+=e;
			a+=w.size();
		}else{
			res+=q[a];
			++a;
		}
	}
	return res;
}

bool printed=0;

int ffff(std::string file){
	if (printed){
		return 0;
	}
	printed=1;
	auto d=fopen(file.c_str(),"r");
	auto s=readfile_(d);
	fclose(d);
	for (size_t w=0;w<128;++w){
		if (isspace(w) and w!='\n'){
			s=replace_(s,{char(w)},"");
		}
	}
	size_t len=512;
	size_t start=len*0;
	std::cerr<<"PART "<<start/len<<" of "<< s.size()/len+1  <<std::endl;
	std::cerr<<string(s.begin()+(start<s.size()?start:s.size()),s.begin()+(start+len<s.size()?start+len:s.size()))<<std::endl;
	return 0;
}


#define area(...) area(__VA_ARGS__)+ffff(__FILE__)
