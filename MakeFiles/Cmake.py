import sys
import os


if __name__ == "__main__":
    dir = os.getcwd()
    args = sys.argv
    if len(args) >= 2:
        target = args[1]
    else:
        target = "MakeFiles/make.txt"
    src = ""

    f = open(target, "r")
    for line in f:
        src += line.replace("\n", " ")

    os.chdir(dir)
    os.system(src)
