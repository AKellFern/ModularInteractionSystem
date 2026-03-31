// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InteractionFramework : ModuleRules
{
	public InteractionFramework(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"InteractionFramework",
			"InteractionFramework/Variant_Platforming",
			"InteractionFramework/Variant_Platforming/Animation",
			"InteractionFramework/Variant_Combat",
			"InteractionFramework/Variant_Combat/AI",
			"InteractionFramework/Variant_Combat/Animation",
			"InteractionFramework/Variant_Combat/Gameplay",
			"InteractionFramework/Variant_Combat/Interfaces",
			"InteractionFramework/Variant_Combat/UI",
			"InteractionFramework/Variant_SideScrolling",
			"InteractionFramework/Variant_SideScrolling/AI",
			"InteractionFramework/Variant_SideScrolling/Gameplay",
			"InteractionFramework/Variant_SideScrolling/Interfaces",
			"InteractionFramework/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
