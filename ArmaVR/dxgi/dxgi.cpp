#include "dxgi.hpp"
#include "abi.hpp"
#include "factory.hpp"
#include "swapchain.hpp"
#include "../hooker.hpp"
#include "../dllmain.hpp"
#include "../util.hpp"
#include "../dlops.hpp"


#include <dxgi.h>
#include <d3d11.h>
#include <dxgi1_3.h>

#include <iostream>
#include <iomanip>


namespace hooks
{
    struct CreateSwapChain : public hooker::hook
    {
        IDXGIFactory* factory;
        static armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain original;

        CreateSwapChain(IDXGIFactory* f) : hooker::hook("CreateSwapChain"), factory(f)
        {
            if (armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(factory) != original)
            {
                std::cout << "Aquiring hook of IDXGIFactory::CreateSwapChain" << std::endl;
                original = armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(factory);
                armavr::dxgi::addresses::IDXGIFactory::set_CreateSwapChain(factory, callback);
            }
        }
        virtual ~CreateSwapChain()
        {
            if (armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(factory) != original)
            {
                std::cout << "Releasing hook of IDXGIFactory::CreateSwapChain" << std::endl;
                armavr::dxgi::addresses::IDXGIFactory::set_CreateSwapChain(factory, original);
            }
        }

        static HRESULT _stdcall callback(
            IDXGIFactory* This,
            IUnknown* pDevice,
            DXGI_SWAP_CHAIN_DESC* pDesc,
            IDXGISwapChain** ppSwapChain)
        {
            F_PRINT;

            auto r = original(This, pDevice, pDesc, ppSwapChain);

            *ppSwapChain = new DXGISwapChainLayer(*ppSwapChain);

            return r;
        }
    };
    armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain CreateSwapChain::original = 0;
}







struct IUnknown;

typedef HRESULT(WINAPI* CreateDXGIFactory2_t) (UINT, REFIID, void**);

HRESULT WINAPI CreateDXGIFactoryHooked(REFIID riid, void** ppFactory)
{
    F_PRINT;
    HRESULT r = CreateDXGIFactoryActual(0U, riid, ppFactory);
    return r;
}
HRESULT WINAPI CreateDXGIFactory1Hooked(REFIID riid, void** ppFactory)
{
    F_PRINT;
    HRESULT r = CreateDXGIFactoryActual(0U, riid, ppFactory);
    return r;
}

HRESULT WINAPI CreateDXGIFactory2Hooked(UINT Flags, REFIID riid, void** ppFactory)
{
    F_PRINT;
    HRESULT r = CreateDXGIFactoryActual(Flags, riid, ppFactory);
    return r;
}

HRESULT WINAPI CreateDXGIFactoryActual(UINT Flags, REFIID riid, void** ppFactory)
{
    auto& dl = dlops::get("C:/Windows/System32/dxgi.dll");
    auto cProc = dl.resolve<HRESULT WINAPI (UINT, REFIID, void**)>("CreateDXGIFactory2");

    std::cout << "CreateDXGIFactory with { " <<
        "Flags: " << "0x" << std::hex << Flags << ", " <<
        "Addr: " << "0x" << std::hex << ppFactory << ", " <<
        "IID: " << riid << 
        " }" << std::endl;

    HRESULT result = ERROR;
    if (__uuidof(IDXGIFactory) == riid)
    {
        IDXGIFactory* factory;

        if (FAILED(result = cProc(Flags, __uuidof(IDXGIFactory), (void**)(&factory))))
        {
            std::cout << "Failed to call dxgi.dll -> CreateDXGIFactory2" << std::endl;
            return result;
        }

        hooker::register_hook<hooks::CreateSwapChain>(factory);

        *ppFactory = factory;
        return 0;
    }
    else
    {
        std::cout << "Unknown UUID" << riid;
        return ERROR_UNKNOWN_COMPONENT;
    }
}