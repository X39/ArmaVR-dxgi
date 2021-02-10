#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

struct IDXGIFactory;
struct IUnknown;
struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;
namespace armavr::dxgi::addresses
{
    namespace IDXGIFactory
    {
        typedef HRESULT(STDMETHODCALLTYPE* CreateSwapChain)(
            ::IDXGIFactory* This,
            ::IUnknown* pDevice,
            ::DXGI_SWAP_CHAIN_DESC* pDesc,
            ::IDXGISwapChain** ppSwapChain);
        [[nodiscard]] CreateSwapChain get_CreateSwapChain(void* pFactory);
        void set_CreateSwapChain(void* pFactory, CreateSwapChain addr);
    }
}