#include "abi.hpp"
#include "../util.hpp"

#define CINTERFACE
#define D3D11_NO_HELPERS
#include <dxgi.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_1.h>

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

armavr::dxgi::addresses::ID3D11DeviceContext::ClearRenderTargetView armavr::dxgi::addresses::ID3D11DeviceContext::get_ClearRenderTargetView(void* pDeviceContext)
{
    auto deviceContext = reinterpret_cast<::ID3D11DeviceContext1*>(pDeviceContext);
    return reinterpret_cast<ClearRenderTargetView>(deviceContext->lpVtbl->ClearRenderTargetView);
}

void armavr::dxgi::addresses::ID3D11DeviceContext::set_ClearRenderTargetView(void* pDeviceContext, ClearRenderTargetView addr)
{
    auto deviceContext = reinterpret_cast<::ID3D11DeviceContext1*>(pDeviceContext);

    DWORD original_protect;
    VirtualProtect(&deviceContext->lpVtbl->ClearRenderTargetView, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    deviceContext->lpVtbl->ClearRenderTargetView = addr;
    VirtualProtect(&deviceContext->lpVtbl->ClearRenderTargetView, sizeof(void*), original_protect, &original_protect);
}