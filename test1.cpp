#include<vector>
#include<exception>
#include<fstream>
#include<climits>

#undef throw

#define CC const
#define MM Matrix
#define RR Residue
#define SM SquareMatrix

inline bool equals(double x,double y){
return x-y<1e-6&&x-y>-1e-6;
}

CC size_t bigPrime=1493;

void testMM(){
//Nowlet'stestmatrices.
using std::vector;


CC MM<4,5,RR<17>>am={{8,-4,-5,5,9},
{1,-3,-5,0,-7},
{7,-5,1,4,1},
{3,-1,3,2,5}};
CC MM<5,4,RR<17>>bm={{4,0,3,2},
{1,-7,4,5},
{7,1,5,3},
{-5,-3,-3,-1},
{1,-5,2,3}};
//CC MM<4,5,RR<17>>am=a;
//CC MM<5,4,RR<17>>bm=b;

if(am.rank()!=4||bm.rank()!=3)
throw std::runtime_error("rank()methodfailed.");
CC SM<4,RR<17>>ab={{-23,-37,-14,3},
{-41,51,-48,-49},
{11,19,-4,-9},
{27,-21,24,23}};

CC auto abm=am*bm;
if(abm!=SM<4,RR<17>>(ab))
throw std::runtime_error("matrixmultiplicationorCC ructorsfailed.");

CC auto aminusb=am-bm.transposed();
CC MM<4,5,RR<17>>diff={{4,-5,-12,10,8},
{1,4,-6,3,-2},
{4,-9,-4,7,-1},
{1,-6,0,3,2}};
if(aminusb!=diff)
throw std::runtime_error("Additionorsubtractionfailed.");

auto newMM=RR<17>(2)*aminusb*bm;
newMM[2][2]=RR<17>(1);

if(newMM.det()!=RR<17>(14420160))
throw std::runtime_error("Determinantiswrong.");

if(newMM.trace()!=RR<17>(-345))
throw std::runtime_error("Traceiswrong.");

MM<4,4,RR<17>>finiteUnity;
for(int i=0;i<4;++i){
for(int j=0;j<4;++j){
finiteUnity[i][j]=RR<17>(i==j);
}
}
if(newMM.inverted()*newMM!=finiteUnity)
throw std::runtime_error("A*A^(-1)mustbeequaltounitymatrix.");

// std::cerr<<"Testsoverthefinitefieldpassed!\n";

// std::ifstream in("matr.txt");
// SM<20>bigMM;
// for(int i=0;i<20;++i)
// for(int j=0;j<20;++j)
// in>>bigMM[i][j];

// vector<vector<double>>bigInvertedMM(20,vector<double>(20));
// for(int i=0;i<20;++i)
// for(int j=0;j<20;++j)
// in>>bigInvertedMM[i][j];

// auto anotherMM=bigMM;
//bigMM.inverted();
// bigMM.invert();
// std::cerr<<"Bigmatrixinverted!\n";
// for(int i=0;i<20;++i){
// auto row=bigMM.getRow(i);
// auto anotherRow=bigInvertedMM[i];
// for(int j=0;j<20;++j){
// if(!equals(static_cast<double>(row[j]),anotherRow[j])){
// throw std::runtime_error("Invertedmatrixisincorrect!");
// }
// }
// }
// std::cerr<<"Invertedmatrixiscorrect!\n";
// bigMM*=anotherMM;
// std::cerr<<"MMmultipliedbyitsinvertedmatrix!\n";
// SM<20>unity=SM<20>();
// for(int i=0;i<20;++i){
// for(int j=0;j<20;++j){
// unity[i][j]=(i==j);
// }
// }

// for(int j=0;j<20;++j){
// auto column=bigMM.getColumn(j);
// auto unityColumn=unity.getColumn(j);
// for(int i=0;i<20;++i){
// if(column[i]!=unityColumn[i]){
// throw std::runtime_error("ProductofAandA^(-1)mustbeequaltounitymatrix.");
// }
// }
// }

// std::cerr<<"ResultofA*A^(-1)iscorrect!\n";

// auto det=anotherMM.det();
// std::cerr<<"Determinantiscomputed!\n";
//det/=20;
// for(int i=0;i<20;++i)
// anotherMM[0][i]/=det;
//nowanotherMMisorthogonalmatrix
// if(anotherMM.det()!=1)
// throw std::runtime_error("Dividingarowbydetmustmakethedeterminantequalto1.");

// auto transposedMM=anotherMM.transposed();
// if((anotherMM*=transposedMM).det()!=1)
// throw std::runtime_error("Productoftwomatriceswithdet=1mustgivethematrixwithsamedeterminant.");

}
