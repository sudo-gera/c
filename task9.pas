const pi=3.14159265358979323846;
const n = 2;
var a,b,k1,k2,a1,a2,s:real;
i:integer;
sp:array[1..n] of array[1..2] of integer;
sp1:array[1..n] of array[1..2] of real;
begin
  Writeln('Введите целые координаты точек. Количество: ',n);
  for i:=1 to n do 
  begin
    read(sp[i][1]);//Координата x
    read(sp[i][2]);//Координата y
    sp1[i][1]:=(sp[i][1]*sp[i][1]+sp[i][2]*sp[i][2])/2;
    if sp[i][1]=0 then sp1[i][2]:=pi/2
    else sp1[i][2]:=2*arctan((sp[i][2])/(sp[i][1]));
  end;
  k1:=sp[1][1];
  k2:=sp[1][2];
  for i:=2 to n do
  begin
    a:=k1*cos(sp[i][2])+sp[i][1]*cos(k2);
    b:=k1*sin(sp[i][2])+sp[i][1]*sin(k2);
    k1:=a*a+b*b;
    if k1<>0 then
    begin
      a:=a/k1;
      b:=b/k1;
      a1:=arctan(sqrt(1-a*a)/a);//arccos(a)
      a2:=arctan(b/sqrt(1-b*b));//arcsin(b)
      if (a1>=0) and (a2>=0) then
        k2:=a1
      else if (a1>=0) and (a2<0) then
        k2:=a2
      else if (a1<0) and (a2>=0) then
        k2:=a1
      else if (a1<0) and (a2<0) then
        k2:=-a1;
    end;  
  end;
  for i:=1 to n do s:=s+sp1[i][1];
  s:=s-k1;
  if cos(k2)<>0 then writeln('k = ',tan(k2))
  else writeln('x = 0');
  writeln('Минимальная сумма квадратов расстояний равна ', s);
end.