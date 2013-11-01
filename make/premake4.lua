dofile("premake-helper.lua")

solution "Reaping2"
	location "../build"
	
	libdirs {
		"../deps/boost_1_54_0/stage/lib",
		"../deps/glfw-3.0.3/build/src/Release",
		"../deps/glfw-3.0.3/build/src/Debug",
		"../deps/glfw-3.0.3/build/src",
		"../deps/zlib-1.2.8/build/Debug",
		"../deps/zlib-1.2.8/build/Release",
		"../deps/lpng166/build/Debug",
		"../deps/lpng166/build/Release"
	}
	includedirs {
		"../src",
		"../deps/boost_1_54_0",
		"../deps/glfw-3.0.3/include",
		"../deps/glm_0_9_4_6",
		"../deps/zlib-1.2.8",
		"../deps/zlib-1.2.8/build",
		"../deps/lpng166"
	}
	links { "glfw3" }
	
	-- flags { "FatalWarnings" }

	configurations { "Debug", "Release" }
	
	configuration { "Debug" }
		targetdir "../bin/debug"
	configuration { "Release" }
		targetdir "../bin/release"
 

	configuration { "Debug*" }
		defines { "_DEBUG", "DEBUG" }
		flags   { "Symbols" }
		if os.is("windows") then
			links { "opengl32", "zlibstaticd", "libpng16_staticd" }
			linkoptions	{ "/nodefaultlib:libmsvcrtd.lib", "/nodefaultlib:libmsvcrt.lib" }
		else
			links { "Xi", "Xrandr", "GL", "boost_system" }
		end
 
	configuration { "Release*" }
		defines { "NDEBUG" }
		flags   { "Optimize" }
		if os.is("windows") then
			links { "opengl32", "zlibstatic", "libpng16_static" }
			linkoptions	{ "/nodefaultlib:libmsvcrt.lib" }
		else
			links { "Xi", "Xrandr", "GL", "boost_system" }
		end

	newaction 
	{
		trigger = "clean",
		description = "Cleaning up",
		execute = function()
			os.execute("echo Cleaning up stuff")
			os.rmdir("../bin")
		end
	}
	 

	project "core"
		language "C++"
		kind "StaticLib"
		setup_files_for_project("core")
	 
	project "input"
		language "C++"
		kind "StaticLib"
		setup_files_for_project("input")
	 
	project "platform"
		language "C++"
		kind "StaticLib"
		setup_files_for_project("platform")

	project "render"
		language "C++"
		kind "StaticLib"
		setup_files_for_project("render")
		
	project "main"
		language "C++"
		kind "ConsoleApp"

		links { "core", "input", "platform", "render"}
		setup_files_for_project("main")

		files  { "../src/**.h", "../src/**.cpp" }

	project "r2pkg"
		kind     "ConsoleApp"
		language "C++"

		if os.is("windows") then
			-- no boost here, the headers do this job with visual studio
			links { "opengl32" }
			linkoptions  { "/nodefaultlib:libmsvcrt.lib", "/nodefaultlib:libmsvcrtd.lib" }
		else
			links { "boost_system" }
		end
		files  { "../tools/r2pkg/**.h", "../tools/r2pkg/**.cpp", "../src/platform/**.h", "../src/platform/**.cpp" }
	 
		configuration { "Debug*" }
			defines { "_DEBUG", "DEBUG" }
			flags   { "Symbols" }
			if os.is("windows") then
				links { "zlibstaticd", "libpng16_staticd" }
			end
	 
		configuration { "Release*" }
			defines { "NDEBUG" }
			flags   { "Optimize" }
			if os.is("windows") then
				links { "zlibstatic", "libpng16_static" }
			end