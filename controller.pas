uses System.IO, System.Net;
 
function urlopen(url:string):string;
var 
	html : string;
	// url : string := 'http://programmersforum.ru/showthread.php?p=1658760';
begin
	var myRequest : HttpWebRequest := HttpWebRequest(WebRequest.Create(url));
	myRequest.Method := 'GET';
	var myResponse : WebResponse := myRequest.GetResponse();
	var sr : StreamReader := new StreamReader(myResponse.GetResponseStream(), System.Text.Encoding.UTF8);
	html := sr.ReadToEnd();
	sr.Close();
	myResponse.Close();
	urlopen:=html;  
	// writeln(html); // в html как раз и хранится код сайта
end;



begin
	var url:=urlopen('https://sudo-gera.github.io/controller/');
	println(1,2,3);
	println(url);
end.