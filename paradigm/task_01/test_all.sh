#!/bin/bash
cd "$(
    dirname "$(
        realpath "${0}"
    )"
)"

export CARGO_TARGET_DIR="../target"
export RUST_BACKTRACE=full
export RUSTFLAGS='-D warnings'

find . -name 'Cargo.toml' -exec bash -c 'echo ; echo {} ; cd "$(dirname {})" && cargo build || touch ../tests_failed' \;
find . -name 'Cargo.toml' -exec bash -c 'echo ; echo {} ; cd "$(dirname {})" && cargo clippy -- -D warnings || touch ../tests_failed' \;

find . -name 'Cargo.toml' -exec bash -c 'cd "$(dirname {})" && cargo clean' \;

if [ -f tests_failed ]
then
    rm tests_failed
    echo 'tests failed!'
    exit 1
else
    echo
    echo
    echo
    echo
    echo 'everything is ok!'
fi
