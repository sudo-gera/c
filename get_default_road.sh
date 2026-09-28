#!/usr/bin/env bash

# 1. Get the default gateway IP and the interface name
# Example output of 'ip route show default': default via 192.168.1.1 dev eth0
GATEWAY_INFO=$(ip route show default | head -n 1)
GATEWAY_IP=$(echo "$GATEWAY_INFO" | awk '{print $3}')
INTERFACE=$(echo "$GATEWAY_INFO" | awk '{print $5}')

# 2. Get the local IP address for that specific interface
INTERFACE_IP=$(ip -4 addr show "$INTERFACE" | grep -oP '(?<=inet\s)\d+(\.\d+){3}')

echo "$GATEWAY_IP"
echo "$INTERFACE_IP"
