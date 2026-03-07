#!/usr/bin/env bash

set -e -x -u -o pipefail

function modify_table(){
    table_mod="$1"

    iptables -t nat "$table_mod" REDSOCKS
}

function modify_rules(){
    rule_mod="$1"

    iptables -t nat "$rule_mod" REDSOCKS -d 0.0.0.0/8 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 10.0.0.0/8 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 100.64.0.0/10 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 127.0.0.0/8 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 169.254.0.0/16 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 172.16.0.0/12 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 192.168.0.0/16 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 198.18.0.0/15 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 224.0.0.0/4 -j RETURN
    iptables -t nat "$rule_mod" REDSOCKS -d 240.0.0.0/4 -j RETURN

    iptables -t nat "$rule_mod" REDSOCKS -p tcp -j REDIRECT --to-ports 12345

    iptables -t nat "$rule_mod" PREROUTING -j REDSOCKS
}

function enable(){
    modify_table '-N' || :
    modify_rules '-A'
}

function disable(){(
    set +e
    modify_rules '-D'
    modify_table '-X'
    true
)}

trap 'disable' EXIT

enable

tail -f /dev/null
