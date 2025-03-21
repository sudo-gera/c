# #!/bin/bash

# tmux_socket_name=_${RANDOM}_

# function wrap_script(){
#     args="$1"
#     command="$2"
#     if script --version 2>/dev/null 1>/dev/null
#     then
#         script $args -c 
# }

# function create_window(){
#     name="$1"
#     script_args="$2"
#     command="$3"
#     tmux -L $tmux_socket_name new -d
#     if script --version 2>/dev/null 1>/dev/null
#     then
#         tmux -L $tmux_socket_name send -l "script ${command@Q}"
#     else
#         tmux -L $tmux_socket_name send -l "${command@Q}"
#     fi
# }

# create_window master '


