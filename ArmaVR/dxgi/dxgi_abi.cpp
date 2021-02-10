#include "dxgi_abi.hpp"

#ifndef CINTERFACE
#define CINTERFACE
#include <dxgi.h>
#undef CINTERFACE
#endif

armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(void* pFactory)
{
    auto factory = reinterpret_cast<::IDXGIFactory*>(pFactory);
    return reinterpret_cast<CreateSwapChain>(factory->lpVtbl->CreateSwapChain);
}

void armavr::dxgi::addresses::IDXGIFactory::set_CreateSwapChain(void* pFactory, CreateSwapChain addr)
{
    auto factory = reinterpret_cast<::IDXGIFactory*>(pFactory);

    DWORD original_protect;
    VirtualProtect(&factory->lpVtbl->CreateSwapChain, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    factory->lpVtbl->CreateSwapChain = addr;
    VirtualProtect(&factory->lpVtbl->CreateSwapChain, sizeof(void*), original_protect, &original_protect);
}
