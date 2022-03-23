---lua5.4---

workspace "Ember"
    architecture "x64"
    startproject "sandbox"

    configurations { 
        "Debug", 
        "Release",
        "Dist"
    }

-- define some parameters
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ember/third-party/GLFW/include"
IncludeDir["Glad"] = "Ember/third-party/Glad/include"
IncludeDir["imGUI"] = "Ember/third-party/imGUI/include"
IncludeDir["glm"] = "Ember/third-party/glm/include"



--[[
------------------------- GLFW project -------------------------
--]]
-- runs "Ember/third-party/GLFW/premake5.lua"
include "Ember/third-party/GLFW"
include "Ember/third-party/Glad"
include "Ember/third-party/imGUI"


--[[
------------------------- Ember project ------------------------
--]]
project "Ember"
    location "Ember"
    kind "SharedLib"    -- dll and ConsoleApp .etc
    language "C++"

    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )   -- 编译结果目录
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )  -- 中间文件目录

    pchheader "pch.h"
    pchsource "Ember/src/pch.cpp"

    -- 源文件
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/third-party/glm/glm/**.hpp",
        "%{prj.name}/third-party/glm/glm/**.inl",
        "%{prj.name}/third-party/glm/glm/**.h"
    }

    -- 第三方库文件包含
    includedirs {
        "%{prj.name}/third-party/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGUI}",
        "%{IncludeDir.glm}"
    }

    -- 链接
    links {
        "GLFW",
        "Glad",
        "imGUI",
        "opengl32.lib"
    }


    -- 模式过滤
    ----------------------system:windows----------------------------
    filter "system:windows" 
        cppdialect "C++17"      -- C++ version
        systemversion "latest" -- SDK version
        staticruntime "on"      -- Sets <RuntimeLibrary> to "MultiThreaded"	
        
        -- 预定义
        defines {
            "EMBER_PLATFORM_WINDOWS",
            "EMBER_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        -- 编译后命令 将dll拷贝到启动项目目录
        postbuildcommands { "{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox" }

    
    ------------------configurations:Debug--------------------------
    filter "configurations:Debug"
        defines "EMBER_DEBUG"
        buildoptions "/MDd"
        symbols "On"    -- 是否生成调试符号表
    

    ------------------configurations:Release------------------------
    filter "configurations:Release"
        defines "EMBER_RELAESE"
        buildoptions "/MD"
        optimize "On"   -- 指定构建目标配置时使用的优​​化级别和类型



    ------------------configurations:Dist---------------------------
    filter "configurations:Dist" 
        defines "EMBER_DIST"
        buildoptions "/MD"
        optimize "On"
    


--[[
------------------------- sandbox project------------------------
--]]
project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )   -- 编译结果目录
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )  -- 中间文件目录

    -- 源文件
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- 包含文件
    includedirs {
        "Ember/third-party/spdlog/include",
        "Ember/src",
        "%{IncludeDir.glm}"
    }

    -- 指定要链接的库和项目
    links {
        "Ember"
    }

    -- 模式过滤
    ----------------------system:windows----------------------------
    filter "system:windows"
        cppdialect "C++17"      -- C++ version
        systemversion "latest"  -- SDK version
        staticruntime "on"      -- Sets <RuntimeLibrary> to "MultiThreaded"	
        
        -- 预定义
        defines { "EMBER_PLATFORM_WINDOWS" }


    ------------------configurations:Debug--------------------------
    filter "configurations:Debug"
        defines "EMBER_DEBUG"
        buildoptions "/MDd"
        symbols "On"    -- 是否生成调试符号表
    

    ------------------configurations:Release------------------------
    filter "configurations:Release"
        defines "EMBER_RELAESE"
        buildoptions "/MD"
        optimize "On"   -- 指定构建目标配置时使用的优​​化级别和类型



    ------------------configurations:Dist---------------------------
    filter "configurations:Dist"
        defines "EMBER_DIST"
        buildoptions "/MD"
        optimize "On"