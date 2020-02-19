
from datetime import *
from pathlib import Path
import os
import sys

include_disable_warnings = '#include "GrpcIncludesBegin.h"'
include_enable_warnings = '#include "GrpcIncludesEnd.h"'

def WrapCC(Source):
    print("parsing " + str(Source))
    SourceDisc = open(Source, 'r', errors="ignore")
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

def WrapHeader(Source):
    print("parsing " + str(Source))
    SourceDisc = open(Source, 'r', errors="ignore")
    if (SourceDisc is None):
        print("Failed to read ")
        return
    lines = SourceDisc.readlines()

    SourceDisc.close()
    SourceDisc = open(Source, 'w')
    if (SourceDisc is None):
        print("Failed to write ") 
        return

    for line in lines:
        if len(line) > 5:
            if line[0:5] == "class" and (len(line) < 27 or line[6:27] != "INFRAWORLDRUNTIME_API") and line[-2] == ":":
                line = line[0:5] + " INFRAWORLDRUNTIME_API" + line[5:]
        SourceDisc.write(line)
    

    SourceDisc.close()
    print("Success to regenerate the code for UE4")

def Generate(Dir):
    result = list(Path(Dir).rglob("**/*.cc"))
    for ccfile in result:
        WrapCC(ccfile)

    result = list(Path(Dir).rglob("**/*.h"))
    for hfile in result:
        WrapHeader(hfile)


Generate("Plugins\InfraworldRuntime\Source\InfraworldRuntime\Layton")
