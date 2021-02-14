#include "swapchain.hpp"
#include "../util.hpp"
#include "../hooker.hpp"
#include "abi.hpp"

#include <d3d11.h>
#include <d3d11_1.h>
#include <iostream>

namespace hooks
{
    struct ClearRenderTargetView : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::ClearRenderTargetView original;

        ClearRenderTargetView(ID3D11DeviceContext1* dc) : hooker::hook("ClearRenderTargetView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(deviceContext, callback);
            }
        }
        ClearRenderTargetView(ID3D11DeviceContext* dc) : hooker::hook("ClearRenderTargetView"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(deviceContext, callback);
            }
        }
        virtual ~ClearRenderTargetView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::ClearRenderTargetView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11RenderTargetView* pRenderTargetView,
            /* [annotation] */
            _In_  const FLOAT ColorRGBA[4])
        {
            F_PRINT;

            original(This, pRenderTargetView, ColorRGBA);
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::ClearRenderTargetView ClearRenderTargetView::original = 0;


    struct ClearDepthStencilView : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::ClearDepthStencilView original;

        ClearDepthStencilView(ID3D11DeviceContext1* dc) : hooker::hook("ClearDepthStencilView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearDepthStencilView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(deviceContext, callback);
            }
        }
        ClearDepthStencilView(ID3D11DeviceContext* dc) : hooker::hook("ClearDepthStencilView"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearDepthStencilView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(deviceContext, callback);
            }
        }
        virtual ~ClearDepthStencilView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::ClearDepthStencilView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11DepthStencilView* pDepthStencilView,
            /* [annotation] */
            _In_  UINT ClearFlags,
            /* [annotation] */
            _In_  FLOAT Depth,
            /* [annotation] */
            _In_  UINT8 Stencil)
        {
            F_PRINT;

            original(This, pDepthStencilView, ClearFlags, Depth, Stencil);
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::ClearDepthStencilView ClearDepthStencilView::original = 0;

    struct ClearView : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::ClearView original;

        ClearView(ID3D11DeviceContext1* dc) : hooker::hook("ClearView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(deviceContext, callback);
            }
        }
        ClearView(ID3D11DeviceContext* dc) : hooker::hook("ClearView"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(deviceContext, callback);
            }
        }
        virtual ~ClearView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::ClearView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ::ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11View* pView,
            /* [annotation] */
            _In_  const FLOAT* Color,
            /* [annotation] */
            const RECT* pRect,
            UINT NumRects)
        {
            F_PRINT;

            original(This, pView, Color, pRect, NumRects);
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::ClearView ClearView::original = 0;

    struct OMSetRenderTargets : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static void* render_target;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::OMSetRenderTargets original;

        OMSetRenderTargets(ID3D11DeviceContext1* dc) : hooker::hook("OMSetRenderTargets"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(deviceContext, callback);
            }
        }
        OMSetRenderTargets(ID3D11DeviceContext* dc) : hooker::hook("OMSetRenderTargets"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::OMSetRenderTargets" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(deviceContext, callback);
            }
        }
        virtual ~OMSetRenderTargets()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::OMSetRenderTargets" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ::ID3D11DeviceContext1* This,
            UINT                   NumViews,
            ID3D11RenderTargetView * const *ppRenderTargetViews,
            ID3D11DepthStencilView *pDepthStencilView)
        {
            for (UINT i = 0; i < NumViews; ++i)
            {
                if (ppRenderTargetViews[i] == render_target)
                {
                    F_PRINT;
                }
            }

            original(This, NumViews, ppRenderTargetViews, pDepthStencilView);
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::OMSetRenderTargets OMSetRenderTargets::original = 0;
    void* OMSetRenderTargets::render_target = nullptr;


    struct CreateRenderTargetView : public hooker::hook
    {
        ID3D11Device* device;
        static void** capture_resource; // resource to capture
        static armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView original;

        CreateRenderTargetView(ID3D11Device* dc) : hooker::hook("CreateRenderTargetView"), device(dc)
        {
            if (armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device) != original)
            {
                std::cout << "Aquiring hook of ID3D11Device::CreateRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device);
                armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(device, callback);
            }
        }
        virtual ~CreateRenderTargetView()
        {
            if (armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device) != original)
            {
                std::cout << "Releasing hook of ID3D11Device::CreateRenderTargetView" << std::endl;
                armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(device, original);
            }
            device->Release();
        }
        static HRESULT STDMETHODCALLTYPE callback(
            ::ID3D11Device                      *This,
            ID3D11Resource                      *pResource,
            const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
            ID3D11RenderTargetView              **ppRTView
        )
        {
            auto result = original(This, pResource, pDesc, ppRTView);
            if (pResource == *capture_resource)
            {
                F_PRINT;
                std::cout << (void*)*ppRTView << std::endl;
                OMSetRenderTargets::render_target = *ppRTView;
            }

            return result;
        }
    };
    armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView CreateRenderTargetView::original = 0;
    void** CreateRenderTargetView::capture_resource = nullptr;
}


DXGISwapChainLayer::DXGISwapChainLayer(IDXGISwapChain* swp)
    : m_swapchain(swp)
    , m_device(nullptr)
    , m_device_context(nullptr)
    , m_swapchain_back_buffer(nullptr)
{
    IDXGIDevice1* dev;
    GetDevice(__uuidof(IDXGIDevice1), (void**)(&dev));
    dev->SetMaximumFrameLatency(1);
    dev->Release();

    swp->GetDevice(__uuidof(ID3D11Device), (void**)&m_device);
    m_device->GetImmediateContext(&m_device_context);

    hooks::CreateRenderTargetView::capture_resource = &m_swapchain_back_buffer;
    hooker::register_hook<hooks::CreateRenderTargetView>(m_device);

    hooker::register_hook<hooks::ClearRenderTargetView>(m_device_context);
    hooker::register_hook<hooks::ClearDepthStencilView>(m_device_context);
    hooker::register_hook<hooks::ClearView>(m_device_context);
    hooker::register_hook<hooks::OMSetRenderTargets>(m_device_context);
}

HRESULT __stdcall DXGISwapChainLayer::QueryInterface(REFIID riid, void** ppvObject)
{
    F_PRINT;
    return m_swapchain->QueryInterface(riid, ppvObject);
}

ULONG __stdcall DXGISwapChainLayer::AddRef(void)
{
    F_PRINT;
    return m_swapchain->AddRef();
}

ULONG __stdcall DXGISwapChainLayer::Release(void)
{
    F_PRINT;
    m_device->Release();
    auto r = m_swapchain->Release();
    if (r == 0)
        delete this;
    return r;
}

HRESULT __stdcall DXGISwapChainLayer::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData)
{
    F_PRINT;
    return m_swapchain->SetPrivateData(Name, DataSize, pData);
}

HRESULT __stdcall DXGISwapChainLayer::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown)
{
    F_PRINT;
    return m_swapchain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT __stdcall DXGISwapChainLayer::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData)
{
    F_PRINT;
    return m_swapchain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT __stdcall DXGISwapChainLayer::GetParent(REFIID riid, void** ppParent)
{
    F_PRINT;
    return m_swapchain->GetParent(riid, ppParent);
}

HRESULT __stdcall DXGISwapChainLayer::GetDevice(REFIID riid, void** ppDevice)
{
    F_PRINT;
    return m_swapchain->GetDevice(riid, ppDevice);
}

HRESULT __stdcall DXGISwapChainLayer::Present(UINT SyncInterval, UINT Flags)
{
    F_PRINT;
    return m_swapchain->Present(0, Flags);
}

HRESULT __stdcall DXGISwapChainLayer::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface)
{
    F_PRINT;
    auto result = m_swapchain->GetBuffer(Buffer, riid, ppSurface);
    if (m_swapchain_back_buffer == nullptr)
    {
        m_swapchain_back_buffer = *ppSurface;
    }
    return result;
}

HRESULT __stdcall DXGISwapChainLayer::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget)
{
    F_PRINT;
    return m_swapchain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT __stdcall DXGISwapChainLayer::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget)
{
    //F_PRINT;
    auto r = m_swapchain->GetFullscreenState(pFullscreen, ppTarget);
    return r;
}

HRESULT __stdcall DXGISwapChainLayer::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc)
{
    //F_PRINT;
    auto r = m_swapchain->GetDesc(pDesc);
    pDesc->SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    pDesc->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    return r;

}

HRESULT __stdcall DXGISwapChainLayer::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    F_PRINT;
    return m_swapchain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT __stdcall DXGISwapChainLayer::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters)
{
    F_PRINT;
    return m_swapchain->ResizeTarget(pNewTargetParameters);
}

HRESULT __stdcall DXGISwapChainLayer::GetContainingOutput(IDXGIOutput** ppOutput)
{
    F_PRINT;
    return m_swapchain->GetContainingOutput(ppOutput);
}

HRESULT __stdcall DXGISwapChainLayer::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats)
{
    F_PRINT;
    return m_swapchain->GetFrameStatistics(pStats);
}

HRESULT __stdcall DXGISwapChainLayer::GetLastPresentCount(UINT* pLastPresentCount)
{
    F_PRINT;
    return m_swapchain->GetLastPresentCount(pLastPresentCount);
}
