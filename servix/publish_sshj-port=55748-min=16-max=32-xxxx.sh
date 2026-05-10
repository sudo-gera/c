this_file="${BASH_SOURCE[0]}"
this_file_abs="$(
    realpath -- "$this_file"
)"
this_dir="$(
    dirname -- "$this_file_abs"
)"
source "${this_dir}/publish_sshj.sh"
