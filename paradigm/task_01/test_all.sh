#!/bin/bash
cd "$(
    dirname "$(
        realpath "${0}"
    )"
)"

export CARGO_TARGET_DIR="../target"
export RUST_BACKTRACE=full

find . -name 'Cargo.toml' -exec bash -c 'cd "$(dirname {})" && cargo test || touch tests_failed' \;

find . -name 'Cargo.toml' -exec bash -c 'cd "$(dirname {})" && cargo clean' \;

if [ -f tests_failed ]
then
    rm tests_failed
    exit 1
fi
