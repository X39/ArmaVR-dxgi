#include "d3d11.hpp"
#include "abi.hpp"
#include "../util.hpp"
#include "../dlops.hpp"
#include "../hooker.hpp"

namespace hooks
{
    struct ClearRenderTargetView : public hooker::hook
    {
        ID3D11DeviceContext* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext::ClearRenderTargetView original;

        ClearRenderTargetView(ID3D11DeviceContext* dc) : hooker::hook("ClearRenderTargetView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext::ClearRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext::get_ClearRenderTargetView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext::set_ClearRenderTargetView(deviceContext, hooked);
            }
        }
        virtual ~ClearRenderTargetView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext::ClearRenderTargetView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext::set_ClearRenderTargetView(deviceContext, original);
            }
        }
        static void STDMETHODCALLTYPE hooked(
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
    armavr::dxgi::addresses::ID3D11DeviceContext::ClearRenderTargetView ClearRenderTargetView::original = 0;
}


HRESULT WINAPI D3D11CreateDeviceHooked(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _COM_Outptr_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    auto& dl = dlops::get("C:/Windows/System32/D3D11.dll");
    auto cProc = dl.resolve<HRESULT WINAPI(_In_opt_ IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
        _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL*, UINT, UINT, _COM_Outptr_opt_ ID3D11Device**,
        _Out_opt_ D3D_FEATURE_LEVEL*, _COM_Outptr_opt_ ID3D11DeviceContext**)>("D3D11CreateDevice");
    F_PRINT;

    std::cout << "D3D11CreateDevice with { " <<
        "IDXGIAdapter*: " << "0x" << std::hex << pAdapter << ", " <<
        "D3D_DRIVER_TYPE: " << "0x" << std::hex << DriverType << ", " <<
        "HMODULE: " << "0x" << std::hex << Software << ", " <<
        "Flags: " << "0x" << std::hex << Flags << ", " <<
        "D3D_FEATURE_LEVEL: " << "0x" << std::hex << pFeatureLevels << ", " <<
        "FeatureLevels: " << "0x" << std::hex << FeatureLevels << ", " <<
        "SDKVersion: " << "0x" << std::hex << SDKVersion << ", " <<
        "ID3D11Device**: " << "0x" << std::hex << ppDevice << ", " <<
        "D3D_FEATURE_LEVEL*: " << "0x" << std::hex << pFeatureLevel << ", " <<
        "ID3D11DeviceContext**: " << "0x" << std::hex << ppImmediateContext <<
        " }" << std::endl;

    HRESULT result = ERROR;

    if (FAILED(result = cProc(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext)))
    {
        std::cout << "Failed to call d3d11.dll -> D3D11CreateDevice" << std::endl;
        return result;
    }

    hooker::register_hook<hooks::ClearRenderTargetView>(*ppImmediateContext);
    return 0;
}

HRESULT WINAPI D3D11CreateDeviceAndSwapChainHooked(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    _COM_Outptr_opt_ IDXGISwapChain** ppSwapChain,
    _COM_Outptr_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    auto& dl = dlops::get("C:/Windows/System32/D3D11.dll");
    auto cProc = dl.resolve<HRESULT WINAPI(_In_opt_ IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
        _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL*, UINT, UINT, _In_opt_ CONST DXGI_SWAP_CHAIN_DESC*, _COM_Outptr_opt_ IDXGISwapChain** ppSwapChain, _COM_Outptr_opt_ ID3D11Device**,
        _Out_opt_ D3D_FEATURE_LEVEL*, _COM_Outptr_opt_ ID3D11DeviceContext**)>("D3D11CreateDevice");
    F_PRINT;

    std::cout << "D3D11CreateDeviceAndSwapChain with { " <<
        "IDXGIAdapter*: " << "0x" << std::hex << pAdapter << ", " <<
        "D3D_DRIVER_TYPE: " << "0x" << std::hex << DriverType << ", " <<
        "HMODULE: " << "0x" << std::hex << Software << ", " <<
        "Flags: " << "0x" << std::hex << Flags << ", " <<
        "D3D_FEATURE_LEVEL: " << "0x" << std::hex << pFeatureLevels << ", " <<
        "FeatureLevels: " << "0x" << std::hex << FeatureLevels << ", " <<
        "SDKVersion: " << "0x" << std::hex << SDKVersion << ", " <<
        "DXGI_SWAP_CHAIN_DESC*: " << "0x" << std::hex << pSwapChainDesc << ", " <<
        "IDXGISwapChain**: " << "0x" << std::hex << ppSwapChain << ", " <<
        "ID3D11Device**: " << "0x" << std::hex << ppDevice << ", " <<
        "D3D_FEATURE_LEVEL*: " << "0x" << std::hex << pFeatureLevel << ", " <<
        "ID3D11DeviceContext**: " << "0x" << std::hex << ppImmediateContext <<
        " }" << std::endl;

    HRESULT result = ERROR;

    if (FAILED(result = cProc(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext)))
    {
        std::cout << "Failed to call d3d11.dll -> D3D11CreateDevice" << std::endl;
        return result;
    }

    hooker::register_hook<hooks::ClearRenderTargetView>(*ppImmediateContext);
    return 0;
}