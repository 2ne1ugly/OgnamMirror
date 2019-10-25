// Copyright 2019 Ognam Studios. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class OgnamEditorTarget : TargetRules
{
	public OgnamEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        //BuildEnvironment = TargetBuildEnvironment.Unique;

        ExtraModuleNames.AddRange( new string[] { "Ognam" } );
    }
}
