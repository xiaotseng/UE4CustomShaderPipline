// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class test : ModuleRules
{
	public test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
        PublicIncludePaths.AddRange(
            new string[] {
                "Myshader/Public",
                "Myshader/Classes",
                "..\\intermediate\\Build\\Win64\\UE4Editor\\Inc\\test"
				// ... add public include paths required here ...
			}
            );

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
