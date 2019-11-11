--premake5.lua

workspace "HTEST"
    configurations{"Debug", "Release"}

project "HashTest"

    kind "ConsoleApp"
    language "C++"
    targetdir "../bin/"
    includedirs {"../include"}
    links {"sfml-graphics", "sfml-window" , "sfml-system"}
    -- buildoptions{"-O3"}
    -- buildoptions{"-g", "-Wall"}
    files {"../src/*.cpp"}
    -- symbols "On"

    configuration "Release"
        buildoptions{"-O3"}
        defines {"NDEBUG"}
        optimize "Speed"

    configuration "Debug"
        buildoptions{"-g", "-Wall"}
        symbols "On"  
        flags { "Symbols" }




