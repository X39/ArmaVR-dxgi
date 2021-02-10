#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

struct IDXGIFactory;
struct IUnknown;
struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
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
        [[nodiscard]] armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain get_CreateSwapChain(::IDXGIFactory* pFactory);
        void set_CreateSwapChain(::IDXGIFactory* pFactory, CreateSwapChain addr);
    }
    namespace ID3D11DeviceContext1
    {
        typedef void (STDMETHODCALLTYPE* ClearRenderTargetView)(
            ::ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11RenderTargetView* pRenderTargetView,
            /* [annotation] */
            _In_  const FLOAT ColorRGBA[4]);
        [[nodiscard]] armavr::dxgi::addresses::ID3D11DeviceContext1::ClearRenderTargetView get_ClearRenderTargetView(::ID3D11DeviceContext1* pDeviceContext);
        void set_ClearRenderTargetView(::ID3D11DeviceContext1* pDeviceContext, ClearRenderTargetView addr);


        typedef void (STDMETHODCALLTYPE* ClearDepthStencilView)(
            ::ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11DepthStencilView* pDepthStencilView,
            /* [annotation] */
            _In_  UINT ClearFlags,
            /* [annotation] */
            _In_  FLOAT Depth,
            /* [annotation] */
            _In_  UINT8 Stencil);
        [[nodiscard]] armavr::dxgi::addresses::ID3D11DeviceContext1::ClearDepthStencilView get_ClearDepthStencilView(::ID3D11DeviceContext1* pDeviceContext);
        void set_ClearDepthStencilView(::ID3D11DeviceContext1* pDeviceContext, ClearDepthStencilView addr);
    }
}