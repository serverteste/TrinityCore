/*
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "AuthenticationPackets.h"

WorldPackets::AuthPackets::AuthResponse::AuthResponse() : ServerPacket(SMSG_AUTH_RESPONSE, 1 + 4 + 1 + 4 + 1 + 4 + 1 + 1 + 4)
{
    // Initialize the default fields
    Unknown1 = 0;
    Unknown2 = 0;
    HasAccountInfo = true;
    BillingTimeRemaining = 0;
    BillingPlanFlags = 0;
    BillingTimeRested = 0;
}

void WorldPackets::AuthPackets::AuthResponse::Write()
{
    _worldPacket.WriteBit(Queued);
    if (Queued)
        _worldPacket.WriteBit(Unknown1);

    _worldPacket->WriteBit(HasAccountInfo);

    _worldPacket->FlushBits();

    // account info
    _worldPacket << uint32(BillingTimeRemaining);
    _worldPacket << uint8(Expansion);
    _worldPacket << uint32(Unknown2);
    _worldPacket << uint8(Expansion);
    _worldPacket << uint32(BillingTimeRested);
    _worldPacket << uint8(BillingPlanFlags);

    _worldPacket << uint8(Response);
    if (Queued)
        _worldPacket << uint32(QueuePos);
}

std::string WorldPackets::AuthPackets::AuthResponse::ToString() const
{
    // Perhaps write some additional data here
    return "WorldPackets::AuthenticationPackets::AuthResponse";
}
