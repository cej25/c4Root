#include "LisaCalData.h"

LisaCalData::LisaCalData()
{

}

LisaCalItem::LisaCalItem()
{

}

void LisaCalItem::SetAll(uint64_t wr,
                        int layer,
                        std::string c,
                        int xpos,
                        int ypos,
                        int e,
                        std::vector<uint16_t> tr)
{   
    wr_t = wr;
    layer_id = layer;
    city = c;
    xposition = xpos;
    yposition = ypos;
    energy = e;
    trace = tr;
}

void LisaCalItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    layer_id = 0;
    city = "";
    xposition = 0;
    yposition = 0;
    energy = 0;
    trace = {};
}

ClassImp(LisaCalData)