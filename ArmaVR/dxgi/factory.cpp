#include "factory.hpp"
#include "dxgi.hpp"

#include <iostream>

#ifdef _DEBUG
#define F_PRINT std::cout << __FUNCTION__ "\n" << std::endl
#else
#define F_PRINT
#endif


armavr::dxgi::factory::factory(UINT Flags, REFIID riid)
{
    CreateDXGIFactoryActual(Flags, riid, (void**)(&mFactory));
}

HRESULT __stdcall armavr::dxgi::factory::QueryInterface(REFIID riid, void** ppvObject)
{
    F_PRINT;
    return mFactory->QueryInterface(riid, ppvObject);
}

ULONG __stdcall armavr::dxgi::factory::AddRef(void)
{
    F_PRINT;
    return mFactory->AddRef();
}

ULONG __stdcall armavr::dxgi::factory::Release(void)
{
    F_PRINT;
    auto r = mFactory->Release();
    if (r == 0)
        delete this;
    return r;
}

HRESULT __stdcall armavr::dxgi::factory::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData)
{
    F_PRINT;
    return mFactory->SetPrivateData(Name, DataSize, pData);
}

HRESULT __stdcall armavr::dxgi::factory::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown)
{
    F_PRINT;
    return mFactory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT __stdcall armavr::dxgi::factory::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData)
{
    F_PRINT;
    return mFactory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT __stdcall armavr::dxgi::factory::GetParent(REFIID riid, void** ppParent)
{
    F_PRINT;
    return mFactory->GetParent(riid, ppParent);
}

HRESULT __stdcall armavr::dxgi::factory::EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter)
{
    F_PRINT;
    return mFactory->EnumAdapters(Adapter, ppAdapter);
}

HRESULT __stdcall armavr::dxgi::factory::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
    F_PRINT;
    return mFactory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT __stdcall armavr::dxgi::factory::GetWindowAssociation(HWND* pWindowHandle)
{
    F_PRINT;
    return mFactory->GetWindowAssociation(pWindowHandle);
}

HRESULT __stdcall armavr::dxgi::factory::CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
    F_PRINT;
    return mFactory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
}

HRESULT __stdcall armavr::dxgi::factory::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter)
{
    F_PRINT;
    return mFactory->CreateSoftwareAdapter(Module, ppAdapter);
}

/*
HRESULT __stdcall armavr::dxgi::factory::EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter)
{
    return mFactory->EnumAdapters1(Adapter, ppAdapter);
}

BOOL __stdcall armavr::dxgi::factory::IsCurrent(void)
{
    return mFactory->IsCurrent();
}

BOOL __stdcall armavr::dxgi::factory::IsWindowedStereoEnabled(void)
{
    return mFactory->IsWindowedStereoEnabled();
}

HRESULT __stdcall armavr::dxgi::factory::CreateSwapChainForHwnd(IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
    return mFactory->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
}

HRESULT __stdcall armavr::dxgi::factory::CreateSwapChainForCoreWindow(IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
    return mFactory->CreateSwapChainForCoreWindow(pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain);
}

HRESULT __stdcall armavr::dxgi::factory::GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid)
{
    return mFactory->GetSharedResourceAdapterLuid(hResource, pLuid);
}

HRESULT __stdcall armavr::dxgi::factory::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie)
{
    return mFactory->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT __stdcall armavr::dxgi::factory::RegisterStereoStatusEvent(HANDLE hEvent, DWORD* pdwCookie)
{
    return mFactory->RegisterStereoStatusEvent(hEvent, pdwCookie);
}

void __stdcall armavr::dxgi::factory::UnregisterStereoStatus(DWORD dwCookie)
{
    mFactory->UnregisterStereoStatus(dwCookie);
}

HRESULT __stdcall armavr::dxgi::factory::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie)
{
    return mFactory->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT __stdcall armavr::dxgi::factory::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD* pdwCookie)
{
    return mFactory->RegisterOcclusionStatusEvent(hEvent, pdwCookie);
}

void __stdcall armavr::dxgi::factory::UnregisterOcclusionStatus(DWORD dwCookie)
{
    mFactory->UnregisterOcclusionStatus(dwCookie);
}

HRESULT __stdcall armavr::dxgi::factory::CreateSwapChainForComposition(IUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
    return mFactory->CreateSwapChainForComposition(pDevice, pDesc, pRestrictToOutput, ppSwapChain);
}
*/