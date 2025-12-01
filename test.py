import os

def main():
    root_dir = "reports"
    if not os.path.isdir(root_dir):
        raise FileNotFoundError(f"{root_dir} does not exist")

    for dirpath, dirnames, filenames in os.walk(root_dir):
        for filename in filenames:
            file_path = os.path.join(dirpath, filename)
            with open(file_path) as file_file:
                for line in file_file:
                    if line=='virus\n':
                         os.remove(file_path)
                         break

if __name__ == "__main__":
    main()
