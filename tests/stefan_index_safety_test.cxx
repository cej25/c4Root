#include "../c4source/stefan/StefanIndexSafety.h"

#include <cassert>

int main()
{
    using stefan_index_safety::ValidDssd;

    assert(ValidDssd(0, 1));
    assert(ValidDssd(0, 3));
    assert(ValidDssd(2, 3));

    assert(!ValidDssd(-1, 3));
    assert(!ValidDssd(-2, 3));
    assert(!ValidDssd(3, 3));
    assert(!ValidDssd(4, 3));
    assert(!ValidDssd(0, 0));
    return 0;
}
