// Copyright (c), Firelight Technologies Pty, Ltd. 2012-2016.

namespace UnrealBuildTool.Rules
{
	public class FMODStudio : ModuleRules
	{
		public FMODStudio(TargetInfo Target)
		{
			bFasterWithoutUnity = true;

			PublicIncludePaths.AddRange(
				new string[] {
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"FMODStudio/Private",
					"FMODStudio/Public/FMOD",
					"FMODStudioOculus/Public",
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"Projects"
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
				}
				);

			if (UEBuildConfiguration.bBuildEditor == true)
			{
				PrivateDependencyModuleNames.Add("AssetRegistry");
				PrivateDependencyModuleNames.Add("UnrealEd");
			}

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
				}
				);

			string configName = "";

			if (Target.Configuration != UnrealTargetConfiguration.Shipping)
			{
				configName = "L";
				Definitions.Add("FMODSTUDIO_LINK_LOGGING=1");
			}
			else
			{
				configName = "";
				Definitions.Add("FMODSTUDIO_LINK_RELEASE=1");
			}

			string platformName = Target.Platform.ToString();

			string platformMidName = "";
			string linkExtension = "";
			string dllExtension = "";
			string libPrefix = "";

			// ModuleDirectory points to FMODStudio\source\FMODStudio, need to get back to binaries directory for our libs
			string BasePath = System.IO.Path.Combine(ModuleDirectory, "../../Binaries", platformName);

			string copyThirdPartyPath = "";
			bool bAddRuntimeDependencies = true;
			bool bAddDelayLoad = false;
			bool bShortLinkNames = false;
			bool bLinkFromBinaries = true;
			switch (Target.Platform)
			{
				case UnrealTargetPlatform.Win32:
					linkExtension = "_vc.lib";
					dllExtension = ".dll";
					bAddDelayLoad = true;
					break;
				case UnrealTargetPlatform.Win64:
					platformMidName = "64";
					linkExtension = "_vc.lib";
					dllExtension = ".dll";
					bAddDelayLoad = true;
					break;
				case UnrealTargetPlatform.Mac:
					linkExtension = dllExtension = ".dylib";
					libPrefix = "lib";
					bLinkFromBinaries = false;

					break;
				case UnrealTargetPlatform.XboxOne:
					linkExtension = "_vc.lib";
					dllExtension = ".dll";
					copyThirdPartyPath = "../XBoxOne"; // XBoxOne still doesn't seem to support plugins with .dlls
					bAddDelayLoad = true;
					break;
				case UnrealTargetPlatform.PS4:
					linkExtension = "_stub.a";
					dllExtension = ".prx";
					libPrefix = "lib";
					bAddDelayLoad = true;
					break;
				case UnrealTargetPlatform.Android:
					// Don't use an explicit path with the .so, let the architecture dirs be filtered by UBT
					PublicLibraryPaths.Add(System.IO.Path.Combine(BasePath, "armeabi-v7a"));
					PublicLibraryPaths.Add(System.IO.Path.Combine(BasePath, "arm64-v8a"));
					PublicLibraryPaths.Add(System.IO.Path.Combine(BasePath, "x86"));
					bAddRuntimeDependencies = false; // Don't use this system
					bShortLinkNames = true; // strip off lib and .so
					linkExtension = dllExtension = ".so";
					libPrefix = "lib";
					break;
				case UnrealTargetPlatform.IOS:
					linkExtension = "_iphoneos.a";
					libPrefix = "lib";
					bAddRuntimeDependencies = false;
					break;
				case UnrealTargetPlatform.Linux:
					BasePath = System.IO.Path.Combine(BasePath, "x86_64");
					linkExtension = ".so";
					dllExtension = ".so";
					libPrefix = "lib";
					break;
				default:
					//extName = ".a";
					throw new System.Exception(System.String.Format("Unsupported platform {0}", Target.Platform.ToString()));
					//break;
			}
			
			//System.Console.WriteLine("FMOD Current path: " + System.IO.Path.GetFullPath("."));
			//System.Console.WriteLine("FMOD Base path: " + BasePath);

			PublicLibraryPaths.Add(BasePath);

			string fmodLibName = System.String.Format("{0}fmod{1}{2}{3}", libPrefix, configName, platformMidName, linkExtension);
			string fmodStudioLibName = System.String.Format("{0}fmodstudio{1}{2}{3}", libPrefix, configName, platformMidName, linkExtension);

			string fmodDllName = System.String.Format("{0}fmod{1}{2}{3}", libPrefix, configName, platformMidName, dllExtension);
			string fmodStudioDllName = System.String.Format("{0}fmodstudio{1}{2}{3}", libPrefix, configName, platformMidName, dllExtension);

			string fmodLibPath = System.IO.Path.Combine(BasePath, fmodLibName);
			string fmodStudioLibPath = System.IO.Path.Combine(BasePath, fmodStudioLibName);

			string fmodDllPath = System.IO.Path.Combine(BasePath, fmodDllName);
			string fmodStudioDllPath = System.IO.Path.Combine(BasePath, fmodStudioDllName);

			System.Collections.Generic.List<string> plugins = GetPlugins(BasePath);

			if (bShortLinkNames)
			{
				// For android we have provided the paths to all architectures above
				// Just provide the name without "lib" and without extension
				PublicAdditionalLibraries.Add(System.String.Format("fmod{0}{1}", configName, platformMidName));
				PublicAdditionalLibraries.Add(System.String.Format("fmodstudio{0}{1}", configName, platformMidName));
			}
			else if (bLinkFromBinaries)
			{
				PublicAdditionalLibraries.Add(fmodLibPath);
				PublicAdditionalLibraries.Add(fmodStudioLibPath);
			}
			else
			{
				string LibPath = System.IO.Path.Combine(ModuleDirectory, "../../Libs/Mac/");
				PublicAdditionalLibraries.Add(System.String.Format("{0}libfmod{1}.dylib", LibPath, configName));			
				PublicAdditionalLibraries.Add(System.String.Format("{0}libfmodStudio{1}.dylib", LibPath, configName));		
			}

			if (bAddRuntimeDependencies)
			{
				RuntimeDependencies.Add(new RuntimeDependency(fmodDllPath));
				RuntimeDependencies.Add(new RuntimeDependency(fmodStudioDllPath));
				foreach (string plugin in plugins)
				{
					string pluginPath = System.IO.Path.Combine(BasePath, plugin + dllExtension);
					System.Console.WriteLine("Adding reference to FMOD plugin: " + pluginPath);
					RuntimeDependencies.Add(new RuntimeDependency(pluginPath));
				}
			}

			if (copyThirdPartyPath.Length != 0)
			{
				string destPath = System.IO.Path.Combine(UEBuildConfiguration.UEThirdPartyBinariesDirectory, copyThirdPartyPath);
				System.IO.Directory.CreateDirectory(destPath);

				string fmodDllDest = System.IO.Path.Combine(destPath, fmodDllName);
				string fmodStudioDllDest = System.IO.Path.Combine(destPath, fmodStudioDllName);

				CopyFile(fmodDllPath, fmodDllDest);
				CopyFile(fmodStudioDllPath, fmodStudioDllDest);
			}

			if (bAddDelayLoad)
			{
				PublicDelayLoadDLLs.AddRange(
						new string[] {
							fmodDllName,
							fmodStudioDllName
							}
						);
			}

			if (Target.Platform == UnrealTargetPlatform.Android)
			{
				string APLName = System.String.Format("FMODStudio{0}_APL.xml", configName);
				string RelAPLPath = Utils.MakePathRelativeTo(System.IO.Path.Combine(ModuleDirectory, APLName), BuildConfiguration.RelativeEnginePath);
				System.Console.WriteLine("Adding {0}", RelAPLPath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", RelAPLPath));
				foreach (string PluginName in System.IO.Directory.GetFiles(BasePath))
				{
					if (PluginName.EndsWith("_APL.xml", System.StringComparison.OrdinalIgnoreCase))
					{
						string RelPluginPath = Utils.MakePathRelativeTo(PluginName, BuildConfiguration.RelativeEnginePath);
						System.Console.WriteLine("Adding {0}", RelPluginPath);
						AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", RelPluginPath));
					}
				}
			}
		}

		private void CopyFile(string source, string dest)
		{
			//System.Console.WriteLine("Copying {0} to {1}", source, dest);
			if (System.IO.File.Exists(dest))
			{
				System.IO.File.SetAttributes(dest, System.IO.File.GetAttributes(dest) & ~System.IO.FileAttributes.ReadOnly);
			}
			try
			{
				System.IO.File.Copy(source, dest, true);
			}
			catch (System.Exception ex)
			{
				System.Console.WriteLine("Failed to copy file: {0}", ex.Message);
			}
		}

		private System.Collections.Generic.List<string> GetPlugins(string BasePath)
		{
			System.Collections.Generic.List<string> AllPlugins = new System.Collections.Generic.List<string>();
			string PluginListName = System.IO.Path.Combine(BasePath, "plugins.txt");
			if (System.IO.File.Exists(PluginListName))
			{
				try
				{
					foreach (string FullEntry in System.IO.File.ReadAllLines(PluginListName))
					{
						string Entry = FullEntry.Trim();
						if (Entry.Length > 0)
						{
							AllPlugins.Add(Entry);
						}
					}
				}
				catch (System.Exception ex)
				{
					System.Console.WriteLine("Failed to read plugin list file: {0}", ex.Message);
				}
			}
			return AllPlugins;
		}
	}
}