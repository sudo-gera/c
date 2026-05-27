import argparse
import pathlib
from typing import *

def process_one_file(to_replace: str, path: pathlib.Path) -> None:
    lines = []
    with path.open('r') as file:
        for i,l in enumerate(file):
            l = l.replace(to_replace, f'{path}:{i+1}')
            lines.append(l)
    
    with path.open('w') as file:
        file.write(''.join(lines))
    
def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('--to-replace', required=True)
    parser.add_argument('--path', required=True, type=pathlib.Path, nargs='*')
    args = parser.parse_args()

    to_replace = cast(str, args.to_replace)
    paths = cast(list[pathlib.Path], args.path)

    for path in paths:
        process_one_file(to_replace, path)

if __name__ == '__main__':
    main()