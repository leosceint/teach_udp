#include <ostream>

#pragma pack(push, 1)
struct CanData
{
    unsigned int type;
    double pos0;
    double pos1;
    double pos2;
    unsigned short time;
};

struct CanFrame
{
    unsigned int number;
    CanData packet_1;
    CanData packet_2;
    CanData packet_3;
    CanData packet_4;
};

#pragma pack(pop)

std::ostream& operator<< (std::ostream& out, const CanData& data);

std::ostream& operator<< (std::ostream& out, const CanFrame& frame);