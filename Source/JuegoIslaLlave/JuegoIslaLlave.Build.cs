// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JuegoIslaLlave : ModuleRules
{
	public JuegoIslaLlave(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
