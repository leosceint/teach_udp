#include "CanData.h"

#include <iomanip>

std::ostream& operator<< (std::ostream& out, const CanData& data)
{
    out << std::hex << data.type << " : " 
        << std::dec 
        << std::setprecision(8) << data.pos0 << " : " 
        << std::setprecision(8) << data.pos1 << " : "
        << std::setprecision(8) << data.pos2 << " : " 
        << data.time;
    
    return out;
}

std::ostream& operator<< (std::ostream& out, const CanFrame& frame)
{
    out << frame.packet_1 << std::endl;
    out << frame.packet_2 << std::endl;
    out << frame.packet_3 << std::endl;
    out << frame.packet_4 << std::endl;
    return out;
}