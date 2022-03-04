---lua5.4---

workspace "Ember"
    architecture "x64"
    startproject "sandbox"

    configurations { 
        "Debug", 
        "Release",
        "Dist"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--[[
-------------------------------Ember---------------------------
--]]
project "Ember"
    location "Ember"
    kind "SharedLib"    -- dll and ConsoleApp .etc
    language "C++"

    targetdir ( "bin/" .. outputDir .. "/%{prj.name}" )   -- 编译结果目录
    objdir ( "bin-int/" .. outputDir .. "/%{prj.name}" )  -- 中间文件目录

    -- 源文件
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- 第三方库文件包含
    includedirs {
        "%{prj.name}/third-party/spdlog/include"
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
            "EMBER_BUILD_DLL"
        }

        -- 编译后命令 将dll拷贝到启动项目目录
        postbuildcommands { "{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/sandbox" }

    
    ------------------configurations:Debug--------------------------
    filter "configurations:Debug"
        defines "EMBER_DEBUG"
        symbols "On"    -- 是否生成调试符号表
    

    ------------------configurations:Release------------------------
    filter "configurations:Release"
        defines "EMBER_RELAESE"
        optimize "On"   -- 指定构建目标配置时使用的优​​化级别和类型



    ------------------configurations:Dist---------------------------
    filter "configurations:Dist" 
        defines "EMBER_DIST"
        optimize "On"
    


--[[
-------------------------------sandbox---------------------------
--]]
project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ( "bin/" .. outputDir .. "/%{prj.name}" )   -- 编译结果目录
    objdir ( "bin-int/" .. outputDir .. "/%{prj.name}" )  -- 中间文件目录

    -- 源文件
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- 包含文件
    includedirs {
        "Ember/third-party/spdlog/include",
        "Ember/src"
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
        symbols "On"    -- 是否生成调试符号表
    

    ------------------configurations:Release------------------------
    filter "configurations:Release"
        defines "EMBER_RELAESE"
        optimize "On"   -- 指定构建目标配置时使用的优​​化级别和类型



    ------------------configurations:Dist---------------------------
    filter "configurations:Dist"
        defines "EMBER_DIST"
        optimize "On"