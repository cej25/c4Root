#ifndef FIMP_FINE_TIME_BINS_H
#define FIMP_FINE_TIME_BINS_H

// ROOT histogram normal bins are one-based (bin 0 is underflow).
// FIMP's raw fine-time TDC codes are zero-based, matching the histogram
// x-axis [0, max_fine_time_bins). Call for a valid raw code only.
namespace fimp_fine_time_bins
{
inline int RootBinForRawFineTime(int raw_fine_time)
{
    return raw_fine_time + 1;
}
} // namespace fimp_fine_time_bins

#endif
