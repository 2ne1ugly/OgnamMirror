using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class OgnamServerTarget : TargetRules   // Change this line as shown previously
{
    public OgnamServerTarget(TargetInfo Target) : base(Target)  // Change this line as shown previously
    {
        Type = TargetType.Server;

        ExtraModuleNames.Add("Ognam");    // Change this line as shown previously
    }
}