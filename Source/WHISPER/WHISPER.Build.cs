// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WHISPER : ModuleRules
{
	public WHISPER(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG",
			"Slate",
			"CommonUI",
			"CommonInput",
			"CommonGame"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"WHISPER",
			"WHISPER/Variant_Platforming",
			"WHISPER/Variant_Platforming/Animation",
			"WHISPER/Variant_Combat",
			"WHISPER/Variant_Combat/AI",
			"WHISPER/Variant_Combat/Animation",
			"WHISPER/Variant_Combat/Gameplay",
			"WHISPER/Variant_Combat/Interfaces",
			"WHISPER/Variant_Combat/UI",
			"WHISPER/Variant_SideScrolling",
			"WHISPER/Variant_SideScrolling/AI",
			"WHISPER/Variant_SideScrolling/Gameplay",
			"WHISPER/Variant_SideScrolling/Interfaces",
			"WHISPER/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
