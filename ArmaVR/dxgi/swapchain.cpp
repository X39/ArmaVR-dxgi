#include "swapchain.hpp"
#include "../util.hpp"

#include <d3d11.h>
#include <iostream>

DXGISwapChainLayer::DXGISwapChainLayer(IDXGISwapChain* swp) : mSwapchain(swp)
{
    IDXGIDevice1* dev;
    GetDevice(__uuidof(IDXGIDevice1), (void**)(&dev));
    dev->SetMaximumFrameLatency(1);
    dev->Release();
}

HRESULT __stdcall DXGISwapChainLayer::QueryInterface(REFIID riid, void** ppvObject)
{
    F_PRINT;
    return mSwapchain->QueryInterface(riid, ppvObject);
}

ULONG __stdcall DXGISwapChainLayer::AddRef(void)
{
    F_PRINT;
    return mSwapchain->AddRef();
}

ULONG __stdcall DXGISwapChainLayer::Release(void)
{
    F_PRINT;
    auto r = mSwapchain->Release();
    if (r == 0)
        delete this;
    return r;
}

HRESULT __stdcall DXGISwapChainLayer::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData)
{
    F_PRINT;
    return mSwapchain->SetPrivateData(Name, DataSize, pData);
}

HRESULT __stdcall DXGISwapChainLayer::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown)
{
    F_PRINT;
    return mSwapchain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT __stdcall DXGISwapChainLayer::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData)
{
    F_PRINT;
    return mSwapchain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT __stdcall DXGISwapChainLayer::GetParent(REFIID riid, void** ppParent)
{
    F_PRINT;
    return mSwapchain->GetParent(riid, ppParent);
}

HRESULT __stdcall DXGISwapChainLayer::GetDevice(REFIID riid, void** ppDevice)
{
    F_PRINT;
    return mSwapchain->GetDevice(riid, ppDevice);
}

HRESULT __stdcall DXGISwapChainLayer::Present(UINT SyncInterval, UINT Flags)
{
    return mSwapchain->Present(0, Flags);
}

HRESULT __stdcall DXGISwapChainLayer::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface)
{
    F_PRINT;
    return mSwapchain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT __stdcall DXGISwapChainLayer::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget)
{
    F_PRINT;
    return mSwapchain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT __stdcall DXGISwapChainLayer::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget)
{
    //F_PRINT;
    auto r = mSwapchain->GetFullscreenState(pFullscreen, ppTarget);
    return r;
}

HRESULT __stdcall DXGISwapChainLayer::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc)
{
    //F_PRINT;
    auto r = mSwapchain->GetDesc(pDesc);
    pDesc->SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    pDesc->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    return r;

}

HRESULT __stdcall DXGISwapChainLayer::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    F_PRINT;
    return mSwapchain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT __stdcall DXGISwapChainLayer::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters)
{
    F_PRINT;
    return mSwapchain->ResizeTarget(pNewTargetParameters);
}

HRESULT __stdcall DXGISwapChainLayer::GetContainingOutput(IDXGIOutput** ppOutput)
{
    F_PRINT;
    return mSwapchain->GetContainingOutput(ppOutput);
}

HRESULT __stdcall DXGISwapChainLayer::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats)
{
    F_PRINT;
    return mSwapchain->GetFrameStatistics(pStats);
}

HRESULT __stdcall DXGISwapChainLayer::GetLastPresentCount(UINT* pLastPresentCount)
{
    F_PRINT;
    return mSwapchain->GetLastPresentCount(pLastPresentCount);
}
