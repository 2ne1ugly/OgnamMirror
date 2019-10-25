// Copyright 2019 Ognam Studios. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class OgnamTarget : TargetRules
{
	public OgnamTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        bUsesSteam = true;
        ExtraModuleNames.AddRange( new string[] { "Ognam" } );
	}
}
