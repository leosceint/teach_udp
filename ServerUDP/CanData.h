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
#pragma pack(pop)

std::ostream& operator<< (std::ostream& out, const CanData& data);