#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <type_traits>

class hooker
{
public:
    class hook
    {
        std::string m_name;
    public:
        hook(const char* name) : m_name(name) { }
        hook(std::string name) : m_name(name) { }
        virtual ~hook() { }

        std::string_view name() const { return m_name; }
    };
private:
    std::vector<hook*> m_hooks;
    static hooker* instance;
public:
    // Frees and destroys all hooks created
    static void release();

    template<class T, typename... TArgs>
    static void register_hook(TArgs... args)
    {
        static_assert(std::is_base_of<hook, T>::value, "Hook not deriving from hooker::hook.");
        if (!instance)
        {
            instance = new hooker();
        }
        instance->m_hooks.push_back(new T(std::forward<TArgs>(args)...));
    }
};