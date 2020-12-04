"""
* Author  : Abolfazl Ziaeemehr
* Date    : December 2020
* Version : 0.1 
* 
* This script make a single header file for neuro_toolbox library

"""

import os
from glob import glob
from os.path import join


def get_headerfile_names():

    names = []
    with open(join(data_path, "neuro_toolbox.hpp"), "r") as f:
        lines = f.readlines()
        for i in range(len(lines)):
            if "#include" in lines[i]:
                tmp = lines[i].split(" ")[1]
                names.append(tmp.rstrip()[1:-1])

    return names


def copy_to_file(input_name, output_file, skip_header=2, skip_footer=1, skip_include=True):

    output_file.write("// from {:s}\n// {:s}".format(input_name, "-" * 76))
    with open(join(data_path, input_name)) as f:
        lines = f.readlines()
        n_lines = len(lines)
        for i in range(skip_header, n_lines-skip_footer):
            if skip_include and ("#include" in lines[i]):
                continue
            output_file.write(lines[i])


data_path = "../src/include"


if __name__ == "__main__":

    headers = get_headerfile_names()
    # print(headers)

    # open single header file
    output_file_name = "neuro_toolbox.hpp"
    output_file = open(output_file_name, "w")
    output_file.write("#ifndef NEURO_TOOLBOX\n")
    output_file.write("#define NEURO_TOOLBOX\n")
    output_file.write(" \n")

    for name in headers:
        if name == "config.hpp":
            copy_to_file(name,
                         output_file,
                         skip_header=2,
                         skip_footer=1,
                         skip_include=False)
        else:
            copy_to_file(name,
                         output_file,
                         skip_header=2,
                         skip_footer=1)

    output_file.write("\n#endif // !NEURO_TOOLBOX\n")
    output_file.close()

    # print(join(data_path, "*"))

    # header_files =
# if (line[:7] == "#ifndef") or (line[:7] == "#define"):
# header_files = glob(join(data_path, "*"))
#     header_files = [file.split("/")[3] for file in header_files]
#     header_files.remove("config.hpp")
#     header_files.remove("neuro_toolbox.hpp")
#     # print(header_files)
