import sys
import os
import re

if __name__ == "__main__":
    # python Cmakev2 MakeFiles/make.txt debug
    dir = os.getcwd()
    args = sys.argv
    if len(args) != 3:
        print("""Not enough arguments. Try:\n
              python Cmakev2 MakeFiles/make.txt debug""")
    target = args[1]
    mode = args[2]
    src = ""

    f = open(target, "r")
    for line in f:
        src += line.replace("\n", "")

    mode = r"(?<=(" + re.escape(mode) + r"\s{))([^}])*"
    execute_code = re.search(mode, src).group(0)
    execute_code = re.sub("\s\s+", " ", execute_code)

    os.chdir(dir)
    os.system(execute_code)
