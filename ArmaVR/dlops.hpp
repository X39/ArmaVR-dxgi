#pragma once
#include <string>
#include <sstream>
#include <unordered_map>


class dlops
{
private:
    void* handle;
    std::string mpath;
    bool try_resolve_do(std::string name, void** outptr);
    void* resolve_do(std::string name);

    //Prevent copy
    dlops(const dlops&) = delete;
    void operator=(dlops const& x) = delete;
    dlops(std::string path);
    ~dlops()
    {
        close();
    }

    static std::unordered_map<std::string, dlops*> active_libraries;
    void close();
public:
    std::string path() { return mpath; }
    template<typename FUNC> FUNC* resolve(std::string name)
    { return (FUNC*)resolve_do(name); }
    template<typename FUNC> bool try_resolve(std::string name, FUNC** outptr)
    {
        void* tmp;
        if (try_resolve_do(name, &tmp))
        {
            *outptr = (FUNC*)tmp;
            return true;
        }
        return false;
    }


    static dlops& get(std::string str);
    static void close(dlops& dl);
    static void close_all();
};
