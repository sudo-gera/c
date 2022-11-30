#include <iostream>
#include <string>

using namespace std::literals;

std::string popen(std::string q){
	std::string s;
	auto pipe=popen(q.c_str(), "r");
	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(pipe)) != EOF) { // standard C I/O file reading loop
		s+=static_cast<char>(c);
	}
	pclose(pipe);
	return s;
}

std::string python(std::string q){
	return popen("python3 -c \""+q+"\"");
}




int main(){

}


