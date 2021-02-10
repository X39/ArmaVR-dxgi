#pragma once

#include <dxgi1_3.h>

namespace armavr::dxgi
{
    struct factory : public IDXGIFactory
    {
        IDXGIFactory* mFactory;

        // Inherited via IDXGIFactory2
        virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
        virtual ULONG __stdcall AddRef(void) override;
        virtual ULONG __stdcall Release(void) override;
        virtual HRESULT __stdcall SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) override;
        virtual HRESULT __stdcall SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) override;
        virtual HRESULT __stdcall GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) override;
        virtual HRESULT __stdcall GetParent(REFIID riid, void** ppParent) override;
        virtual HRESULT __stdcall EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter) override;
        virtual HRESULT __stdcall MakeWindowAssociation(HWND WindowHandle, UINT Flags) override;
        virtual HRESULT __stdcall GetWindowAssociation(HWND* pWindowHandle) override;
        virtual HRESULT __stdcall CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) override;
        virtual HRESULT __stdcall CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter) override;

        /*virtual HRESULT __stdcall EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter) override;
        virtual BOOL __stdcall IsCurrent(void) override;
        virtual BOOL __stdcall IsWindowedStereoEnabled(void) override;
        virtual HRESULT __stdcall CreateSwapChainForHwnd(IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        virtual HRESULT __stdcall CreateSwapChainForCoreWindow(IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        virtual HRESULT __stdcall GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid) override;
        virtual HRESULT __stdcall RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie) override;
        virtual HRESULT __stdcall RegisterStereoStatusEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        virtual void __stdcall UnregisterStereoStatus(DWORD dwCookie) override;
        virtual HRESULT __stdcall RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie) override;
        virtual HRESULT __stdcall RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        virtual void __stdcall UnregisterOcclusionStatus(DWORD dwCookie) override;
        virtual HRESULT __stdcall CreateSwapChainForComposition(IUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        */
    public:
        factory(IDXGIFactory* factory) : mFactory(factory) { }
        factory(UINT Flags, REFIID riid);
    };
}