#include "CanData.h"

std::ostream& operator<< (std::ostream& out, const CanData& data)
{
    out << std::hex << data.type << " : " << std::dec << data.pos0 << " : " << data.pos1 
        << data.pos2 << " : " << data.time << std::endl;
    
    return out;
}