#!/bin/bash
iptables-restore << EOF
*filter
:INPUT ACCEPT [7:488]
:FORWARD ACCEPT [0:0]
:OUTPUT ACCEPT [4:424]
COMMIT
EOF
