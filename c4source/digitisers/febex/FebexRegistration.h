#ifndef FEBEX_REGISTRATION_H
#define FEBEX_REGISTRATION_H

#include "ext_h101_febex.h"

extern "C"
{
#include "ext_data_client.h"
}

#include <cstddef>
#include <string>

namespace febex
{
struct BankRegistration
{
    ext_data_structure_info* info;
    const std::string& prefix;

    std::string Name(const char* field) const
    {
        return *field ? prefix + (field + sizeof("FEBEX") - 1) : "";
    }
};

// The generated ITEMS_INFO supplies offsets, dimensions and count-field names.
// These overloads are found by argument-dependent lookup and prefix the names
// before forwarding to ext-data. Extra API arguments such as flags pass through.
template <typename... Args>
int ext_data_struct_info_item(BankRegistration bank, std::size_t offset, std::size_t size,
                              int type, const char* parent, int index,
                              const char* field, const char* control, Args... args)
{
    return ::ext_data_struct_info_item(bank.info, offset, size, type, parent, index,
                                      bank.Name(field).c_str(), bank.Name(control).c_str(), args...);
}

template <typename... Args>
int ext_data_struct_info_item_stderr(BankRegistration bank, std::size_t offset, std::size_t size,
                                     int type, const char* parent, int index,
                                     const char* field, const char* control, Args... args)
{
    return ::ext_data_struct_info_item_stderr(bank.info, offset, size, type, parent, index,
                                             bank.Name(field).c_str(), bank.Name(control).c_str(), args...);
}

inline bool RegisterBank(ext_data_structure_info* info, std::size_t offset, const std::string& prefix)
{
    const BankRegistration bank{info, prefix};
    int ok = 0;
    EXT_STR_h101_febex_ITEMS_INFO(ok, bank, offset, EXT_STR_h101_febex, 0);
    return ok != 0;
}
}

#endif
