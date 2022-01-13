#include <math.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <algorithm>

double zero=0.000012345;

double pi=3.141592653589793;

struct Point{
	double x,y;
	Point(){}
	Point(double q,double w):x(q),y(w){}
};

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
	Line(double k,double b){
		*this=Line({0,b},{1,b+k});
	}
	Line(Point a,double k){
		*this=Line(a,{a.x+1,a.y+k});
	}
};

struct vect;

vect operator+(vect q,vect e);

vect operator*(vect q,double e);

struct vect{
	double x=0,y=0;
	vect(){};
	vect(double _x,double _y):
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
	vect operator-(){
		return {-x,-y};
	}
	double abs(){
		return sqrt(x*x+y*y);
	}
	operator Point()const{
		return {x,y};
	}
	vect rotate(double a){
		return vect(
			x*cosl(a)-y*sinl(a),
			y*cosl(a)+x*sinl(a)
		);
	}
	Line to_line(Point q){
		return Line(q,vect(q)+*this);
	}
	vect perp(){
		return {-y,x};
	}
	double coord_angle(){
		return atan2(y,x);
	}
	double angle(vect e){
		auto t=e.coord_angle()-coord_angle();
		if (t<pi){
			t+=pi*2;
		}
		if (t>pi){
			t-=pi*2;
		}
		return t;
	}
	vect(Point q,Point e,double r,double t);
	vect(Line q){
		*this=vect(q.a,q.s);
	}
};

Line perp_line(Point q,Point w,Point e){
	return vect(q,w).perp().to_line(e);
}

vect::vect(Point q,Point e,double r,double t){
	*this=vect(q,e)*r+vect(q,e).perp()*t;
}

double angle(vect q,vect e){
	return q.angle(e);
}

double angle(Point q,Point w,Point e){
	return angle(vect(q,w),vect(w,e));
}

vect operator+(vect q,vect e){
	return {q.x+e.x,q.y+e.y};
}

vect operator-(vect q,vect e){
	return {q.x-e.x,q.y-e.y};
}

vect operator*(vect q,double e){
	return {q.x*e,q.y*e};
}

vect operator*(double q,vect e){
	return {q*e.x,q*e.y};
}

vect operator/(vect q,double e){
	return {q.x/e,q.y/e};
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
	virtual double perimeter()=0;
	virtual double area()=0;
	virtual bool isCongruentTo(const Shape&q);
	virtual bool isSimilarTo(const Shape&q);
	virtual bool containsPoint(const Point&q)=0;
	virtual void rotate(Point center, double angle)=0;
	virtual void reflect(Point center)=0;
	virtual void reflect(Line axis)=0;
	virtual void scale(Point center, double coefficient)=0;
	virtual ~Shape(){}
};

Point rotate(Point q,Point e,double r){
	return e+vect(e,q).rotate(r);
}

Point scale(Point q,Point e,double r){
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
		/ //	---------------------------------------------
					((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4))
	,
				((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))
		/ //	---------------------------------------------
					((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4))
	};

}

Point normal(Point q,Line e){
	return intersect(perp_line(e.a,e.s,q),e);
}

Point reflect(Point q,Line e){
	return 2*normal(q,e)-q;
}

Point reflect(Point q,Point e){
	return 2*e-q;
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
		double direction=0;
		for (size_t w=0;w<vertices.size();++w){
			auto&A=vertices[w];
			auto&B=vertices[(w+1)%vertices.size()];
			auto&C=vertices[(w+2)%vertices.size()];
			direction+=angle(A,B,C);
		}
		for (size_t w=0;w<vertices.size();++w){
			auto&A=vertices[w];
			auto&B=vertices[(w+1)%vertices.size()];
			auto&C=vertices[(w+2)%vertices.size()];
			if (direction*angle(A,B,C)<0){
				return false;
			}
		}
		return true;
	}
	Polygon(const std::vector<Point>&q):
		vertices(q.begin(),q.end())
	{}
	template <typename...T>
	Polygon(const T&...q):
		vertices({Point(q)...})
	{}
	double perimeter() override {
		auto res=vect(vertices[vertices.size()-1],vertices[0]).abs();
		for (size_t w=1;w<vertices.size();++w){
			res+=vect(vertices[w-1],vertices[w]).abs();
		}
		return res;
	}
	double area()override{
		double res=0;
		for (size_t w=2;w<vertices.size();++w){
			res+=vect(vertices[0],vertices[w-1])/vect(vertices[w-1],vertices[w]);
		}
		return abs(res)/2;
	}
	bool containsPoint(const Point&q)override;
	void rotate(Point center, double angle)override{
		for (auto&w:vertices){
			w=::rotate(w,center,angle);
		}
	}
	void reflect(Point center)override{
		for (auto&w:vertices){
			w=::reflect(w,center);			
		}
	}
	void reflect(Line axis)override{
		for (auto&w:vertices){
			w=::reflect(w,axis);
		}
	}
	void scale(Point center, double coefficient)override{
		for (auto&w:vertices){
			w=::scale(w,center,coefficient);
		}
	}
};

class Ellipse:public Shape{
public:
	double a,b,c,e;
	Point f1,f2;
	Ellipse(Point _f1,Point _f2,double d):f1(_f1),f2(_f2){
		a=d/2;
		c=vect(_f1,_f2).abs()/2;
		b=sqrt(a*a-c*c);
		e=c/a;
	}
	std::pair<Point,Point> focuses(){
		return {f1,f2};
	}
	std::pair<Line, Line> directrices(){
		vect p=vect(f1,f2).perp();
		vect d=vect(f1,f2)/c/2*a/e;
		return {
			p.to_line(center()+d),
			p.to_line(center()-d)
		};
	}
	double eccentricity(){
		return e;
	}
	Point center(){
		return (f1+f2)/2;
	}
	double perimeter(){
		double res=0;
		double dt=0.0000004;
		double tmp;
		for (double t=0;t<pi/2;t+=dt){
			tmp=cos(t)*e;
			res+=dt*sqrt(1-tmp*tmp);
		}
		return 4*a*res;
	}
	double area(){
		return a*b*pi;
	}
	bool containsPoint(const Point&e){
		return vect(f1,e).abs()+vect(f2,e).abs()<=a*2;
	}
	void rotate(Point center, double angle){
		f1=::rotate(f1,center,angle);
		f2=::rotate(f2,center,angle);
	}
	void reflect(Point center){
		f1=::reflect(f1,center);
		f2=::reflect(f2,center);
	}
	void reflect(Line axis){
		f1=::reflect(f1,axis);
		f2=::reflect(f2,axis);
	}
	void scale(Point center, double coefficient){
		f1=::scale(f1,center,coefficient);
		f2=::scale(f2,center,coefficient);
		a*=abs(coefficient);
		b*=abs(coefficient);
		c*=abs(coefficient);
	}
};

class Circle:
	public Ellipse{
public:
	Circle(Point q,double d):
		Ellipse(q,q,d*2)
	{}
	Circle(Point q,Point e):
		Ellipse(q,q,vect(q,e).abs()*2)
	{}
	double radius(){
		return a;
	}
};

class Rectangle:
	public Polygon{
public:
	using Polygon::Polygon;
	Rectangle(Point q,Point e,double f){
		if (f>=1){
			auto s=vect(q,e,1/(f*f+1),f/(f*f+1));
			*this=Rectangle(q,q+s,e,e-s);
		}else{
			*this=Rectangle(q,e,1/f);
		}
	}
	Rectangle(Point q,Point e,int f){
		*this=Rectangle(q,e,double(f));
	}
	std::pair<Line, Line> diagonals(){
		return {
			{vertices[0],vertices[2]},
			{vertices[1],vertices[3]}
		};
	}
	Point center(){
		return (vertices[0]+vertices[1]+vertices[2]+vertices[3])/4;
	}
};

class Square:
	public Rectangle{
public:
	using Rectangle::Rectangle;
	Square(Point q,Point e){
		auto g=vect(q,e,0.5,0.5);
		*this=Square(q,g+q,e,e-g);
	}
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
			perp_line(vertices[0],vertices[1],(vertices[0]+vertices[1])/2),
			perp_line(vertices[0],vertices[2],(vertices[0]+vertices[2])/2)
		);
		return Circle(g,vertices[0]);
	}
	Circle inscribedCircle(){
		auto b1=vect(vertices[0],vertices[2]).rotate(
					angle(
						vect(vertices[0],vertices[2]),
						vect(vertices[0],vertices[1])
					)/2
			).to_line(vertices[0]);
		auto b2=vect(vertices[1],vertices[2]).rotate(
					angle(
						vect(vertices[1],vertices[2]),
						vect(vertices[1],vertices[0])
					)/2
			).to_line(vertices[1]);
		auto g=intersect(b1,b2);
		return Circle(g,normal(g,Line(vertices[0],vertices[1])));
	}
	Point centroid(){
		return (vertices[0]+vertices[1]+vertices[2])/3;
	}
	Point orthocenter(){
		return intersect(
			perp_line(vertices[0],vertices[1],vertices[2]),
			perp_line(vertices[2],vertices[1],vertices[0])
		);
	}
	Line EulerLine(){
		return Line(centroid(),orthocenter());
	}
	Circle ninePointsCircle(){
		auto g=circumscribedCircle();
		g.scale(centroid(),-0.5);
		return g;


	}
};

bool in_triangle(Triangle q,Point w,bool no_bord=0){
	auto z=vect(q.vertices[0],q.vertices[1])^vect(q.vertices[0],w);
	auto x=vect(q.vertices[1],q.vertices[2])^vect(q.vertices[1],w);
	auto c=vect(q.vertices[2],q.vertices[0])^vect(q.vertices[2],w);
	if (no_bord){
		return z==x and x==c;
	}
	if (z>=0 and x>=0 and c>=0){
		return 1;
	}
	if (z<=0 and x<=0 and c<=0){
		return 1;
	}
	return 0;
}

bool Polygon::containsPoint(const Point&q){
	double direction=0;
	for (size_t w=0;w<vertices.size();++w){
		auto&A=vertices[w];
		auto&B=vertices[(w+1)%vertices.size()];
		auto&C=vertices[(w+2)%vertices.size()];
		direction+=angle(A,B,C);
	}
	std::list<Point> ver;
	if (direction>0){
		ver=std::list<Point>(vertices.begin(),vertices.end());
	}else{
		ver=std::list<Point>(vertices.rbegin(),vertices.rend());
	}
	while (ver.size()>2){
		for (auto w=++ver.begin();w!=--ver.end();++w){
			auto A=*--w;
			auto B=*++w;
			auto C=*++w;
			--w;
			if (angle(A,B,C)>0){
				bool no_points=1;
				for (auto e=vertices.begin();e!=vertices.end();++e){
					if (in_triangle({A,B,C},*e,1)){
						no_points=0;
						break;
					}
				}
				if (no_points){
					if (in_triangle({A,B,C},q)){
						return 1;
					}
					ver.erase(w);
					break;
				}
			}
		}
	}
	if (ver.size()==2){
		auto A=*ver.begin();
		auto B=*++ver.begin();
		auto C=A+vect(A,B).perp();
		auto z=in_triangle({A,B,C},q);
		C=B+vect(B,A).perp();
		auto x=in_triangle({A,B,C},q);
		return z and x;
	}
	if (ver.size()==1){
		auto A=*ver.begin();
		return q==A;
	}
	return 0;
}

template <typename T,typename Y>
bool simPolygon(T q,Y e,bool no_scale=0){
	if (q.vertices.size()!=q.vertices.size()){
		return false;
	}
	if (q.vertices.size()<3){
		return true;
	}
	size_t mw=0;
	double m=vect(q.vertices[0],q.vertices[1]).abs();
	for (size_t w=0;w<q.vertices.size();++w){
		auto A=q.vertices[w];
		auto B=q.vertices[(w+1)%q.vertices.size()];
		auto t=vect(A,B).abs();
		if (t>m){
			mw=w;
			m=t;
		}
	}
	std::rotate(q.vertices.begin(),q.vertices.begin()+mw,q.vertices.end());
	mw=0;
	m=vect(e.vertices[0],e.vertices[1]).abs();
	for (size_t w=0;w<e.vertices.size();++w){
		auto A=e.vertices[w];
		auto B=e.vertices[(w+1)%e.vertices.size()];
		auto t=vect(A,B).abs();
		if (t>m){
			mw=w;
			m=t;
		}
	}
	std::rotate(e.vertices.begin(),e.vertices.begin()+mw,e.vertices.end());
	if (!no_scale){
		e.scale(
			e.vertices[0],
			(vect(q.vertices[0],q.vertices[1])).abs()/
			(vect(e.vertices[0],e.vertices[1])).abs()
		);
	}
	auto tm=vect(e.vertices[0],q.vertices[0]);
	for (size_t w=0;w<e.vertices.size();++w){
		e.vertices[w]=e.vertices[w]+tm;
	}
	auto an=angle(
		vect(e.vertices[0],e.vertices[1]),
		vect(q.vertices[0],q.vertices[1])
	);
	e.rotate(e.vertices[0], an);
	bool res=0;
	res=res or eqPolygon(q,e);
	e.reflect(Line(e.vertices[0],e.vertices[1]));
	res=res or eqPolygon(q,e);
	e.reflect(perp_line(e.vertices[0],e.vertices[1],(e.vertices[0]+e.vertices[1])/2));
	res=res or eqPolygon(q,e);
	e.reflect(Line(e.vertices[0],e.vertices[1]));
	res=res or eqPolygon(q,e);
	return res;
}

template <typename T,typename Y>
bool eqPolygon(const T&q,const Y&e){
	if (q.vertices.size()!=q.vertices.size()){
		return false;
	}
	if (q.vertices.size()==0){
		return true;
	}
	for (size_t r=0;r<e.vertices.size();++r){
		bool not_same=0;
		for (size_t w=0;w<q.vertices.size();++w){
			if (q.vertices[w]!=e.vertices[(r+w)%e.vertices.size()]){
				not_same=1;
			}
		}
		if (!not_same){
			return true;
		}
		not_same=0;
		for (size_t w=0;w<q.vertices.size();++w){
			if (q.vertices[w]!=e.vertices[(e.vertices.size()+r-w)%e.vertices.size()]){
				not_same=1;
			}
		}
		if (!not_same){
			return true;
		}
	}
	return false;
}

template <typename PolCMP,typename EllCMP>
bool cmp(const Shape&q,const Shape&e){
	if (auto w=dynamic_cast<const Polygon*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return PolCMP{}(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Rectangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return PolCMP{}(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Square*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Rectangle*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Square*>(&e)){
			return PolCMP{}(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Triangle*>(&q)){
		if (auto r=dynamic_cast<const Polygon*>(&e)){
			return PolCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Triangle*>(&e)){
			return PolCMP{}(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Ellipse*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return EllCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return EllCMP{}(*w,*r);
		}
	}
	if (auto w=dynamic_cast<const Circle*>(&q)){
		if (auto r=dynamic_cast<const Ellipse*>(&e)){
			return EllCMP{}(*w,*r);
		}
		if (auto r=dynamic_cast<const Circle*>(&e)){
			return EllCMP{}(*w,*r);
		}
	}
	return false;
}

struct PolSim{
	template <typename T,typename Y>
	bool operator()(T q,Y e){
		return simPolygon(q,e);
	}
};

struct EllSim{
	template <typename T,typename Y>
	bool operator()(T q,Y e){
		return abs(q.a*e.b-q.b*e.a)<zero;
	}
};

struct PolCon{
	template <typename T,typename Y>
	bool operator()(T q,Y e){
		return simPolygon(q,e,1);
	}
};

struct EllCon{
	template <typename T,typename Y>
	bool operator()(T q,Y e){
		return abs(q.a-e.a)<zero;
	}
};

struct PolEq{
	template <typename T,typename Y>
	bool operator()(T q,Y e){
		return eqPolygon(q,e);
	}
};

struct EllEq{
	template <typename T,typename Y>
	bool operator()(T q,Y e){
		return abs(q.a-e.a)<zero and (q.f1-e.f1).abs()<zero and (q.f2-e.f2).abs()<zero;
	}
};

bool operator==(const Shape&q,const Shape&e){
	return cmp<PolEq,EllEq>(q,e);
}

bool Shape::isCongruentTo(const Shape&q){
	return cmp<PolCon,EllCon>(*this,q);
}

bool Shape::isSimilarTo(const Shape&q){
	return cmp<PolSim,EllSim>(*this,q);
}

bool operator!=(const Shape&q,const Shape&e){
	return !(q==e);
}
