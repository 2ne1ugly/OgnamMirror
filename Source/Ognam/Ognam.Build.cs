// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net.NetworkInformation;
using System.Text;
using System.Text.RegularExpressions;
using UnrealBuildTool;

public class Ognam : ModuleRules
{
	public Ognam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
           "Core",
           "CoreUObject",
           "Engine",
           "InputCore",
           "UMG",
           "Slate",
           "SlateCore",
           "InfraworldRuntime",
        });

        AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
        AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");

        PrivateDependencyModuleNames.AddRange(new string[] { "Projects" });
        MinFilesUsingPrecompiledHeaderOverride = 1;
    }
}
