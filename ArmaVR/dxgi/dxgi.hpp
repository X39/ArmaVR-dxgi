#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

HRESULT WINAPI CreateDXGIFactoryHooked(REFIID riid, void** ppFactory);
HRESULT WINAPI CreateDXGIFactory1Hooked(REFIID riid, void** ppFactory);
HRESULT WINAPI CreateDXGIFactory2Hooked(UINT Flags, REFIID riid, void** ppFactory);

HRESULT WINAPI CreateDXGIFactoryActual(UINT Flags, REFIID riid, void** ppFactory);