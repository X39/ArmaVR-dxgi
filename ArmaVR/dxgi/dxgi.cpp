#include "dxgi.hpp"
#include "dxgi_abi.hpp"
#include "factory.hpp"
#include "swapchain.hpp"
#include "../hooker.hpp"
#include "../dllmain.hpp"


#include <dxgi.h>
#include <d3d11.h>
#include <dxgi1_3.h>

#include <iostream>
#include <iomanip>

#ifdef _DEBUG
#define F_PRINT std::cout << __FUNCTION__ "\n" << std::endl
#else
#define F_PRINT
#endif

std::ostream& operator<< (std::ostream& stream, const IID iid)
{
    auto casted = reinterpret_cast<const char*>(&iid);
    for (
        size_t i = 0;
        i < sizeof(iid.Data1);
        i++)
    {
        char c = casted[i];
        stream << std::hex << std::setfill('0') << std::setw(2) << +c;
    }
    stream << "-";
    for (
        size_t i = sizeof(iid.Data1);
        i < sizeof(iid.Data1) + sizeof(iid.Data2);
        i++)
    {
        char c = casted[i];
        stream << std::hex << std::setfill('0') << std::setw(2) << +c;
    }
    stream << "-";
    for (
        size_t i = sizeof(iid.Data1) + sizeof(iid.Data2);
        i < sizeof(iid.Data1) + sizeof(iid.Data2) + sizeof(iid.Data3);
        i++)
    {
        char c = casted[i];
        stream << std::hex << std::setfill('0') << std::setw(2) << +c;
    }
    stream << "-";
    for (
        size_t i = sizeof(iid.Data1) + sizeof(iid.Data2) + sizeof(iid.Data3);
        i < sizeof(iid.Data1) + sizeof(iid.Data2) + sizeof(iid.Data3) + sizeof(iid.Data4);
        i++)
    {
        char c = casted[i];
        stream << std::hex << std::setfill('0') << std::setw(2) << +c;
    }
    return stream;
}

namespace hooks
{
    struct CreateSwapChain : public hooker::hook
    {
        void* factory;
        static armavr::dxgi::addresses::IDXGIFactory::CreateSwapChain original;

        CreateSwapChain(void* f) : hooker::hook("CreateSwapChain"), factory(f)
        {
            if (armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(factory) != original)
            {
                std::cout << "Aquiring hook of IDXGIFactory::CreateSwapChain" << std::endl;
                original = armavr::dxgi::addresses::IDXGIFactory::get_CreateSwapChain(factory);
                armavr::dxgi::addresses::IDXGIFactory::set_CreateSwapChain(factory, hooked);
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

        static HRESULT _stdcall hooked(
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

HMODULE libHandledxgi = NULL;

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
    if (libHandledxgi == NULL)
    {
        libHandledxgi = LoadLibraryA("C:/Windows/System32/dxgi.dll");
        LoadLibraryA("Indicium-ImGui.dll");
    }

    if (libHandledxgi == NULL)
    {
        std::cout << "Failed to load dxgi.dll" << std::endl;
        return ERROR_INVALID_LIBRARY;
    }

    CreateDXGIFactory2_t cProc = (CreateDXGIFactory2_t)GetProcAddress(libHandledxgi, "CreateDXGIFactory2");

    std::cout << "CreateDXGIFactory with { " <<
        "Flags: " << "0x" << std::hex << Flags << ", " <<
        "Addr: " << "0x" << std::hex << ppFactory << "," <<
        "IID: " << riid << "," <<
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