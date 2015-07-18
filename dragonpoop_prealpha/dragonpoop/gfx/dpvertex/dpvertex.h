
#ifndef dragonpoop_dpvertex_h
#define dragonpoop_dpvertex_h

#include "../../core/dpid/dpid.h"
#include "dpxyzw.h"
#include <stdint.h>

namespace dragonpoop
{

#pragma pack( 1 )
    struct dptexcoord
    {
        float s, t;
    };
#pragma pack(  )

#pragma pack( 1 )
    struct dpvertex_unit
    {
        dpxyzw pos, normal;
        dptexcoord texcoords[ 2 ];
    };
#pragma pack(  )

#pragma pack( 1 )
    struct dpvertex
    {
        dpvertex_unit start, end;
    };
#pragma pack(  )

};

#endif