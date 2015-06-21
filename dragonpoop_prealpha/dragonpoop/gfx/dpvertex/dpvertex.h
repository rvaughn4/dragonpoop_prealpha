
#ifndef dragonpoop_dpvertex_h
#define dragonpoop_dpvertex_h

#include "../../core/dpid/dpid.h"
#include "dpxyzw.h"
#include <stdint.h>

namespace dragonpoop
{

    struct dptexcoord
    {
        float s, t;
    };

    struct dpvertex_unit
    {
        dpxyzw pos, normal;
        dptexcoord texcoords[ 2 ];
    };

    struct dpvertex
    {
        dpvertex_unit start, end;
        dpid id;
    };

};

#endif