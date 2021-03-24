// array of array of используется для описания многомерных массивов
// пример: array of array of array of integer - трёхмерный массив целох чисел

// перегрузка функций - определение нескольких функций с одним названием и разными типами данных.
// При вызове по типам аргумента угадывается, какая функция должна быть вызвана
// типы array of integer и array of array of integer - разные
// Функции определённые только для одного из них не будут работать с другим

// многие функции определяются для одномерных массивов, потом двумерных, трёхмерных и так далее

// функция для вычисления длины строк и массивов
// нужны для единообразия взятия длины
// не надо думать, где .length а где length()
function len(q:
	string):integer;begin len:=q.length;end;
function len(q:
	array of string):integer;begin len:=length(q);end;
function len(q:
	array of array of string):integer;begin len:=length(q);end;
function len(q:
	array of array of array of string):integer;begin len:=length(q);end;
function len(q:
	array of integer):integer;begin len:=length(q);end;
function len(q:
	array of array of integer):integer;begin len:=length(q);end;
function len(q:
	array of array of array of integer):integer;begin len:=length(q);end;
function len(q:
	array of real):integer;begin len:=length(q);end;
function len(q:
	array of array of real):integer;begin len:=length(q);end;
function len(q:
	array of array of array of real):integer;begin len:=length(q);end;

// процедура для добавления элемента в конец массива
// общий вид: 
// setlength(array,new_length) устанавливает новую днину массива
// в данном случае, это на 1 больше, чем старая длина, так как нужно добавить только 1 элемент
// a[length(a)-1] обращение к последнему элементу массива, динамические массивы нумеруются с 0
// сначала определяется для различных массивов типа integer
procedure push_back(var a: array of
	integer; value:
	integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of integer; value:
	array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of integer; value:
	array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of integer; value:
	array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of integer; value:
	array of array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of integer; value:
	array of array of array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of array of integer; value:
	array of array of array of array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
// далее для массивов типа real
procedure push_back(var a: array of
	real; value:
	real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of real; value:
	array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of real; value:
	array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of real; value:
	array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of real; value:
	array of array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of real; value:
	array of array of array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of array of real; value:
	array of array of array of array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
// далее для массивов типа string
procedure push_back(var a: array of
	string; value:
	string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of string; value:
	array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of string; value:
	array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of string; value:
	array of array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of string; value:
	array of array of array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of string; value:
	array of array of array of array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;

// преобразователь чего-либо к массиву (something to array)
// что-либо должно быть итерируемо, то есть можно пройти по элементам циклом foreach
// цикл foreach [item] in [array] do
// по очереди записывает эдементы цикла в переменную [item]
// и для каждого запускает тело цикла
// некоторые типы данных можно итерировать, но нельзя обращаться по индексам
// общий вид:
// foreach w in a do
// тут w становится по почереди каждым элементом a
// push_back(result,a)
// тут эта переменная добавляется в уонец массива
// переменная result определяется в начале каждой функции
// имеет тот же тип, что и возвращаемое значение функции
// если в функции не определено, что возвращать, возвращается значение этой переменной
// сначала определим для типа sequence of integer
// а так же sequence of array of integer
// sequence of array of array of integer и так далее
function stoa(a:sequence of
	integer): array of
	integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of integer): array of
	array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of integer): array of
	array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of integer): array of
	array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of integer): array of
	array of array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of array of integer): array of
	array of array of array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
// потом для типа sequence of real
function stoa(a:sequence of
	real): array of
	real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of real): array of
	array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of real): array of
	array of array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of real): array of
	array of array of array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of real): array of
	array of array of array of array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of array of real): array of
	array of array of array of array of array of real;begin foreach var w in a do push_back(result,w);end;
// далее тип sequence of string
function stoa(a:sequence of
	string): array of
	string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of string): array of
	array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of string): array of
	array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of string): array of
	array of array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of string): array of
	array of array of array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of array of string): array of
	array of array of array of array of array of string;begin foreach var w in a do push_back(result,w);end;
// тип set of integer
function stoa(a:set of
	integer): array of
	integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of integer): array of
	array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of integer): array of
	array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of array of integer): array of
	array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
// тип set of string
function stoa(a:set of
	string): array of
	string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of string): array of
	array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of string): array of
	array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of array of string): array of
	array of array of array of string;begin foreach var w in a do push_back(result,w);end;

// функция, которая принимает что-то и возвращает массив с элементами того же типа, что и входной аргумент
// например, если в функцию передать переменную типа array of integer
// то вернётся array of array of integer
// возвращаемый массив может содержать в себе что-то
// tarr(integer)
// создаёт массив с типом integer и возвращает его
function tarr(q:
	integer):array of
	integer;
	begin
		tarr:=arr(0);
	end;
// тут функция tarr принимает массив
// метод select массивов принимает функцию
// которая применяется ко всем элементам
// возвращается последовательность (sequence) результатов
// запись x->tarr(x) означает лямбда-функцию
// которая принимает 1 аргумент и возвращает
// результат выполнения tarr от него
// stoa помогает перейти от sequence к массиву
function tarr(q:
	array of integer):array of
	array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of integer):array of
	array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of integer):array of
	array of array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of integer):array of
	array of array of array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of array of integer):array of
	array of array of array of array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
// ананлогично для массивов real
function tarr(q:
	real):array of
	real;
	begin
		tarr:=arr(0.0);
	end;
function tarr(q:
	array of real):array of
	array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of real):array of
	array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of real):array of
	array of array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of real):array of
	array of array of array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of array of real):array of
	array of array of array of array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;

// функция для создания пустых массивов
// как tarr но теперь гарантируется, что полученный массив пустой
function emparr(q:
	integer):array of
	integer;
	begin
		result:=arr(0);
		SetLength(result,0);
		emparr:=result;
	end;
function emparr(q:
	array of integer):array of
	array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of integer):array of
	array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of integer):array of
	array of array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of integer):array of
	array of array of array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of array of integer):array of
	array of array of array of array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	real):array of
	real;
	begin
		result:=arr(0.0);
		SetLength(result,0);
		emparr:=result;
	end;
function emparr(q:
	array of real):array of
	array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of real):array of
	array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of real):array of
	array of array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of real):array of
	array of array of array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of array of real):array of
	array of array of array of array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;

// функция для преобразования строки в число
// integer.tryparse(string,integer) пытается
// преобразовать переданную строку в переданную числовую переменную 
// возвращается ответ на вопрос получилось ли преобразовать? (true/false)
function int(q:string):integer;
begin
	var e:=0;
	if not(integer.tryparse(q,e)) then println('error in int');
	int:=e;
end;

// массив cache для "хранения" строк в массиве для целых чисел
// если надо записать строку в массив для чисел
// стоит вызвать tocache от этой строки перед записью
// тогда строка добавится в массив cache
// а в числовую переменную запишется её индекс
// для испльзования строки потом достаточно обратиться к массиву cache
// по имеющемуся индексу
var cache: array of string;
function tocache(q:string):integer;
begin
	push_back(cache,q);
	tocache:=len(cache)-1;
end;

// приближение числа pi 
// это не особо точно, в конце нехватает 
// всего лишь бесконечности цифр
var pi:=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989;

// функция atan2 возвращает угол наклона вектора
// по двум его координатам
// просто перебираются все возможные положения вектора
function atan2(a:real;s:real):real;
begin
	if (a<0) and (s<0)then atan2:= arctan(a/s)-pi;
	if (a<0) and (s=0)then atan2:= -pi/2;
	if (a<0) and (s>0)then atan2:= arctan(a/s);
	if (a=0) and (s<0)then atan2:= 0;
	if (a=0) and (s=0)then atan2:= 0;
	if (a=0) and (s>0)then atan2:= 0;
	if (a>0) and (s<0)then atan2:= arctan(a/s)+pi;
	if (a>0) and (s=0)then atan2:= pi/2;
	if (a>0) and (s>0)then atan2:= arctan(a/s);
end;

// функция, которая преобразует выражение a*cos(x+b)+c*cos(x+d) в e*cos(x+f)
// массивы d1 и d2 содержат a,b и c,d соответственно
// возвращается массив с числами e и f
function makesum(d1:array of real;d2:array of real):array of real;
begin
	// создадим функцию ff которая для данного числа x
	// вернёт a*cos(x+b)+c*cos(x+d)
	var ff:real->real:= x-> (d1[0]*cos(x+d1[1])+d2[0]*cos(x+d2[1]));
	// найдём точку максимум функции ff
	// так как ff имеет вид e*cos(x+f)
	// то полученная точка будет равна -f + 2*pi*n где n - какое-то целое

	// для этого воспользуемся тернарным посиком максимума
	// для него найдём область авпуклости вверх
	// для этого расчитаем значение функции в некоторых точках
	// это множитель шага
	var j:=16;
	// тут будут храниться результаты вычислений
	// в формате [ff(x),x]
	var aa:array of array of real;
	// на случай если область выпуклости вверх будет в 0
	// и как следствие, разделена на 2 части
	// делаем просмотр не до 2*pi а до 4*pi
	for var w:=0 to round(j*pi*4) do
	begin
		// домножим конечное значение цикла на j
		// а в цикле разделим переменную на j
		push_back(aa,arr(ff(w/j),w/j));
	end;
	// рассмотрим несколько подряд идущих точке
	// это количество подряд идущих точек, которое будем рассматривать
	var k:=4;
	// у последовательно идущих точек, которая содержит максимум
	// будет наибольшая сумма
	// так можно найти последовательность. которая модержит в себе
	// участок выпуклости вверх, где искомый максимум
	// для этого расчитаем сумму на каждой последовательности
	// k подряд идущих точек
	// тут будут суммы последовательностей
	var s2:=emparr(0.0);
	// в переменной w хранится индекс
	// первой переменной последовательности
	for var w :=0 to len(aa)-1 do
	begin
		// добавляем 0 чтобы потом к нему прибавлять
		// элементы последовательности
		push_back(s2, 0.0 );
		// проходим по последовательности и прибавляем в сумму элементы
		for var ww := w to min(w+k-1,len(aa)-1) do
		begin
			s2[len(s2)-1]+=aa[ww][0];
		end;
	end;
	// ищем макстмум
	// тут будет значение максимальной суммы
	var mv:=s2[0];
	// тут индекс максимума
	var mi:=0;
	// проходим по массиву s2 и находим максимум
	for var w :=0 to len(s2)-1 do
	begin
		if s2[w]>mv then
		begin
			mv:=s2[w];
			mi:=w;
		end;
	end;
	// в переменнцю s записываем найденный индекс
	var s:=mi;
	// массив aa обрезаем по полученной последовательности
	// теперь тут будут тоько элементы последовательности
	// содержащей область выпуклости вверх
	aa:=aa[s:s+k];
	// создаём переменные st и fi
	// для начала и конца тернарного поиска соответственно
	var fi:=aa[0][1];
	var st:=aa[len(aa)-1][1];
	// кол-во итераций тернарного поиска
	var l:=64;
	for var t :=1 to l do
	begin
		// делим отрезок на 3 части и записываем 
		// координаты полученных разрезов в пеерменные
		// cl и cr
		var cl:=(st+st+fi)/3;
		var cr:=(st+fi+fi)/3;
		// проверяем значения ff в этих точках
		// и сдвигаем границы отрезка выпуклости вверх
		if ff(cl) < ff(cr) then
			st:=cl;
		if ff(cl) > ff(cr) then
			fi:=cr;
		if ff(cl) = ff(cr) then
		begin
			st:=cl;
			fi:=cr;
		end;
	end;
	// полученный максимум записываем
	var res:=(fi+st)/2;
	// приводим в полуинт
	while res>pi*2 do res-=pi*2;
	while res<=0 do res+=pi*2;
	makesum:= arr(ff(res),2*pi-res);
end;
begin
	var task:=2;
	if task=1 then
	begin
		var q0:='';
		read(q0);
		var q1:=q0[2:len(q0)].split(')(');
		var q2:=stoa(q1.select(w->w.split('+')));
		var q3:=stoa(q2.select(w->stoa(w.select(e->arr(e.split('x^')[0],e.split('x^')[1].split('y^')[0],e.split('y^')[1])))));
		var q:=stoa(q3.select(w->stoa(w.select(e->stoa(e.select(r->int(r)))))));
		var a:array of array of integer;
		foreach w: array of integer in q[0] do
			foreach e: array of integer in q[1] do
				push_back(a,arr(w[0]*e[0],w[1]+e[1],w[2]+e[2]));
		var a1:=stoa(a.select(w->arr(w[0],tocache('x^'+w[1]+'y^'+w[2]))));
		// var d:dictionary<string,integer>;
		var dk:set of string;
		foreach w:array of integer in a1 do
		begin
			dk+=[cache[w[1]]];
		end;
		var d:=stoa(dk).todictionary(x->x,x->0);
		foreach w:array of integer in a1 do
			d[cache[w[1]]]+=w[0];
		var s:array of string;
		foreach w:string in dk do
		begin
			push_back(s,d[w].tostring()+w);
		end;
		println(string.join('+',s));
	end;
	if task=3 then
	begin
		var he:=0;
		var wi:=0;
		read(wi,he);
		var d:array of array of integer;
		for var w:=1 to he do
		begin
			push_back(d,emparr(0));
			for var e:= 1 to wi do
			begin
				var c:=0;
				read(c);
				push_back(d[w-1],c);
			end;
		end;
		d:=d[::-1];
		var ca :=emparr(emparr(emparr(0)));
		for var w:=1 to he do
		begin
			push_back(ca,emparr(emparr(0)));
			for var e:= 1 to wi do
			begin
				var x:=w-1;
				var y:=e-1;
				if (x=0) and (0=y) then
				begin
					push_back(ca[w-1],arr(d[x][y],-1,-1));
				end else
				if x=0 then
				begin
					push_back(ca[w-1],arr(d[x][y]+ca[x][y-1][0],x,y-1));
				end else
				if y=0 then
				begin
					push_back(ca[w-1],arr(d[x][y]+ca[x-1][y][0],x-1,y));
				end else
				begin
					if ca[x-1][y][0]<ca[x][y-1][0] then
					begin
						push_back(ca[w-1], arr(d[x][y]+ca[x-1][y][0],x-1,y));
					end
					else
					begin
						push_back(ca[w-1], arr(d[x][y]+ca[x][y-1][0],x,y-1));
					end;
				end;
			end;
		end;
		var p:=arr(len(d)-1,len(d[0])-1);
		var ext:=emparr(emparr(0));
		while (p[0]<>-1) or (p[1]<>-1) do
		begin
			push_back(ext,p);
			p:=arr(ca[p[0]][p[1]][1],ca[p[0]][p[1]][2]);
		end;
		ext:=ext[::-1];
		foreach w:array of integer in ext do
			println(w[1]+1,w[0]+1)
	end;
	if task=2 then
	begin


		var he:=0;
		var wi:=2;
		read(he);
		var d:array of array of real;
		for var w:=1 to he do
		begin
			push_back(d,emparr(0.0));
			for var e:= 1 to wi do
			begin
				var c:=0;
				read(c);
				push_back(d[w-1],c);
			end;
		end;



		var d1:=stoa(d.select(w->arr( 1.0*w[0]*w[0]+w[1]*w[1] , pi-atan2(w[1],w[0])*2 )         ));




		var f1:=d1[0];
		foreach w:array of real in d1[1:] do
		begin
			f1:=makesum(f1,w);
		end;
		var f:=f1[1]/2;
		if (pi/4<f) and (f<3*pi/4) then
			println('y='+tan(pi/2-f)+'*x')
		else
			println('x='+tan(f)+'*y');

{}
	end;
end.