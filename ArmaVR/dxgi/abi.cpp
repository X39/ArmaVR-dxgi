#include "abi.hpp"
#include "../util.hpp"

#define CINTERFACE
#define D3D11_NO_HELPERS
#include <dxgi.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_1.h>

armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(::IDXGIFactory* factory)
{
    return reinterpret_cast<CreateSwapChain>(factory->lpVtbl->CreateSwapChain);
}

void armavr::dxgi::addresses::IDXGIFactory::set_CreateSwapChain(::IDXGIFactory* factory, CreateSwapChain addr)
{
    DWORD original_protect;
    VirtualProtect(&factory->lpVtbl->CreateSwapChain, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    factory->lpVtbl->CreateSwapChain = addr;
    VirtualProtect(&factory->lpVtbl->CreateSwapChain, sizeof(void*), original_protect, &original_protect);
}

armavr::dxgi::addresses::ID3D11DeviceContext1::ClearRenderTargetView armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(::ID3D11DeviceContext1* deviceContext)
{
    return reinterpret_cast<ClearRenderTargetView>(deviceContext->lpVtbl->ClearRenderTargetView);
}

void armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(::ID3D11DeviceContext1* deviceContext, ClearRenderTargetView addr)
{
    DWORD original_protect;
    VirtualProtect(&deviceContext->lpVtbl->ClearRenderTargetView, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    deviceContext->lpVtbl->ClearRenderTargetView = addr;
    VirtualProtect(&deviceContext->lpVtbl->ClearRenderTargetView, sizeof(void*), original_protect, &original_protect);
}

armavr::dxgi::addresses::ID3D11DeviceContext1::ClearDepthStencilView armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(::ID3D11DeviceContext1* deviceContext)
{
    return reinterpret_cast<ClearDepthStencilView>(deviceContext->lpVtbl->ClearDepthStencilView);
}

void armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(::ID3D11DeviceContext1* deviceContext, ClearDepthStencilView addr)
{
    DWORD original_protect;
    VirtualProtect(&deviceContext->lpVtbl->ClearRenderTargetView, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    deviceContext->lpVtbl->ClearDepthStencilView = addr;
    VirtualProtect(&deviceContext->lpVtbl->ClearRenderTargetView, sizeof(void*), original_protect, &original_protect);
}