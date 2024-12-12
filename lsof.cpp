#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <tuple>
#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <concepts>
#include <deque>
#include <vector>
#include <optional>
#include <unordered_map>
#include <variant>
#include <iomanip>
#include <functional>
#include <list>

#if __cplusplus < 202000L
#error "need c++20"
#endif

using std::operator""s;

#define FORWARD(arg) std::forward<decltype(arg)>(arg)
#define THROW_ON_ERRNO(expr, ...) (([&](){ errno = 0 ; auto res__ = (expr) ; if (errno) { throw std::runtime_error{std::string() + "ERROR: " + #expr + ": " + strerror(errno) + " "s + quoted_all(__VA_ARGS__)} ; } ; return res__ ; })())
#define CATCH(e) catch(std::exception& e)

template<std::integral T>
auto quoted(T val){
    return std::to_string(val);
}
auto quoted(std::string val){
    std::stringstream ss;
    ss << std::quoted(val);
    return ss.str();
}

auto quoted_all(auto&&...args){
    std::string data[] = {quoted(FORWARD(args))...};
    std::string res;
    for (auto& s: data){
        if (&s != &data[0]){
            res += ", "s;
        }
        res += s;
    }
    return res;
}

struct dir_entry{
    std::string name;
    ino_t inode;
};

template<bool almost_all>
auto list_dir(std::string dir_path){
    auto dir = std::unique_ptr<DIR,
        decltype([](DIR* dir){THROW_ON_ERRNO(closedir(dir));})
    >(THROW_ON_ERRNO(opendir(dir_path.data()), dir_path));
    std::vector<dir_entry> content;
    while (dirent* t = THROW_ON_ERRNO(readdir(dir.get()))){
        if constexpr(almost_all){
            if (strcmp(t->d_name, ".") == 0){
                continue;
            }
            if (strcmp(t->d_name, "..") == 0){
                continue;
            }
        }
        content.push_back({
            t->d_name,
            t->d_ino,
        });
    }
    return content;
}

auto symlink_to_filename(std::string link_path){
    std::string filename;
    filename.resize(256);
    THROW_ON_ERRNO(readlink(link_path.data(), filename.data(), filename.size()));
    filename.resize(strlen(filename.data()));
    return filename;
}


// struct net_record1{
//     std::string loc_addr;
//     std::string rem_addr;
//     ino_t inode;
//     net_type type;
// };

struct net_record{
    struct net_types{
        enum net_type{unknown, tcp4, udp4, tcp6, udp6};
    };
    uint16_t loc_port;
    std::string loc_addr;
    uint16_t rem_port;
    std::string rem_addr;
    ino_t inode;
    net_types::net_type type;
};

auto load_spaced_file(std::string path, auto process_line){
    auto file = std::unique_ptr<FILE,
        decltype([](FILE* f){THROW_ON_ERRNO(fclose(f));})
    >(THROW_ON_ERRNO(fopen(path.data(), "r"), path));
    std::string line;
    size_t line_num = 0;
    while (not feof(file.get())){
        int c = fgetc(file.get());
        if (c != '\n' and c != EOF){
            line += c;
            continue;
        }
        std::array<std::array<char, 1024>, 16> data;
        memset(&data, 0, sizeof(data));
        if (sscanf(
            line.c_str(),
            " %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s %1023s ",
            data[0].data(),
            data[1].data(),
            data[2].data(),
            data[3].data(),
            data[4].data(),
            data[5].data(),
            data[6].data(),
            data[7].data(),
            data[8].data(),
            data[9].data(),
            data[10].data(),
            data[11].data(),
            data[12].data(),
            data[13].data(),
            data[14].data(),
            data[15].data()
        )>0 and line_num){
            process_line(data);
        }
        line.clear();
        line_num += 1;
    }
}

auto load_one_net(std::string path){
    std::unordered_map<ino_t, net_record> n;
    load_spaced_file(path, [&](auto& data){
        try{
            net_record tmp1;
            auto& tmp = tmp1;
            tmp1.inode = (ino_t)std::stoll(data[9].data());
            tmp1.loc_addr = data[1].data();
            tmp1.rem_addr = data[2].data();
            std::array<std::string*, 2> addr_ptrs = {&tmp1.loc_addr, &tmp1.rem_addr};
            for (auto addr_ptr : addr_ptrs){
                auto& addr = *addr_ptr;
                if (addr.size() < 5 or addr.end()[-5] != ':'){
                    throw std::runtime_error{"cannot process net addr " + quoted(addr)};
                }
                char* end_ptr = nullptr;
                uint16_t port = std::strtoull(&addr.end()[-4], &end_ptr, 16);
                if (addr_ptr == &tmp1.loc_addr){
                    tmp1.loc_port = port;
                }else
                if (addr_ptr == &tmp1.rem_addr){
                    tmp1.rem_port = port;
                }else
                {
                    assert(false);
                }
                if (addr.size() == 8+1+4){
                    char* end_ptr = nullptr;
                    auto addr_int = std::strtoull(addr.data(), &end_ptr, 16);
                    addr.clear();
                    addr += std::to_string(addr_int % 256);
                    addr += ".";
                    addr += std::to_string(addr_int / 256 % 256);
                    addr += ".";
                    addr += std::to_string(addr_int / 256 / 256 % 256);
                    addr += ".";
                    addr += std::to_string(addr_int / 256 / 256 / 256 % 256);
                }else
                if (addr.size() == 32+1+4){
                    auto data = addr;
                    auto data_ptr = data.data();
                    addr.clear();
                    for (size_t i = 0 ; i < 8 ; ++i){
                        addr += *data_ptr++;
                        addr += *data_ptr++;
                        addr += *data_ptr++;
                        addr += *data_ptr++;
                        addr += ":";
                    }
                    addr.pop_back();
                }else{
                    throw std::runtime_error{"cannot process net addr " + quoted(addr)};
                }
                if (addr_ptr == &tmp1.loc_addr){
                    tmp1.loc_addr = addr;
                }else
                if (addr_ptr == &tmp1.rem_addr){
                    tmp1.rem_addr = addr;
                }else
                {
                    assert(false);
                }
            }
            if (n.count(tmp1.inode)){
                std::cerr << "WARNING: Duplicate inode " << tmp.inode << " in " << path << std::endl;
            }
            n[tmp.inode] = tmp;
        }CATCH(e){
            std::cerr << e.what() << std::endl;
        }
    });
    return n;
}

auto load_net(std::string pid_str){
    class std::unordered_map<ino_t, net_record> output;
    std::array<std::pair<std::string, net_record::net_types::net_type>, 4> net_files = {{
        {"/proc/" + pid_str + "/net/tcp",  net_record::net_types::tcp4},
        {"/proc/" + pid_str + "/net/udp",  net_record::net_types::udp4},
        {"/proc/" + pid_str + "/net/tcp6", net_record::net_types::tcp6},
        {"/proc/" + pid_str + "/net/udp6", net_record::net_types::udp6},
    }};
    for (auto& net_file: net_files){
        auto nets = load_one_net(net_file.first);
        for (auto& net: nets){
            net.second.type = net_file.second;
            output[net.first] = net.second;
        }
    }
    return output;
}

struct record_for_having_resource{
    pid_t pid;
    ino_t inode;
    std::string path;
    std::optional<int> fd;
    struct stat st;
    std::optional<net_record> net;
    std::string exe;
};

auto get_all_files(){
    std::vector<record_for_having_resource> all_files;
    auto pid_dirs = list_dir<1>("/proc/");
    for (auto& pid_dir: pid_dirs){
        pid_t pid = 0;
        try{
            pid = (pid_t)std::stoi(pid_dir.name);
            if (std::to_string(pid) != pid_dir.name){
                continue;
            }
        }catch(...){
            continue;
        }
        try{
            auto net = load_net(pid_dir.name);
            auto files = list_dir<1>("/proc/"s+pid_dir.name+"/fd");
            for (auto& file: files){
                try{
                    int fd = std::stoi(file.name);
                    struct stat st;
                    THROW_ON_ERRNO(stat(("/proc/"s+pid_dir.name+"/fd/"+file.name).data(), &st), "/proc/"s+pid_dir.name+"/fd/"+file.name);
                    all_files.push_back({
                        .pid = pid,
                        .inode = st.st_ino,
                        .path = symlink_to_filename("/proc/"s+pid_dir.name+"/fd/"+file.name),
                        .fd = fd,
                        .st = st,
                        .net = std::nullopt,
                        .exe = symlink_to_filename("/proc/"s+pid_dir.name+"/exe"),
                    });
                    if (net.count(all_files.back().inode)){
                        all_files.back().net = net[all_files.back().inode];
                    }
                }CATCH(e){
                    std::cerr << e.what() << std::endl;
                }
            }
            load_spaced_file("/proc/"s+pid_dir.name+"/maps", [&](auto& data){
            try{
                struct stat st;
                ino_t inode = (ino_t)std::stoull(data[4].data());
                if (inode){
                    all_files.push_back({
                        .pid = pid,
                        .inode = (ino_t)std::stoull(data[4].data()),
                        .path = data[5].data(),
                        .fd = std::nullopt,
                        .st = st,
                        .net = std::nullopt,
                        .exe = symlink_to_filename("/proc/"s+pid_dir.name+"/exe"),
                    });
                    if (all_files.back().inode and all_files.back().path.data()[0] == '/'){
                        THROW_ON_ERRNO(stat(data[5].data(), &st), data[5].data(), "/proc/"s+pid_dir.name+"/maps");
                        all_files.back().st = st;
                    }
                    if (net.count(all_files.back().inode)){
                        all_files.back().net = net[all_files.back().inode];
                    }
                }
            }CATCH(e){
                std::cerr << e.what() << std::endl;
            }
            });
        }CATCH(e){
            std::cerr << e.what() << std::endl;
        }
    }
    return all_files;
}

#define _define_record_fields(...)                                  \
                                                                    \
enum record_fields{__VA_ARGS__, count_of_fields};                   \
                                                                    \
auto record_field_names = [](const char* args){                     \
    std::array<std::string, record_fields::count_of_fields> res;    \
    size_t o_i = 0;                                                 \
    while (*args){                                                  \
        if (*args == ','){                                          \
            o_i += 1;                                               \
        }else{                                                      \
            if (not isspace(*args)){                                \
                res[o_i] += *args;                                  \
            }                                                       \
        }                                                           \
        ++args;                                                     \
    }                                                               \
    return res;                                                     \
}(#__VA_ARGS__);
_define_record_fields(pid, inode, path, st_mode, fd, loc_addr, loc_port, rem_addr, rem_port, type, net_type, exe)
#undef _define_record_fields

struct printable_record{
    // std::array<std::optional<std::string>, record_fields::count_of_fields> data;
    std::unordered_map<std::string, std::string> data;
};

auto make_printable_record(const record_for_having_resource& val){
    printable_record output;
    output.data["pid"] = std::to_string(val.pid);
    output.data["inode"] = std::to_string(val.inode);
    output.data["path"] = val.path;
    output.data["st_mode"] = (
        S_ISSOCK(val.st.st_mode) ? "sock"  :
        S_ISLNK(val.st.st_mode)  ? "link"  :
        S_ISFIFO(val.st.st_mode) ? "fifo"  :
        S_ISREG(val.st.st_mode)  ? "reg"   :
        S_ISBLK(val.st.st_mode)  ? "blk"   :
        S_ISCHR(val.st.st_mode)  ? "chr"   :
        S_ISDIR(val.st.st_mode)  ? "dir"   :
                                   "unknown"
    );
    if (val.fd.has_value()){
        output.data["fd"] = std::to_string(val.fd.value());
    }
    if (val.net.has_value()){
        output.data["loc_addr"] = (val.net.value().loc_addr);
        output.data["loc_port"] = std::to_string(val.net.value().loc_port);
        output.data["rem_addr"] = (val.net.value().rem_addr);
        output.data["rem_port"] = std::to_string(val.net.value().rem_port);
        output.data["net_type"] = (
            val.net.value().type == net_record::net_types::tcp4 ? "tcp4"  :
            val.net.value().type == net_record::net_types::tcp6 ? "tcp6"  :
            val.net.value().type == net_record::net_types::udp4 ? "udp4"  :
            val.net.value().type == net_record::net_types::udp6 ? "udp6"  :
                                                                  "unknown"
        );
    }
    output.data["type"] = val.fd.has_value()?"fd":"map";
    output.data["exe"] = val.exe;
    for (auto& rec: output.data){
        assert(std::find(record_field_names.begin(), record_field_names.end(), rec.first) != record_field_names.end());
    }
    return output;
}

auto record_to_str(const printable_record& val){
    std::string output;
    for (size_t i = 0; i < record_fields::count_of_fields; ++i){
        std::optional<std::string> sv;
        if (val.data.contains(record_field_names[i])){
            sv = val.data.at(record_field_names[i]);
        }
        auto field = std::make_pair(record_field_names[i], &sv);
        if (field.second->has_value()){
            if (not output.empty()){
                output += ", ";
            }
            output += "\"";
            output += field.first;
            output += "\": ";
            output += quoted(field.second->value());
        }
    }
    output = "{" + output + "}";
    return output;
}

struct expr_token{
    struct types{
        enum type{
            unk, opn_b, cls_b, a, o, n, field_name, user_value, condition
        };
    };
    size_t pos;
    types::type type;
    std::optional<std::string> str_value;
    std::optional<std::function<bool(const printable_record &)>> cond;
};

void parse_e(std::list<expr_token>& tokens, std::list<expr_token>::iterator begin, std::list<expr_token>::iterator end){
    // std::cerr << "parse_e(" << std::endl;
    // for (auto it = begin; it != end;++it){
    //     auto& token = *it;
    //     std::cerr << "    " << token.pos << " " << token.type << " " << token.str_value.value_or("(no val)") << " " << (token.cond.has_value()?"true":"false") << std::endl;
    // }
    // std::cerr << ")" << std::endl;

    if (std::next(begin) == end and begin->type == expr_token::types::condition){
        return;
    }
    if (begin->type != expr_token::types::field_name){
        throw std::runtime_error{"syntax error at char "+std::to_string(begin->pos)};
    }
    if (std::find(record_field_names.begin(), record_field_names.end(), begin->str_value.value()) == record_field_names.end()){
        throw std::runtime_error{"unknown field name " + quoted(begin->str_value.value()) + " char "+std::to_string(begin->pos)};
    }
    if (std::next(begin) != std::prev(end)){
        throw std::runtime_error{"expected value at char "+std::to_string(begin->pos)};
    }
    if (std::next(begin)->type != expr_token::types::user_value){
        throw std::runtime_error{"syntax error at char "+std::to_string(std::next(begin)->pos)};
    }
    auto key = begin->str_value.value();
    auto value = std::next(begin)->str_value.value();
    tokens.insert(begin, {
        .pos = begin->pos,
        .type = expr_token::types::condition,
        .str_value = std::nullopt,
        .cond = [=](const printable_record& prec){
            // std::cerr << key << " " << value << " " << (prec.data.contains(key) and prec.data.at(key) == value) << std::endl;
            return prec.data.contains(key) and prec.data.at(key) == value;
        },
    });
    tokens.erase(std::next(begin));
    tokens.erase(begin);
}

void parse_n(std::list<expr_token>& tokens, std::list<expr_token>::iterator begin, std::list<expr_token>::iterator end){
    // std::cerr << "parse_n(" << std::endl;
    // for (auto it = begin; it != end;++it){
    //     auto& token = *it;
    //     std::cerr << "    " << token.pos << " " << token.type << " " << token.str_value.value_or("(no val)") << " " << (token.cond.has_value()?"true":"false") << std::endl;
    // }
    // std::cerr << ")" << std::endl;

    if (begin->type == expr_token::types::n){
        parse_n(tokens, std::next(begin), end);
        assert(std::next(begin) == std::prev(end));
        auto n = std::next(begin)->cond.value();
        tokens.erase(std::next(begin));
        tokens.insert(begin, {
            .pos = begin->pos,
            .type = expr_token::types::condition,
            .str_value = std::nullopt,
            .cond = [=](const printable_record& prec){
                auto nr = n(prec);
                // std::cerr << "return " << "not " << nr << std::endl;
                return not nr;
            },
        });
        tokens.erase(begin);
    }else{
        parse_e(tokens, begin, end);
    }
}

void parse_a(std::list<expr_token>& tokens, std::list<expr_token>::iterator begin, std::list<expr_token>::iterator end){
    // std::cerr << "parse_a(" << std::endl;
    // for (auto it = begin; it != end;++it){
    //     auto& token = *it;
    //     std::cerr << "    " << token.pos << " " << token.type << " " << token.str_value.value_or("(no val)") << " " << (token.cond.has_value()?"true":"false") << std::endl;
    // }
    // std::cerr << ")" << std::endl;

    for (auto it = begin; it != end;){
        if (it->type == expr_token::types::a){
            if (it == begin){
                throw std::runtime_error{"unexpected '&' at char "+std::to_string(it->pos)};
            }
            if (std::next(it) == end){
                throw std::runtime_error{"expected expression at char "+std::to_string(it->pos+1)};
            }
            parse_n(tokens, begin, it);
            parse_a(tokens, std::next(it), end);
            auto p = std::prev(it)->cond.value();
            auto n = std::next(it)->cond.value();
            tokens.erase(std::prev(it));
            tokens.erase(std::next(it));
            tokens.insert(it, {
                .pos = it->pos,
                .type = expr_token::types::condition,
                .str_value = std::nullopt,
                .cond = [=](const printable_record& prec){
                    auto pr = p(prec);
                    auto nr = n(prec);
                    // std::cerr << "return " << pr << " and " << nr << std::endl;
                    return pr and nr;
                },
            });
            tokens.erase(it);
            return;
        }else
        {
            ++it;
        }
    }
    parse_n(tokens, begin, end);
}

void parse_o(std::list<expr_token>& tokens, std::list<expr_token>::iterator begin, std::list<expr_token>::iterator end){
    // std::cerr << "parse_o(" << std::endl;
    // for (auto it = begin; it != end;++it){
    //     auto& token = *it;
    //     std::cerr << "    " << token.pos << " " << token.type << " " << token.str_value.value_or("(no val)") << " " << (token.cond.has_value()?"true":"false") << std::endl;
    // }
    // std::cerr << ")" << std::endl;

    for (auto it = begin; it != end;){
        if (it->type == expr_token::types::o){
            if (it == begin){
                throw std::runtime_error{"unexpected '|' at char "+std::to_string(it->pos)};
            }
            if (std::next(it) == end){
                throw std::runtime_error{"expected expression at char "+std::to_string(it->pos+1)};
            }
            parse_a(tokens, begin, it);
            parse_o(tokens, std::next(it), end);
            auto p = std::prev(it)->cond.value();
            auto n = std::next(it)->cond.value();
            tokens.erase(std::prev(it));
            tokens.erase(std::next(it));
            tokens.insert(it, {
                .pos = it->pos,
                .type = expr_token::types::condition,
                .str_value = std::nullopt,
                .cond = [=](const printable_record& prec){
                    auto pr = p(prec);
                    auto nr = n(prec);
                    // std::cerr << "return " << pr << " or " << nr << std::endl;
                    return pr or nr;
                },
            });
            tokens.erase(it);
            return;
        }else
        {
            ++it;
        }
    }
    parse_a(tokens, begin, end);
}

void parse_b(std::list<expr_token>& tokens){
    // std::cerr << "parse_b(" << std::endl;
    // for (auto it = tokens.begin(); it != tokens.end();++it){
    //     auto& token = *it;
    //     std::cerr << "    " << token.pos << " " << token.type << " " << token.str_value.value_or("(no val)") << " " << (token.cond.has_value()?"true":"false") << std::endl;
    // }
    // std::cerr << ")" << std::endl;

    std::vector<std::list<expr_token>::iterator> open_b;
    for (auto it = tokens.begin(); it != tokens.end();){
        if (it->type == expr_token::types::opn_b){
            open_b.push_back(it);
            ++it;
        }else
        if (it->type == expr_token::types::cls_b){
            if (open_b.empty()){
                throw std::runtime_error{"unexpected  ')' at char " + std::to_string(std::distance(tokens.begin(), it))};
            }
            auto oit = open_b.back();
            open_b.pop_back();
            if (std::next(oit) == it){
                throw std::runtime_error{"expected expression at char " + std::to_string(std::distance(tokens.begin(), it))};
            }
            parse_o(tokens, std::next(oit), it);
            assert(std::next(oit) == std::prev(it));
            assert(std::next(oit)->type == expr_token::types::condition);
            tokens.erase(oit);
            it = tokens.erase(it);
        }else{
            ++it;
        }
    }
    if (not open_b.empty()){
        throw std::runtime_error{"expected  ')' at char " + std::to_string((tokens.size()))};
    }
    if (tokens.size() > 0){
        parse_o(tokens, tokens.begin(), tokens.end());
    }
    if (tokens.size() > 1){
        throw std::runtime_error{"unexpected expression at char "+std::to_string(std::next(tokens.begin())->pos)};
    }
    if (tokens.size() == 0){
        tokens.insert(tokens.begin(), {
            .pos = 0,
            .type = expr_token::types::condition,
            .str_value = std::nullopt,
            .cond = [](const printable_record&){
                // std::cerr << "return true" << std::endl;
                return true;
            },
        });
    }
}

std::function<bool(const printable_record &)> parse_expr(std::string expr){
    std::list<expr_token> tokens;
    bool next_token_is_user_data = false;
    for (size_t i = 0; i < expr.size() ; ++i){
        if (std::isspace(expr[i])){
            continue;
        }else
        if (next_token_is_user_data){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::user_value,
                .str_value = expr.data() + i,
                .cond = std::nullopt,
            });
            next_token_is_user_data = false;
            i += tokens.back().str_value.value().size();
        }else
        if (expr[i] == '('){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::opn_b,
                .str_value = std::nullopt,
                .cond = std::nullopt,
            });
        }else
        if (expr[i] == ')'){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::cls_b,
                .str_value = std::nullopt,
                .cond = std::nullopt,
            });
        }else
        if (expr[i] == '&'){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::a,
                .str_value = std::nullopt,
                .cond = std::nullopt,
            });
        }else
        if (expr[i] == '|'){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::o,
                .str_value = std::nullopt,
                .cond = std::nullopt,
            });
        }else
        if (expr[i] == '!'){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::n,
                .str_value = std::nullopt,
                .cond = std::nullopt,
            });
        }else
        if (std::isalnum(expr[i])){
            tokens.push_back({
                .pos = i,
                .type = expr_token::types::field_name,
                .str_value = expr.data() + i,
                .cond = std::nullopt,
            });
            next_token_is_user_data = true;
            i += tokens.back().str_value.value().size();
        }else{
            throw std::runtime_error{"unexpected symbol chr("s+std::to_string((int)(expr[i]))+") at pos "s+std::to_string(i)};
        }
    }
    parse_b(tokens);
    assert(tokens.size() == 1);
    assert(tokens.begin()->cond.has_value());
    return tokens.begin()->cond.value();
}

int main(int argc, char**argv){
    std::string expr;
    std::vector<std::string> args(argv+1, argv+argc);
    for (auto& arg: args){
        if (&arg != &args[0]){
            expr += '\0';
        }
        expr += arg;
        if (arg == "-h" or arg == "--help" or arg == "-help"){
            std::cout << "Usage:" << std::endl;
            std::cout << "    " << std::quoted(argv[0], '\'') << " [expr]" << std::endl;
            std::cout << "Where:" << std::endl;
            std::cout << "    expr:" << std::endl;
            std::cout << "        - defines which items to print." << std::endl;
            std::cout << "        - follows format below." << std::endl;
            std::cout << "Format for expr:" << std::endl;
            std::cout << "    trivial filter: 'name' 'value' " << std::endl;
            std::cout << "        note: argument breaks are used as bounds for value" << std::endl;
            std::cout << "    logical not:" << std::endl;
            std::cout << "        !expr" << std::endl;
            std::cout << "    logical and" << std::endl;
            std::cout << "        expr&expr" << std::endl;
            std::cout << "    logical or" << std::endl;
            std::cout << "        expr|expr" << std::endl;
            std::cout << "    parentheses" << std::endl;
            std::cout << "        (expr)" << std::endl;
            std::cout << "Examples for expr:" << std::endl;
            std::cout << "    Print all mapped files:" << std::endl;
            std::cout << "        " << std::quoted(argv[0], '\'') << " 'type' 'map'" << std::endl;
            std::cout << "    Print all connections to port 22:" << std::endl;
            std::cout << "        " << std::quoted(argv[0], '\'') << " 'rem_port' '22'" << std::endl;
            std::cout << "    Print all network connections:" << std::endl;
            std::cout << "        " << std::quoted(argv[0], '\'') << " 'net_type' 'tcp4' '|net_type' 'tcp6' '|net_type' 'udp4' '|net_type' 'udp6'" << std::endl;
            std::cout << "    Print all outside connections:" << std::endl;
            std::cout << "        " << std::quoted(argv[0], '\'') << " '(net_type' 'tcp4' '|net_type' 'udp4' '|net_type' 'tcp6' '|net_type' 'udp6' ')&!rem_addr' '127.0.0.1' '&!rem_addr' '0000:0000:0000:0000:0000:0000:0100:0000' '&!rem_addr' '0.0.0.0'" << std::endl;
            std::cout << "    Print all listening sockets:" << std::endl;
            std::cout << "        " << std::quoted(argv[0], '\'') << " 'rem_addr' '0.0.0.0' " << std::endl;
            return 0;
        }
    }
    std::function<bool (const printable_record &)> condition = parse_expr(expr);
    auto files = get_all_files();
    for (auto& file: files){
        auto pfile = make_printable_record(file);
        // std::cerr << "?" << record_to_str(pfile) << std::endl;
        auto res = condition(pfile);
        // std::cerr << "=" << res << std::endl;
        if (res){
            std::cout << record_to_str(pfile) << std::endl;
        }
    }
}
