# CMakeList.txt : CMake project for ArmaVr, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library(ArmaVR SHARED "Source.def" "dllmain.cpp" "dllmain.hpp" "hooker.hpp" "hooker.cpp" "dxgi/dxgi.hpp" "dxgi/dxgi.cpp" "dxgi/factory.hpp" "dxgi/factory.cpp" "dxgi/swapchain.hpp" "dxgi/swapchain.cpp" "dxgi/abi.hpp" "dxgi/abi.cpp" "dxgi/d3d11.hpp" "dxgi/d3d11.cpp" "dlops.hpp" "dlops.cpp")
set_target_properties(ArmaVR PROPERTIES OUTPUT_NAME "dxgi")
