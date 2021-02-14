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

armavr::dxgi::addresses::ID3D11DeviceContext1::ClearView armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(::ID3D11DeviceContext1* deviceContext)
{
    return reinterpret_cast<ClearView>(deviceContext->lpVtbl->ClearView);
}

void armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(::ID3D11DeviceContext1* deviceContext, ClearView addr)
{
    DWORD original_protect;
    VirtualProtect(&deviceContext->lpVtbl->ClearView, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    deviceContext->lpVtbl->ClearView = addr;
    VirtualProtect(&deviceContext->lpVtbl->ClearView, sizeof(void*), original_protect, &original_protect);
}

armavr::dxgi::addresses::ID3D11DeviceContext1::OMSetRenderTargets armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(::ID3D11DeviceContext1* pDeviceContext)
{
    return reinterpret_cast<OMSetRenderTargets>(pDeviceContext->lpVtbl->OMSetRenderTargets);
}

void armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(::ID3D11DeviceContext1* pDeviceContext, OMSetRenderTargets addr)
{
    DWORD original_protect;
    VirtualProtect(&pDeviceContext->lpVtbl->OMSetRenderTargets, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    pDeviceContext->lpVtbl->OMSetRenderTargets = addr;
    VirtualProtect(&pDeviceContext->lpVtbl->OMSetRenderTargets, sizeof(void*), original_protect, &original_protect);
}

armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(::ID3D11Device* pDevice)
{
    return reinterpret_cast<CreateRenderTargetView>(pDevice->lpVtbl->CreateRenderTargetView);
}

void armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(::ID3D11Device* pDevice, CreateRenderTargetView addr)
{
    DWORD original_protect;
    VirtualProtect(&pDevice->lpVtbl->CreateRenderTargetView, sizeof(void*), PAGE_EXECUTE_READWRITE, &original_protect);
    pDevice->lpVtbl->CreateRenderTargetView = addr;
    VirtualProtect(&pDevice->lpVtbl->CreateRenderTargetView, sizeof(void*), original_protect, &original_protect);
}
