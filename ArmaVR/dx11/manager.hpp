#pragma once
#include "../hooker.hpp"

#include <d3d11.h>

#include <functional>

namespace armavr::dx11
{
    class manager : public hooker::hook
    {
    public:
        manager();
        virtual ~manager();
    };
}