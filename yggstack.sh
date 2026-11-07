#!/bin/sh
# setup-yggstack.sh — idempotent Yggstack config bootstrap
set -eu

YGGSTACK="$HOME/yggstack"
DIR="$HOME/.yggstack"
KEY="$DIR/private.key"
CONF="$DIR/config.conf"
PUB="$DIR/public.key"
ADDR="$DIR/address.txt"

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

# 4. Always enforce permissions, even on pre-existing files
chmod 700 "$DIR"
chmod 600 "$KEY" "$CONF"

# 5. Always re-derive public key + address from the current config
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
