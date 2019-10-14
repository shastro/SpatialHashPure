--premake5.lua


project "HashTest"

    kind "ConsoleApp"
    language "C++"
    targetdir "../bin/"
    includedirs {"../include"}
    links {"sfml-graphics", "sfml-window" , "sfml-system"}
    buildoptions{"-O3"}
    files {"../src/*.cpp"}


    filter "configurations.Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations.Release"
        defines {"NDEBUG"}
        buildoptions{"-O3"}
        optimize "Speed"

