#include "stdafx.h"
#include "DeathGas.hpp"
#include "Function.hpp"
#include "Game.hpp"
#include "Events.hpp"
#include "stdlib.hpp"
#include "Map.hpp"
#include "Abe.hpp"

ALIVE_VAR(1, 0x5BD24C, int, gDeathGasCount_5BD24C, 0);
ALIVE_ARY(1, 0x5BC6C8, Prim_SetTPage, 2, gGasTPages_5BC6C8, {});

struct GasPolys
{
    Poly_G4 polys[2][2][4][4];
};
ALIVE_VAR(1, 0x5BC6E8, GasPolys, stru_5BC6E8, {});

struct RandomData
{
    BYTE data[2][5][5];
};
ALIVE_VAR(1, 0x5BD1E4, RandomData, byte_5BD1E4, {});
ALIVE_VAR(1, 0x5BD218, RandomData, byte_5BD218, {});


DeathGas* DeathGas::ctor_43C030(__int16 layer, __int16 amount)
{
    BaseGameObject_ctor_4DBFA0(TRUE, 0);
    SetVTable(this, 0x5451B4);

    gDeathGasCount_5BD24C++;

    field_4_typeId = Types::eMainMenuTransistion_116; // wot moment
    gObjList_drawables_5C1124->Push_Back(this);
    field_6_flags.Set(BaseGameObject::eDrawable);
    field_26_flag = 0;

    Init_SetTPage_4F5B60(&gGasTPages_5BC6C8[0], 0, 1, PSX_getTPage_4F60E0(2, 1, 0, 0));
    Init_SetTPage_4F5B60(&gGasTPages_5BC6C8[1], 0, 1, PSX_getTPage_4F60E0(2, 1, 0, 0));

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int l = 0; l < 4; l++)
                {
                    Poly_G4* pPoly = &stru_5BC6E8.polys[i][j][k][l];
                    PolyG4_Init_4F88B0(pPoly);
                    Poly_Set_SemiTrans_4F8A60(&pPoly->mBase.header, TRUE);
                }
            }
        }
    }

    field_28_layer = layer;
    field_20_total = 0;
    field_22 = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                byte_5BD1E4.data[i][j][k] = Math_NextRandom();
                byte_5BD218.data[i][j][k] = (Math_NextRandom() & 3) + 2;
            }
        }
    }

    field_24_amount = amount;
    return this;
}

BaseGameObject* DeathGas::VDestructor(signed int flags)
{
    return vdtor_43C240(flags);
}

void DeathGas::VScreenChanged()
{
    vScreenChanged_43CA50();
}

void DeathGas::VUpdate()
{
    vUpdate_43C300();
}

void DeathGas::VRender(int** pOrderingTable)
{
    vRender_43C350(pOrderingTable);
}

DeathGas* DeathGas::vdtor_43C240(signed int flags)
{
    dtor_43C270();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void DeathGas::dtor_43C270()
{
    SetVTable(this, 0x5451B4);
    gObjList_drawables_5C1124->Remove_Item(this);
    gDeathGasCount_5BD24C--;
    BaseGameObject_dtor_4DBEC0();
}

void DeathGas::vScreenChanged_43CA50()
{
    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId ||
        gMap_5C3030.field_22 != gMap_5C3030.Get_Path_Unknown_480710() ||
        sActiveHero_5C1B68 == spAbe_554D5C)
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
}

void DeathGas::vUpdate_43C300()
{
    if (Event_Get_422C00(kEventDeathReset))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    if (!field_26_flag)
    {
        field_20_total += field_24_amount;

        if (field_20_total > 255)
        {
            field_20_total = 255;
        }
    }
}

void DeathGas::vRender_43C350(int** /*pOt*/)
{
    NOT_IMPLEMENTED();
}
