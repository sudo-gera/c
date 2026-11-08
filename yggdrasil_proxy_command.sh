#!/usr/bin/env bash

set -xeuo pipefail

MY_TEMP_FILE=$(mktemp)
export MY_TEMP_FILE
trap 'rm -f ${MY_TEMP_FILE@Q}' EXIT TERM HUP

tee > "$MY_TEMP_FILE"

export listen_port="$1"
export listen_host="$2"

ncat -knvlp "$listen_port" "$listen_host" --sh-exec '
    bash -xeuc "$(
        cat "$MY_TEMP_FILE" | sed -nE "s?^\s*ProxyCommand\s*(.*)?\1?gp" | shuf -n 1
    )" | (
        bash -xc '"'"'
            while IFS="" read -r t && [ "$t" != $'"'"'"'"'"'"'"'"'\r'"'"'"'"'"'"'"'"' ] ;
            do : ; done
        '"'"' ; tee
    )
'
