#include "ChangePointType.h"

void fromTempToPerm(pointType * pType)
{
    switch (*pType)
    {
    case TEMPORARY_FREE:
        *pType = FREE;
        break;
    case TEMPORARY_RELATIVE:
        *pType = RELATIVE;
        break;
    case TEMPORARY_LOCKED_CROSSPOINT:
        *pType = LOCKED_CROSSPOINT;
        break;
    case TEMPORARY_LOCKED_ALTITUDE_FOOT:
        *pType = LOCKED_ALTITUDE_FOOT;
        break;
    case TEMPORARY_LOCKED_MIDPOINT:
        *pType = LOCKED_MIDPOINT;
        break;
    case TEMPORARY_LOCKED_PERPENDICULAR_BISECTOR:
        *pType = LOCKED_PERPENDICULAR_BISECTOR;
        break;
    case TEMPORARY_LOCKED_ANGLE_BISECTOR:
        *pType = LOCKED_ANGLE_BISECTOR;
        break;
    case TEMPORARY_LOCKED_OUTSIDE_ANGLE_BISECTOR:
        *pType = LOCKED_OUTSIDE_ANGLE_BISECTOR;
        break;
    default:
        break;
    }

}

void fromPermToTemp(pointType * pType)
{
    switch (*pType)
    {
    case FREE:
        *pType = TEMPORARY_FREE;
        break;
    case RELATIVE:
        *pType = TEMPORARY_RELATIVE;
        break;
    case LOCKED_CROSSPOINT:
        *pType = TEMPORARY_LOCKED_CROSSPOINT;
        break;
    case LOCKED_ALTITUDE_FOOT:
        *pType = TEMPORARY_LOCKED_ALTITUDE_FOOT;
        break;
    case LOCKED_MIDPOINT:
        *pType = TEMPORARY_LOCKED_MIDPOINT;
        break;
    case LOCKED_PERPENDICULAR_BISECTOR:
        *pType = TEMPORARY_LOCKED_PERPENDICULAR_BISECTOR;
        break;
    case LOCKED_ANGLE_BISECTOR:
        *pType = TEMPORARY_LOCKED_ANGLE_BISECTOR;
        break;
    case LOCKED_OUTSIDE_ANGLE_BISECTOR:
        *pType = TEMPORARY_LOCKED_OUTSIDE_ANGLE_BISECTOR;
        break;
    default:
        break;
    }

}
