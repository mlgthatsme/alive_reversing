#include "stdafx_ao.h"
#include "Function.hpp"
#include "ScopedSeq.hpp"
#include "Midi.hpp"
#include "stdlib.hpp"
#include "Midi.hpp"

START_NS_AO

ScopedSeq* ScopedSeq::ctor_476400(char ambianceId, __int16 direction)
{
    SetVTable(this, 0x4BCD44);

    short volLeft = 0;
    short volRight = 0;

    if (direction == 3)
    {
        volLeft = 1;
        volRight = 0;
    }
    else
    {
        volLeft = direction != 4 ? 1 : 0;
        volRight = 1;
    }

    field_4_seq_id = -1;
    field_8_channel_mask = 0;

    switch (ambianceId)
    {
    case 0:
        field_4_seq_id = 27;
        SND_SEQ_Play_477760(27u, 0, 40 * volLeft + 15, 40 * volRight + 15);
        break;

    case 1:
        field_4_seq_id = 26;
        SND_SEQ_Play_477760(26u, 0, 40 * volLeft + 15, 40 * volRight + 15);
        break;

    case 2:
        field_4_seq_id = 28;
        SND_SEQ_Play_477760(28u, 0, 50 * volLeft + 15, 50 * volRight + 15);
        break;

    case 3:
        field_4_seq_id = 29;
        SND_SEQ_Play_477760(29u, 0, 35 * volLeft + 15, 35 * volRight + 15);
        break;

    case 4:
        field_4_seq_id = 30;
        SND_SEQ_Play_477760(30u, 0, 25 * volLeft + 10, 25 * volRight + 10);
        break;

    case 6:
        field_4_seq_id = 31;
        SND_SEQ_Play_477760(31u, 0, 35 * volLeft + 15, 35 * volRight + 15);
        break;

    default:
        break;
    }
    return this;
}

ScopedSeq* ScopedSeq::VDtor(int flags)
{
    SetVTable(this, 0x4BCD44);

    if (field_4_seq_id >= 0)
    {
        SND_Seq_Stop_477A60(field_4_seq_id);
    }

    if (field_8_channel_mask)
    {
        SND_Stop_Channels_Mask_4774A0(field_8_channel_mask);
    }

    if (flags & 1)
    {
        ao_delete_free_447540(this);
    }

    return this;
}

END_NS_AO
