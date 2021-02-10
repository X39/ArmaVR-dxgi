# CMakeList.txt : CMake project for ArmaVr, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library(ArmaVR SHARED "Source.def" "dllmain.cpp" "dllmain.hpp" "hooker.hpp" "hooker.cpp" "dx11/manager.hpp" "dx11/manager.cpp"  "dxgi/dxgi.hpp" "dxgi/dxgi.cpp" "dxgi/factory.hpp" "dxgi/factory.cpp" "dxgi/swapchain.hpp" "dxgi/swapchain.cpp" "dxgi/dxgi_abi.hpp" "dxgi/dxgi_abi.cpp")
set_target_properties(ArmaVR PROPERTIES OUTPUT_NAME "dxgi")
