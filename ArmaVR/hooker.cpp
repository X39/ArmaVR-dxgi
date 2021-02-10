#include "hooker.hpp"

#include <iostream>

hooker* hooker::instance = 0;
void hooker::release()
{
    if (instance)
    {
        std::cout << "Removing hooks:" << std::endl;
        for (auto it = instance->m_hooks.rbegin(); it != instance->m_hooks.rend(); it++)
        {
            std::cout << "    - " << (*it)->name() << std::endl;
            delete (*it);
        }
        delete instance;
        instance = nullptr;
    }
}