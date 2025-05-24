#!/usr/bin/env bash

set -e

cd "$(
    dirname "$(
        realpath "${0}"
    )"
)"

CARGO_TARGET_DIR="$(pwd)/target"
export CARGO_TARGET_DIR
export RUST_BACKTRACE=full
export RUSTFLAGS='-D warnings'

cargo_tomls_escaped_lf_joined="$(find . -name Cargo.toml -exec bash -c 'echo "${0@Q}"' {} \;)"

test_failed=0

if ! (
    echo "$cargo_tomls_escaped_lf_joined" | \
    while read -r cargo_toml_escaped
    do
        cargo_toml="$(bash -c "printf '%s\n' $cargo_toml_escaped")"
        dir_containing_cargo_toml="$(dirname "$cargo_toml")"
        if ! (
            echo
            echo
            echo
            echo
            printf '%s\n' "${dir_containing_cargo_toml@Q}"
            echo
            echo
            cd "$dir_containing_cargo_toml"
            cargo clippy -- -D warnings || exit 1
            cargo build || exit 1
            cargo test || exit 1
        )
        then
            exit 1
        fi
    done
) then
    test_failed=1
fi

echo "$cargo_tomls_escaped_lf_joined" | \
while read -r cargo_toml_escaped
do
    cargo_toml="$(bash -c "printf '%s\n' $cargo_toml_escaped")"
    dir_containing_cargo_toml="$(dirname "$cargo_toml")"
    (
        cd "$dir_containing_cargo_toml"
        cargo clean || :
    )
done

echo
echo
echo
echo

if [ "$test_failed" -eq 1 ]
then
    echo 'tests failed!'
else
    echo 'everything is ok!'
fi
