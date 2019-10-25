// Copyright 2019 Ognam Studios. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class OgnamServerTarget : TargetRules  
{
    public OgnamServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        ExtraModuleNames.Add("Ognam");
    }
}