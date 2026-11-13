#ifndef STEFAN_INDEX_SAFETY_H
#define STEFAN_INDEX_SAFETY_H

#include <cstddef>

namespace stefan_index_safety
{
inline bool ValidDssd(int dssd, std::size_t count)
{
    return dssd >= 0 && static_cast<std::size_t>(dssd) < count;
}
} // namespace stefan_index_safety

#endif
