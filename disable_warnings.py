
from datetime import *
from pathlib import Path
import os
import sys

include_disable_warnings = '#include "GrpcIncludesBegin.h"'
include_enable_warnings = '#include "GrpcIncludesEnd.h"'

def WrapHeader(Source):
    print("parsing " + str(Source))
    SourceDisc = open(Source, 'r')
    if (SourceDisc is None):
        print("Failed to read ")
        return

    lines = SourceDisc.readlines()
    for line in lines:
        if (line.find(include_disable_warnings) >= 0 or line.find(include_enable_warnings) >= 0):
            return

    SourceDisc.close()
    SourceDisc = open(Source, 'w')
    if (SourceDisc is None):
        print("Failed to write ") 
        return

    SourceDisc.write("\n{0}\n\n".format(include_disable_warnings))
    for line in lines:
        SourceDisc.write(line)
    SourceDisc.write("\n{0}\n\n".format(include_enable_warnings))
    SourceDisc.close()

    print("Success to regenerate the code for UE4")

def Generate(Dir):
    result = list(Path(Dir).rglob("**/*.pb.cc"))
    for ccfile in result:
        WrapHeader(ccfile)

Generate("Plugins\InfraworldRuntime\Source\InfraworldRuntime\layton")
    