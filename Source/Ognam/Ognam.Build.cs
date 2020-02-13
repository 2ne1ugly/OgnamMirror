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
           //"InfraworldRuntime",
        });

		PrivateDependencyModuleNames.AddRange(new string[] { "Projects" });
        MinFilesUsingPrecompiledHeaderOverride = 1;

        PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
        PublicDefinitions.Add("GPR_FORBID_UNREACHABLE_CODE");
        PublicDefinitions.Add("GRPC_ALLOW_EXCEPTIONS=0");

        ModuleDepPaths deps = GatherDeps(Target.Platform);
        PublicIncludePaths.AddRange(deps.HeaderPaths);
        PublicAdditionalLibraries.AddRange(deps.LibraryPaths);
        
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }

    [Conditional("DEBUG")]
    [Conditional("TRACE")]
    private void clog(params object[] objects)
    {
        Console.WriteLine(string.Join(", ", objects));
    }

    public class ModuleDepPaths
    {
        public readonly string[] HeaderPaths;
        public readonly string[] LibraryPaths;

        public ModuleDepPaths(string[] headerPaths, string[] libraryPaths)
        {
            HeaderPaths = headerPaths;
            LibraryPaths = libraryPaths;
        }

        public override string ToString()
        {
            return "Headers:\n" + string.Join("\n", HeaderPaths) + "\nLibs:\n" + string.Join("\n", LibraryPaths);
        }
    }

    public ModuleDepPaths GatherDeps(UnrealTargetPlatform Platform)
    {
        string RootPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Plugins/InfraworldRuntime"));

        string INCLUDE_ROOT = Path.Combine(RootPath, "GrpcIncludes");
        string LIB_ROOT = Path.Combine(RootPath, "GrpcLibraries");


        List<string> headers = new List<string>();
        List<string> libs = new List<string>();

        string PlatformLibRoot = Path.Combine(LIB_ROOT, Platform.ToString());


        if (Platform == UnrealTargetPlatform.Win64)
        {
            PlatformLibRoot = Path.Combine(LIB_ROOT, Platform.ToString());
            libs.AddRange(new string[] {
                Path.Combine(PlatformLibRoot, "grpc++.lib"),
                Path.Combine(PlatformLibRoot, "grpc.lib"),
                Path.Combine(PlatformLibRoot, "gpr.lib"),
                Path.Combine(PlatformLibRoot, "upb.lib"),
                Path.Combine(PlatformLibRoot, "cares.lib"),
                Path.Combine(PlatformLibRoot, "address_sorting.lib"),
                Path.Combine(PlatformLibRoot, "absl_strings.lib"),
                Path.Combine(PlatformLibRoot, "absl_throw_delegate.lib"),
             });
        }
        else
        {
            PlatformLibRoot = Path.Combine(LIB_ROOT, Platform.ToString());
            libs.AddRange(new string[] {
                Path.Combine(PlatformLibRoot, "libgrpc++.a"),
                Path.Combine(PlatformLibRoot, "libgrpc.a"),
                Path.Combine(PlatformLibRoot, "libgpr.a"),
                Path.Combine(PlatformLibRoot, "libupb.a"),
                Path.Combine(PlatformLibRoot, "libcares.a"),
                Path.Combine(PlatformLibRoot, "libaddress_sorting.a"),
                Path.Combine(PlatformLibRoot, "libabsl_strings.a"),
                Path.Combine(PlatformLibRoot, "libabsl_throw_delegate.a"),
             });
        }

        clog("PlatformLibRoot: " + PlatformLibRoot);
        foreach (string path in libs)
        {
            clog(path);
        }
        headers.Add(Path.Combine(RootPath, "Source", "InfraworldRuntime", "Public"));
        headers.Add(Path.Combine(INCLUDE_ROOT, "include"));
        headers.Add(Path.Combine(INCLUDE_ROOT, "third_party", "protobuf", "src"));

        return new ModuleDepPaths(headers.ToArray(), libs.ToArray());
    }
}
