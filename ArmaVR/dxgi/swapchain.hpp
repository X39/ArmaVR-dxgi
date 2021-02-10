#pragma once

#include <dxgi.h>

class DXGISwapChainLayer : public IDXGISwapChain
{
    IDXGISwapChain* mSwapchain;

public:

    DXGISwapChainLayer(IDXGISwapChain* swap);

    // Inherited via IDXGISwapChain
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
    virtual ULONG __stdcall AddRef(void) override;
    virtual ULONG __stdcall Release(void) override;
    virtual HRESULT __stdcall SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) override;
    virtual HRESULT __stdcall SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) override;
    virtual HRESULT __stdcall GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) override;
    virtual HRESULT __stdcall GetParent(REFIID riid, void** ppParent) override;
    virtual HRESULT __stdcall GetDevice(REFIID riid, void** ppDevice) override;
    virtual HRESULT __stdcall Present(UINT SyncInterval, UINT Flags) override;
    virtual HRESULT __stdcall GetBuffer(UINT Buffer, REFIID riid, void** ppSurface) override;
    virtual HRESULT __stdcall SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget) override;
    virtual HRESULT __stdcall GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget) override;
    virtual HRESULT __stdcall GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) override;
    virtual HRESULT __stdcall ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) override;
    virtual HRESULT __stdcall ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) override;
    virtual HRESULT __stdcall GetContainingOutput(IDXGIOutput** ppOutput) override;
    virtual HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) override;
    virtual HRESULT __stdcall GetLastPresentCount(UINT* pLastPresentCount) override;
};