#!/bin/bash
# setup-yggstack.sh — idempotent Yggstack config bootstrap
set -euo pipefail

YGGSTACK="$HOME/yggstack"
DIR="$HOME/.yggstack"
KEY="$DIR/private.key"
CONF="$DIR/config.conf"
PUB="$DIR/public.key"
ADDR="$DIR/address.txt"
DAEMON="$DIR/daemon.sh"

# 0. Preflight: verify required commands are available
missing=0

if [ ! -x "$YGGSTACK" ]; then
    echo "Error: yggstack binary not found or not executable: $YGGSTACK" >&2
    echo "       Download it to $YGGSTACK and chmod +x it." >&2
    missing=1
fi

if ! command -v jq >/dev/null 2>&1; then
    echo "Error: jq is not installed or not in PATH." >&2
    echo "       Install it via your package manager (e.g. apt install jq, brew install jq)." >&2
    missing=1
fi

if [ "$missing" -ne 0 ]; then
    echo "Aborting: missing required dependencies." >&2
    exit 1
fi

# 1. Create ~/.yggstack with .ssh-like permissions (dir => 700)
if [ ! -d "$DIR" ]; then
    echo "Creating $DIR (0700)..."
    ( umask 077; mkdir -p "$DIR" )
fi

# 2. Generate PEM private key if missing (file => 600)
if [ ! -f "$KEY" ]; then
    echo "Generating $KEY (PEM)..."
    ( umask 077
      "$YGGSTACK" -genconf | "$YGGSTACK" -useconf -exportkey > "$KEY"
    )
fi

# 3. Generate normalised config importing the key if missing (file => 600)
if [ ! -f "$CONF" ]; then
    echo "Generating $CONF (normalised)..."
    ( umask 077
      "$YGGSTACK" -genconf -json \
          | jq --arg kp "$KEY" '.PrivateKeyPath = $kp | del(.PrivateKey)' \
          | "$YGGSTACK" -useconf -normaliseconf > "$CONF"
    )
fi

# 4. Generate daemon.sh if missing (user-editable — never overwritten)
if [ ! -f "$DAEMON" ]; then
    echo "Generating $DAEMON..."
    cat > "$DAEMON" <<'EOF'
#!/bin/sh
# daemon.sh — start yggstack with the config in this directory.
#
# ADD PORT FORWARDING FLAGS HERE (before or instead of the trailing "$@").
#
#   Expose local ports to the Yggdrasil network:
#     -remote-tcp  22                             # same port on both ends
#     -remote-tcp  2022:22                        # local 22 -> remote 2022
#     -remote-tcp  22:192.168.1.1:2022            # explicit target host
#     -remote-udp  5353                           # UDP equivalent
#
#   Forward local ports to a remote Yggdrasil node:
#     -local-tcp   22:[200:dead:beef::1]:22
#     -local-tcp   127.0.0.1:22:[200:dead:beef::1]:22
#     -local-udp   22:[200:dead:beef::1]:2022
#
#   Optional SOCKS proxy (TCP):
#     -socks       :1080                          # or /tmp/yggstack.sock
#
# Example (uncomment / adapt):
#     -remote-tcp  22 \
#     -remote-tcp  443:192.168.1.10:8443 \
#     -socks       :1080 \
#
# DO NOT run multiple yggstack processes with the same config file.
#   They will all share the same IPv6 address
#   and conflict with each other.

exec "$HOME/yggstack" \
    -useconffile "$HOME/.yggstack/config.conf" \
    "$@"
EOF
fi

# 5. Always enforce permissions, even on pre-existing files
chmod 700 "$DIR"
chmod 600 "$KEY" "$CONF"
chmod 755 "$DAEMON"

# 6. Always re-derive public key + address from the current config
echo "Extracting public key and address from $CONF..."
( umask 077
  "$YGGSTACK" -useconf -publickey < "$CONF" > "$PUB"
  "$YGGSTACK" -useconf -address   < "$CONF" > "$ADDR"
)
chmod 644 "$PUB" "$ADDR"

echo "Done."
echo "  private key: $KEY"
echo "  public key:  $PUB"
echo "  config:      $CONF"
echo "  address:     $ADDR"
echo "  daemon:      $DAEMON"