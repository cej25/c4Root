#ifndef BB7_FEBEX_INDEX_SAFETY_H
#define BB7_FEBEX_INDEX_SAFETY_H

#include <cstddef>

namespace bb7_febex_index_safety
{
inline bool ValidDssd(int dssd, std::size_t dssd_count)
{
    return dssd >= 0 && static_cast<std::size_t>(dssd) < dssd_count;
}

// BB7 uses two 32-strip sides for each DSSD.
// The index is assigned only for valid detector coordinates.
inline bool TryChannelIndex(int dssd, int side, int strip,
                            std::size_t dssd_count, std::size_t& index)
{
    if (!ValidDssd(dssd, dssd_count) ||
        (side != 0 && side != 1) ||
        strip < 0 || strip >= 32)
    {
        return false;
    }

    index = static_cast<std::size_t>(dssd) * 64 +
            static_cast<std::size_t>(side) * 32 +
            static_cast<std::size_t>(strip);
    return true;
}
} // namespace bb7_febex_index_safety

#endif
