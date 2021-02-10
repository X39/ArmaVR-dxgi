#pragma once

#include <iostream>
#include <iomanip>

#ifdef _DEBUG
#define F_PRINT std::cout << __FUNCTION__ "\n" << std::endl
#else
#define F_PRINT
#endif

inline std::ostream& operator<< (std::ostream& stream, const IID iid)
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