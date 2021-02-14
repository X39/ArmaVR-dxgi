#pragma once

struct IDXGIFactory;
struct IUnknown;
struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11DeviceContext1;
struct ID3D11View;
struct ID3D11Resource;
struct D3D11_RENDER_TARGET_VIEW_DESC;
struct ID3D11Device;

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

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


        typedef void (STDMETHODCALLTYPE* ClearView)(
            ::ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11View* pView,
            /* [annotation] */
            _In_  const FLOAT Color[4],
            /* [annotation] */
            const RECT* pRect,
            UINT NumRects);
        [[nodiscard]] armavr::dxgi::addresses::ID3D11DeviceContext1::ClearView get_ClearView(::ID3D11DeviceContext1* pDeviceContext);
        void set_ClearView(::ID3D11DeviceContext1* pDeviceContext, ClearView addr);

        typedef void (STDMETHODCALLTYPE* OMSetRenderTargets)(
            ::ID3D11DeviceContext1* This,
            UINT                   NumViews,
            ID3D11RenderTargetView * const *ppRenderTargetViews,
            ID3D11DepthStencilView *pDepthStencilView);
        [[nodiscard]] armavr::dxgi::addresses::ID3D11DeviceContext1::OMSetRenderTargets get_OMSetRenderTargets(::ID3D11DeviceContext1* pDeviceContext);
        void set_OMSetRenderTargets(::ID3D11DeviceContext1* pDeviceContext, OMSetRenderTargets addr);
    }
    namespace ID3D11Device
    {
        typedef HRESULT (STDMETHODCALLTYPE* CreateRenderTargetView)(
            ::ID3D11Device                      *This,
            ID3D11Resource                      *pResource,
            const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
            ID3D11RenderTargetView              **ppRTView
        );
        [[nodiscard]] armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView get_CreateRenderTargetView(::ID3D11Device* pDevice);
        void set_CreateRenderTargetView(::ID3D11Device* pDevice, CreateRenderTargetView addr);
    }
}