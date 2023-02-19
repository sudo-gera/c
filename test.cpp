#define _GNU_SOURCE
#include <boost/stacktrace.hpp>
#include <iostream>

int main(){
    std::cout<<boost::stacktrace::stacktrace();
}

