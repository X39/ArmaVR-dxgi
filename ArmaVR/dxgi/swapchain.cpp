#include "swapchain.hpp"
#include "../util.hpp"
#include "../hooker.hpp"
#include "abi.hpp"



#include <d3d11.h>
#include <d3d11_1.h>
#include <iostream>

#include <array>
#include <csetjmp>


// SaveTextureToBmp
#include <initguid.h>
#include <windows.h>
#include <d3d11_3.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <wincodec.h>   // WIC
#include <windows.foundation.h>
#include <windows.applicationmodel.h>
#include <windows.ui.xaml.h>
#include <windows.ui.xaml.markup.h>
#include <wrl.h>
#include <numeric>
#define LAZYERROR(RES,TXT,...) std::cout << (TXT) << std::hex << RES << std::endl; return;
void SaveTextureToBmp(PCWSTR FileName, ID3D11Texture2D* Texture)
{
    using namespace Microsoft::WRL;
    HRESULT hr;

    // First verify that we can map the texture
    D3D11_TEXTURE2D_DESC desc;
    Texture->GetDesc(&desc);

    // translate texture format to WIC format. We support only BGRA and ARGB.
    GUID wicFormatGuid;
    switch (desc.Format)
    {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        wicFormatGuid = GUID_WICPixelFormat32bppRGBA;
        break;
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        wicFormatGuid = GUID_WICPixelFormat32bppBGRA;
        break;
        default:
        LAZYERROR(
            HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED),
            L"Unsupported DXGI_FORMAT: %d. Only RGBA and BGRA are supported.",
            desc.Format);
    }

    // Get the device context
    ComPtr<ID3D11Device> d3dDevice;
    Texture->GetDevice(&d3dDevice);
    ComPtr<ID3D11DeviceContext> d3dContext;
    d3dDevice->GetImmediateContext(&d3dContext);

    // map the texture
    ComPtr<ID3D11Texture2D> mappedTexture;
    D3D11_MAPPED_SUBRESOURCE mapInfo;
    mapInfo.RowPitch;
    hr = d3dContext->Map(
        Texture,
        0,  // Subresource
        D3D11_MAP_READ,
        0,  // MapFlags
        &mapInfo);

    if (FAILED(hr))
    {
        // If we failed to map the texture, copy it to a staging resource
        if (hr == E_INVALIDARG)
        {
            D3D11_TEXTURE2D_DESC desc2;
            desc2.Width = desc.Width;
            desc2.Height = desc.Height;
            desc2.MipLevels = desc.MipLevels;
            desc2.ArraySize = desc.ArraySize;
            desc2.Format = desc.Format;
            desc2.SampleDesc = desc.SampleDesc;
            desc2.Usage = D3D11_USAGE_STAGING;
            desc2.BindFlags = 0;
            desc2.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            desc2.MiscFlags = 0;

            ComPtr<ID3D11Texture2D> stagingTexture;
            hr = d3dDevice->CreateTexture2D(&desc2, nullptr, &stagingTexture);
            if (FAILED(hr))
            {
                LAZYERROR(hr, L"Failed to create staging texture");
            }

            // copy the texture to a staging resource
            d3dContext->CopyResource(stagingTexture.Get(), Texture);

            // now, map the staging resource
            hr = d3dContext->Map(
                stagingTexture.Get(),
                0,
                D3D11_MAP_READ,
                0,
                &mapInfo);
            if (FAILED(hr))
            {
                LAZYERROR(hr, L"Failed to map staging texture");
            }

            mappedTexture = std::move(stagingTexture);
        }
        else
        {
            LAZYERROR(hr, L"Failed to map texture.");
        }
    }
    else
    {
        mappedTexture = Texture;
    }
    d3dContext->Unmap(mappedTexture.Get(), 0);

    ComPtr<IWICImagingFactory> wicFactory;
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(wicFactory),
        reinterpret_cast<void**>(wicFactory.GetAddressOf()));
    if (FAILED(hr))
    {
        LAZYERROR(
            hr,
            L"Failed to create instance of WICImagingFactory");
    }

    ComPtr<IWICBitmapEncoder> wicEncoder;
    hr = wicFactory->CreateEncoder(
        GUID_ContainerFormatBmp,
        nullptr,
        &wicEncoder);
    if (FAILED(hr))
    {
        LAZYERROR(hr, L"Failed to create BMP encoder");
    }

    ComPtr<IWICStream> wicStream;
    hr = wicFactory->CreateStream(&wicStream);
    if (FAILED(hr))
    {
        LAZYERROR(hr, L"Failed to create IWICStream");
    }

    hr = wicStream->InitializeFromFilename(FileName, GENERIC_WRITE);
    if (FAILED(hr))
    {
        LAZYERROR(hr, L"Failed to initialize stream from file name");
    }

    hr = wicEncoder->Initialize(wicStream.Get(), WICBitmapEncoderNoCache);
    if (FAILED(hr))
    {
        LAZYERROR(hr, L"Failed to initialize bitmap encoder");
    }

    // Encode and commit the frame
    {
        ComPtr<IWICBitmapFrameEncode> frameEncode;
        wicEncoder->CreateNewFrame(&frameEncode, nullptr);
        if (FAILED(hr))
        {
            LAZYERROR(hr, L"Failed to create IWICBitmapFrameEncode");
        }

        hr = frameEncode->Initialize(nullptr);
        if (FAILED(hr))
        {
            LAZYERROR(hr, L"Failed to initialize IWICBitmapFrameEncode");
        }


        hr = frameEncode->SetPixelFormat(&wicFormatGuid);
        if (FAILED(hr))
        {
            LAZYERROR(
                hr,
                L"SetPixelFormat(%s) failed.",
                StringFromWicFormat(wicFormatGuid));
        }

        hr = frameEncode->SetSize(desc.Width, desc.Height);
        if (FAILED(hr))
        {
            LAZYERROR(hr, L"SetSize(...) failed.");
        }

        hr = frameEncode->WritePixels(
            desc.Height,
            mapInfo.RowPitch,
            desc.Height * mapInfo.RowPitch,
            reinterpret_cast<BYTE*>(mapInfo.pData));
        if (FAILED(hr))
        {
            LAZYERROR(hr, L"frameEncode->WritePixels(...) failed.");
        }

        hr = frameEncode->Commit();
        if (FAILED(hr))
        {
            LAZYERROR(hr, L"Failed to commit frameEncode");
        }
    }

    hr = wicEncoder->Commit();
    if (FAILED(hr))
    {
        LAZYERROR(hr, L"Failed to commit encoder");
    }
}





namespace hooks
{
    struct VRRenderTargets : public hooker::hook
    {
        ID3D11Device* device;
        static void** capture_resource; // resource to capture
        static armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView original;
        static ID3D11Texture2D* left_eye_texture;
        static ID3D11RenderTargetView* left_eye_render_target_view;
        static ID3D11Texture2D* right_eye_texture;
        static ID3D11RenderTargetView* right_eye_render_target_view;

        VRRenderTargets(ID3D11Device* dc) : hooker::hook("VRRenderTargets"), device(dc)
        {
            if (armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device) != original)
            {
                std::cout << "Aquiring hook of ID3D11Device::CreateRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device);
                armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(device, callback);
            }
        }
        virtual ~VRRenderTargets()
        {
            if (armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device) != original)
            {
                std::cout << "Releasing hook of ID3D11Device::CreateRenderTargetView" << std::endl;
                armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(device, original);
            }
            device->Release();
        }

        static void create_left_eye_render_target(::ID3D11Device* This)
        {
            HRESULT result = {};
            D3D11_TEXTURE2D_DESC left_eye_texture2d_desc = {};
            left_eye_texture2d_desc.Width = 1920;
            left_eye_texture2d_desc.Height = 1080;
            left_eye_texture2d_desc.MipLevels = 1;
            left_eye_texture2d_desc.ArraySize = 1;
            left_eye_texture2d_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            left_eye_texture2d_desc.SampleDesc.Count = 1;
            left_eye_texture2d_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            left_eye_texture2d_desc.BindFlags = D3D10_BIND_RENDER_TARGET;
            left_eye_texture2d_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
            left_eye_texture2d_desc.MiscFlags = 0;

            // Create our own render target for left and right eye
            if (FAILED(result = This->CreateTexture2D(&left_eye_texture2d_desc, NULL, &left_eye_texture)))
            {
                std::cout << "Failed to create Texture2D for left-eye (0x" << std::hex << result << ")" << std::endl;
                return;
            }

            D3D11_RENDER_TARGET_VIEW_DESC left_eye_render_target_view_desc = {};
            left_eye_render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;
            left_eye_render_target_view_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
            left_eye_render_target_view_desc.Texture2D.MipSlice = 0;

            if (FAILED(result = original(This, left_eye_texture, &left_eye_render_target_view_desc, &left_eye_render_target_view)))
            {
                std::cout << "Failed to create RenderTargetView for left-eye (0x" << std::hex << result << ")" << std::endl;
            }
        }
        static void create_right_eye_render_target(::ID3D11Device* This)
        {
            HRESULT result = {};
            D3D11_TEXTURE2D_DESC right_eye_texture2d_desc = {};
            right_eye_texture2d_desc.Width = 1920;
            right_eye_texture2d_desc.Height = 1080;
            right_eye_texture2d_desc.MipLevels = 1;
            right_eye_texture2d_desc.ArraySize = 1;
            right_eye_texture2d_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            right_eye_texture2d_desc.SampleDesc.Count = 1;
            right_eye_texture2d_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
            right_eye_texture2d_desc.BindFlags = D3D10_BIND_RENDER_TARGET;
            right_eye_texture2d_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
            right_eye_texture2d_desc.MiscFlags = 0;

            // Create our own render target for right and right eye
            if (FAILED(result = This->CreateTexture2D(&right_eye_texture2d_desc, NULL, &right_eye_texture)))
            {
                std::cout << "Failed to create Texture2D for right-eye (0x" << std::hex << result << ")" << std::endl;
                return;
            }

            D3D11_RENDER_TARGET_VIEW_DESC right_eye_render_target_view_desc = {};
            right_eye_render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;
            right_eye_render_target_view_desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
            right_eye_render_target_view_desc.Texture2D.MipSlice = 0;

            if (FAILED(result = original(This, right_eye_texture, &right_eye_render_target_view_desc, &right_eye_render_target_view)))
            {
                std::cout << "Failed to create RenderTargetView for right-eye (0x" << std::hex << result << ")" << std::endl;
            }
        }
        static HRESULT STDMETHODCALLTYPE callback(
            ::ID3D11Device* This,
            ID3D11Resource* pResource,
            const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
            ID3D11RenderTargetView** ppRTView
        )
        {
            if (!left_eye_texture) { create_left_eye_render_target(This); }
            if (!right_eye_texture) { create_right_eye_render_target(This); }

            // Pass creation to original
            auto result = original(This, pResource, pDesc, ppRTView);

            return result;
        }
    };
    armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView VRRenderTargets::original = 0;
    ID3D11Texture2D* VRRenderTargets::left_eye_texture = {};
    ID3D11RenderTargetView* VRRenderTargets::left_eye_render_target_view = {};
    ID3D11Texture2D* VRRenderTargets::right_eye_texture = {};
    ID3D11RenderTargetView* VRRenderTargets::right_eye_render_target_view = {};


    struct ClearRenderTargetView : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::ClearRenderTargetView original;

        ClearRenderTargetView(ID3D11DeviceContext1* dc) : hooker::hook("ClearRenderTargetView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(deviceContext, callback);
            }
        }
        ClearRenderTargetView(ID3D11DeviceContext* dc) : hooker::hook("ClearRenderTargetView"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(deviceContext, callback);
            }
        }
        virtual ~ClearRenderTargetView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearRenderTargetView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::ClearRenderTargetView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearRenderTargetView(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
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
    armavr::dxgi::addresses::ID3D11DeviceContext1::ClearRenderTargetView ClearRenderTargetView::original = 0;


    struct ClearDepthStencilView : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::ClearDepthStencilView original;

        ClearDepthStencilView(ID3D11DeviceContext1* dc) : hooker::hook("ClearDepthStencilView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearDepthStencilView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(deviceContext, callback);
            }
        }
        ClearDepthStencilView(ID3D11DeviceContext* dc) : hooker::hook("ClearDepthStencilView"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearDepthStencilView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(deviceContext, callback);
            }
        }
        virtual ~ClearDepthStencilView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearDepthStencilView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::ClearDepthStencilView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearDepthStencilView(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11DepthStencilView* pDepthStencilView,
            /* [annotation] */
            _In_  UINT ClearFlags,
            /* [annotation] */
            _In_  FLOAT Depth,
            /* [annotation] */
            _In_  UINT8 Stencil)
        {
            F_PRINT;

            original(This, pDepthStencilView, ClearFlags, Depth, Stencil);
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::ClearDepthStencilView ClearDepthStencilView::original = 0;

    struct ClearView : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::ClearView original;

        ClearView(ID3D11DeviceContext1* dc) : hooker::hook("ClearView"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(deviceContext, callback);
            }
        }
        ClearView(ID3D11DeviceContext* dc) : hooker::hook("ClearView"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(deviceContext, callback);
            }
        }
        virtual ~ClearView()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_ClearView(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::ClearView" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_ClearView(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ::ID3D11DeviceContext1* This,
            /* [annotation] */
            _In_  ID3D11View* pView,
            /* [annotation] */
            _In_  const FLOAT* Color,
            /* [annotation] */
            const RECT* pRect,
            UINT NumRects)
        {
            F_PRINT;

            original(This, pView, Color, pRect, NumRects);
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::ClearView ClearView::original = 0;

    struct OMSetRenderTargets : public hooker::hook
    {
        ID3D11DeviceContext1* deviceContext;
        static void* render_target;
        static armavr::dxgi::addresses::ID3D11DeviceContext1::OMSetRenderTargets original;
        static int render_state;

        static constexpr int LEFT_EYE = 0;
        static constexpr int RIGHT_EYE = 1;
        static constexpr int ORIGINAL = 2;
        static bool enabled = false;

        OMSetRenderTargets(ID3D11DeviceContext1* dc) : hooker::hook("OMSetRenderTargets"), deviceContext(dc)
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::ClearView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(deviceContext, callback);
            }
        }
        OMSetRenderTargets(ID3D11DeviceContext* dc) : hooker::hook("OMSetRenderTargets"), deviceContext(nullptr)
        {
            dc->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)(&deviceContext));
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext) != original)
            {
                std::cout << "Aquiring hook of ID3D11DeviceContext1::OMSetRenderTargets" << std::endl;
                original = armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext);
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(deviceContext, callback);
            }
        }
        virtual ~OMSetRenderTargets()
        {
            if (armavr::dxgi::addresses::ID3D11DeviceContext1::get_OMSetRenderTargets(deviceContext) != original)
            {
                std::cout << "Releasing hook of ID3D11DeviceContext1::OMSetRenderTargets" << std::endl;
                armavr::dxgi::addresses::ID3D11DeviceContext1::set_OMSetRenderTargets(deviceContext, original);
            }
            deviceContext->Release();
        }
        static void STDMETHODCALLTYPE callback(
            ::ID3D11DeviceContext1* This,
            UINT                   NumViews,
            ID3D11RenderTargetView * const *ppRenderTargetViews,
            ID3D11DepthStencilView *pDepthStencilView)
        {
            auto hasOriginalRenderTarget = false;
            for (UINT i = 0; i < NumViews; ++i)
            {
                if (ppRenderTargetViews[i] == render_target)
                {
                    hasOriginalRenderTarget = true;
                }
            }
            if (hasOriginalRenderTarget || !enabled)
            {
                switch (render_state)
                {
                    case ORIGINAL:
                    original(This, NumViews, ppRenderTargetViews, pDepthStencilView);
                    render_state = LEFT_EYE;
                    break;
                    case RIGHT_EYE:
                    original(This, 1, &VRRenderTargets::right_eye_render_target_view, pDepthStencilView);
                    render_state = ORIGINAL;
                    break;
                    case LEFT_EYE:
                    default:
                    original(This, 1, &VRRenderTargets::left_eye_render_target_view, pDepthStencilView);
                    render_state = RIGHT_EYE;
                    break;
                }
            }
            else
            {
                original(This, NumViews, ppRenderTargetViews, pDepthStencilView);
            }
        }
    };
    armavr::dxgi::addresses::ID3D11DeviceContext1::OMSetRenderTargets OMSetRenderTargets::original = 0;
    void* OMSetRenderTargets::render_target = nullptr;
    int OMSetRenderTargets::render_state = OMSetRenderTargets::LEFT_EYE;
    bool OMSetRenderTargets::enabled = false;


    struct CreateRenderTargetView : public hooker::hook
    {
        ID3D11Device* device;
        static void** capture_resource; // resource to capture
        static armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView original;

        CreateRenderTargetView(ID3D11Device* dc) : hooker::hook("CreateRenderTargetView"), device(dc)
        {
            if (armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device) != original)
            {
                std::cout << "Aquiring hook of ID3D11Device::CreateRenderTargetView" << std::endl;
                original = armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device);
                armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(device, callback);
            }
        }
        virtual ~CreateRenderTargetView()
        {
            if (armavr::dxgi::addresses::ID3D11Device::get_CreateRenderTargetView(device) != original)
            {
                std::cout << "Releasing hook of ID3D11Device::CreateRenderTargetView" << std::endl;
                armavr::dxgi::addresses::ID3D11Device::set_CreateRenderTargetView(device, original);
            }
            device->Release();
        }
        static HRESULT STDMETHODCALLTYPE callback(
            ::ID3D11Device                      *This,
            ID3D11Resource                      *pResource,
            const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
            ID3D11RenderTargetView              **ppRTView
        )
        {
            auto result = original(This, pResource, pDesc, ppRTView);
            if (pResource == *capture_resource)
            {
                F_PRINT;
                std::cout << (void*)*ppRTView << std::endl;
                OMSetRenderTargets::render_target = *ppRTView;
            }

            return result;
        }
    };
    armavr::dxgi::addresses::ID3D11Device::CreateRenderTargetView CreateRenderTargetView::original = 0;
    void** CreateRenderTargetView::capture_resource = nullptr;
}


DXGISwapChainLayer::DXGISwapChainLayer(IDXGISwapChain* swp)
    : m_swapchain(swp)
    , m_device(nullptr)
    , m_device_context(nullptr)
    , m_swapchain_back_buffer(nullptr)
{
    IDXGIDevice1* dev;
    GetDevice(__uuidof(IDXGIDevice1), (void**)(&dev));
    dev->SetMaximumFrameLatency(1);
    dev->Release();

    swp->GetDevice(__uuidof(ID3D11Device), (void**)&m_device);
    m_device->GetImmediateContext(&m_device_context);

    hooks::CreateRenderTargetView::capture_resource = &m_swapchain_back_buffer;
    hooker::register_hook<hooks::CreateRenderTargetView>(m_device);
    hooker::register_hook<hooks::VRRenderTargets>(m_device);

    hooker::register_hook<hooks::ClearRenderTargetView>(m_device_context);
    hooker::register_hook<hooks::ClearDepthStencilView>(m_device_context);
    hooker::register_hook<hooks::ClearView>(m_device_context);
    hooker::register_hook<hooks::OMSetRenderTargets>(m_device_context);
}

HRESULT __stdcall DXGISwapChainLayer::QueryInterface(REFIID riid, void** ppvObject)
{
    F_PRINT;
    return m_swapchain->QueryInterface(riid, ppvObject);
}

ULONG __stdcall DXGISwapChainLayer::AddRef(void)
{
    F_PRINT;
    return m_swapchain->AddRef();
}

ULONG __stdcall DXGISwapChainLayer::Release(void)
{
    F_PRINT;
    m_device->Release();
    auto r = m_swapchain->Release();
    if (r == 0)
        delete this;
    return r;
}

HRESULT __stdcall DXGISwapChainLayer::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData)
{
    F_PRINT;
    return m_swapchain->SetPrivateData(Name, DataSize, pData);
}

HRESULT __stdcall DXGISwapChainLayer::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown)
{
    F_PRINT;
    return m_swapchain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT __stdcall DXGISwapChainLayer::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData)
{
    F_PRINT;
    return m_swapchain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT __stdcall DXGISwapChainLayer::GetParent(REFIID riid, void** ppParent)
{
    F_PRINT;
    return m_swapchain->GetParent(riid, ppParent);
}

HRESULT __stdcall DXGISwapChainLayer::GetDevice(REFIID riid, void** ppDevice)
{
    F_PRINT;
    return m_swapchain->GetDevice(riid, ppDevice);
}

HRESULT __stdcall DXGISwapChainLayer::Present(UINT SyncInterval, UINT Flags)
{
    F_PRINT;
    return m_swapchain->Present(0, Flags);
}

HRESULT __stdcall DXGISwapChainLayer::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface)
{
    F_PRINT;
    auto result = m_swapchain->GetBuffer(Buffer, riid, ppSurface);
    if (m_swapchain_back_buffer == nullptr)
    {
        m_swapchain_back_buffer = *ppSurface;
    }
    return result;
}

HRESULT __stdcall DXGISwapChainLayer::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget)
{
    F_PRINT;
    return m_swapchain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT __stdcall DXGISwapChainLayer::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget)
{
    //F_PRINT;
    auto r = m_swapchain->GetFullscreenState(pFullscreen, ppTarget);
    return r;
}

HRESULT __stdcall DXGISwapChainLayer::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc)
{
    //F_PRINT;
    auto r = m_swapchain->GetDesc(pDesc);
    pDesc->SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    pDesc->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    return r;

}

HRESULT __stdcall DXGISwapChainLayer::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    F_PRINT;
    return m_swapchain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT __stdcall DXGISwapChainLayer::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters)
{
    F_PRINT;
    return m_swapchain->ResizeTarget(pNewTargetParameters);
}

HRESULT __stdcall DXGISwapChainLayer::GetContainingOutput(IDXGIOutput** ppOutput)
{
    F_PRINT;
    return m_swapchain->GetContainingOutput(ppOutput);
}

HRESULT __stdcall DXGISwapChainLayer::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats)
{
    F_PRINT;
    return m_swapchain->GetFrameStatistics(pStats);
}

HRESULT __stdcall DXGISwapChainLayer::GetLastPresentCount(UINT* pLastPresentCount)
{
    F_PRINT;
    return m_swapchain->GetLastPresentCount(pLastPresentCount);
}
