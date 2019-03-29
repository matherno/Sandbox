workspace "Sandbox"
   configurations { "debug", "release" }

project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin_%{cfg.buildcfg}"
   
   files { "src/**.h", "src/**.cpp" }
   
   libdirs { "./dependencies/mathernogl" }

   links {"MathernoGL", "GL", "GLEW", "glfw", "freeimage" }
   
   includedirs { "./dependencies", "./dependencies/mathernogl", "./src", "./dependencies/misc" }

   cppdialect "C++11"

   filter "configurations:debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:release"
      defines { "NDEBUG" }
      optimize "On"