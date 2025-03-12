#include <bits/stdc++.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>


#define FORWARD(val) (std::forward<decltype(val)>(val))

// clang-format off
const char* escape[] = {
    "\\x00", "\\x01", "\\x02", "\\x03", "\\x04", "\\x05", "\\x06", "\\x07", "\\x08", "\\t",   "\\n",   "\\x0b", "\\x0c", "\\r",   "\\x0e", "\\x0f",
    "\\x10", "\\x11", "\\x12", "\\x13", "\\x14", "\\x15", "\\x16", "\\x17", "\\x18", "\\x19", "\\x1a", "\\x1b", "\\x1c", "\\x1d", "\\x1e", "\\x1f",
    " ",     "!",     "\"",    "#",     "$",     "%",     "&",     "\'",    "(",     ")",     "*",     "+",     ",",     "-",     ".",     "/",    
    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     ":",     ";",     "<",     "=",     ">",     "?",    
    "@",     "A",     "B",     "C",     "D",     "E",     "F",     "G",     "H",     "I",     "J",     "K",     "L",     "M",     "N",     "O",    
    "P",     "Q",     "R",     "S",     "T",     "U",     "V",     "W",     "X",     "Y",     "Z",     "[",     "\\\\",  "]",     "^",     "_",    
    "`",     "a",     "b",     "c",     "d",     "e",     "f",     "g",     "h",     "i",     "j",     "k",     "l",     "m",     "n",     "o",    
    "p",     "q",     "r",     "s",     "t",     "u",     "v",     "w",     "x",     "y",     "z",     "{",     "|",     "}",     "~",     "\\x7f",
    "\\x80", "\\x81", "\\x82", "\\x83", "\\x84", "\\x85", "\\x86", "\\x87", "\\x88", "\\x89", "\\x8a", "\\x8b", "\\x8c", "\\x8d", "\\x8e", "\\x8f",
    "\\x90", "\\x91", "\\x92", "\\x93", "\\x94", "\\x95", "\\x96", "\\x97", "\\x98", "\\x99", "\\x9a", "\\x9b", "\\x9c", "\\x9d", "\\x9e", "\\x9f",
    "\\xa0", "\\xa1", "\\xa2", "\\xa3", "\\xa4", "\\xa5", "\\xa6", "\\xa7", "\\xa8", "\\xa9", "\\xaa", "\\xab", "\\xac", "\\xad", "\\xae", "\\xaf",
    "\\xb0", "\\xb1", "\\xb2", "\\xb3", "\\xb4", "\\xb5", "\\xb6", "\\xb7", "\\xb8", "\\xb9", "\\xba", "\\xbb", "\\xbc", "\\xbd", "\\xbe", "\\xbf",
    "\\xc0", "\\xc1", "\\xc2", "\\xc3", "\\xc4", "\\xc5", "\\xc6", "\\xc7", "\\xc8", "\\xc9", "\\xca", "\\xcb", "\\xcc", "\\xcd", "\\xce", "\\xcf",
    "\\xd0", "\\xd1", "\\xd2", "\\xd3", "\\xd4", "\\xd5", "\\xd6", "\\xd7", "\\xd8", "\\xd9", "\\xda", "\\xdb", "\\xdc", "\\xdd", "\\xde", "\\xdf",
    "\\xe0", "\\xe1", "\\xe2", "\\xe3", "\\xe4", "\\xe5", "\\xe6", "\\xe7", "\\xe8", "\\xe9", "\\xea", "\\xeb", "\\xec", "\\xed", "\\xee", "\\xef",
    "\\xf0", "\\xf1", "\\xf2", "\\xf3", "\\xf4", "\\xf5", "\\xf6", "\\xf7", "\\xf8", "\\xf9", "\\xfa", "\\xfb", "\\xfc", "\\xfd", "\\xfe", "\\xff",
};
// clang-format on

auto repr_s(std::string data) {
    std::string result = "'";
    for (auto c : data) {
        result += escape[c];
    }
    result += "'";
    return result;
}

auto repr(auto&& val) {
    std::stringstream a;
    a << FORWARD(val);
    return repr_s(a.str());
}

struct sys_msg_printer : std::stringstream {

#define add_syscall(name)                                                \
    auto name(auto... args) {                                            \
        errno = 0;                                                       \
        auto ret = ::name(args...);                                      \
        if (errno) {                                                     \
            perror("\n <<< ERROR >>>\n" #name " Failed");                \
            std::cerr << "\n <<< ARGS >>> " << std::endl;                \
            (void)((std::cerr << "    " << repr(args) << "\n"), ..., 0); \
            if (str().size()) {                                          \
                std::cerr << "\n <<< MESSAGE >>> " << std::endl;         \
                std::cerr << str() << std::endl;                         \
            }                                                            \
            std::cerr << std::endl;                                      \
            throw std::runtime_error("syscall failed");                  \
        }                                                                \
        std::stringstream tmp;                                           \
        swap(tmp);                                                       \
        return ret;                                                      \
    }

    add_syscall(write)
    add_syscall(socket)
    add_syscall(fcntl)
    add_syscall(inet_pton)
};

sys_msg_printer sys;

auto create_non_blocking_socket(){
    int s = sys.socket(AF_INET, SOCK_STREAM, 0);
    int flags = sys.fcntl(s, F_GETFL, 0);
    flags |= O_NONBLOCK;
    sys.fcntl(s, F_SETFL, flags);
    return s;
}

auto create_connection(const char* addr, uint16_t port){
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr = inet_pton(addr);


}

int main() {
    sys << "aaaaaaaaa" << std::endl;
    int t = sys.write(1, "hello\n", 6);
    std::cout << t << std::endl;

    sys << "sssssssss";
    t = sys.write(9, "hello\n", 6);
    std::cout << t << std::endl;
}
