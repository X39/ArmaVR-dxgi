#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

struct IDXGIFactory;
struct IUnknown;
struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DeviceContext1;
namespace armavr::dxgi::addresses
{
    namespace IDXGIFactory
    {
        typedef HRESULT(STDMETHODCALLTYPE* CreateSwapChain)(
            ::IDXGIFactory* This,
            ::IUnknown* pDevice,
            ::DXGI_SWAP_CHAIN_DESC* pDesc,
            ::IDXGISwapChain** ppSwapChain);
        [[nodiscard]] armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain get_CreateSwapChain(void* pFactory);
        void set_CreateSwapChain(void* pFactory, CreateSwapChain addr);
    }
    namespace ID3D11DeviceContext
    {
        typedef void (STDMETHODCALLTYPE* ClearRenderTargetView)(
            ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11RenderTargetView* pRenderTargetView,
            /* [annotation] */
            _In_  const FLOAT ColorRGBA[4]);
        [[nodiscard]] armavr::dxgi::addresses::ID3D11DeviceContext::ClearRenderTargetView get_ClearRenderTargetView(void* pDeviceContext);
        void set_ClearRenderTargetView(void* pDeviceContext, ClearRenderTargetView addr);
    }
}