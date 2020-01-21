// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Ognam : ModuleRules
{
	public Ognam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "OnlineSubsystem", "OnlineSubsystemUtils", "Sockets" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Projects" });

        MinFilesUsingPrecompiledHeaderOverride = 1;

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
