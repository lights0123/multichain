#!/usr/bin/env python

import sys

output = ""
header_found = False;
data_found = False;
with open(sys.argv[1], "r") as f:
    for line in f:
        if("configure_args" in line and not header_found):
            header_found = True

        if("shared" in line and header_found and not data_found):
            data_found = True
            output += "no-shared\n"
            continue;

        output += line

with open(sys.argv[1], "w") as f:
    f.write(output)
