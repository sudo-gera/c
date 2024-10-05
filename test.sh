# #!/bin/bash
# function g() {
#     local args;
#     local file;
#     args=("" "$@");
#     if ! \
#         for i in $(seq 1 $#)
#         do
#             file="${args[i]}"
#             echo "$file" | grep / >/dev/null && exe="$file.out" || exe="./$file.out"
#             test -f "$file" && break
#         done
#     then
#         echo "Error: file not given or does not exist."
#         return 1
#     fi
#     rm "$exe"
#     clang++ -g -fsanitize=address,undefined -std=c++20 -Ofast -o "$exe" "${args[@]:1:i}" && \
#         [ ! -f "$exe" ] || [ ! -x "$exe" ] || "$exe" "${args[@]:i+1:$#-i}"
# }
# g -std=c++20 -E -o test_ test.cpp '1  2'
alias 'clang++'=' clang++ -std=c++20 -g -fsanitize=address,undefined -Ofast'
alias     'g++'='     g++ -std=c++20 -g -fsanitize=address,undefined -Ofast'
# clang__ test.cpp
