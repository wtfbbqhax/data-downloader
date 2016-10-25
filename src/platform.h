#pragma once

#ifdef WIN32
constexpr auto package_name = "release-mingw32-x86_64.zip";
#elif  __linux__
constexpr auto package_name = "release-linux-x86_64.zip";
#elif  __APPLE__
constexpr auto package_name = "release-darwin-x86_64.zip";
#endif 
