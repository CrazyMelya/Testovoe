// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Testovoe : ModuleRules
{
	public Testovoe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Testovoe",
			"Testovoe/Variant_Platforming",
			"Testovoe/Variant_Combat",
			"Testovoe/Variant_Combat/AI",
			"Testovoe/Variant_SideScrolling",
			"Testovoe/Variant_SideScrolling/Gameplay",
			"Testovoe/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
