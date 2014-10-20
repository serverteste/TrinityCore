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

#include "ObjectMgr.h"
#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "AuthenticationPackets.h"

void WorldSession::SendAuthResponse(uint8 code, bool queued, uint32 queuePos)
{
    WorldPackets::AuthPackets::AuthResponse response;
    response.Result = code;
    response.Queued = queued;
    response.WaitCount = queuePos;
    response.AccountExpansionLevel = Expansion();
    response.ActiveExpansionLevel = Expansion();
    response.VirtualRealmAddress = realmHandle.Index;

    std::string realmName = sObjectMgr->GetRealmName(realmHandle.Index);

    // Send current home realm. Also there is no need to send it later in realm queries.
    response.VirtualRealms.emplace_back(realmHandle.Index, true, false, realmName, realmName);

    response.AvailableClasses = &sObjectMgr->GetClassExpansionRequirements();
    response.AvailableRaces = &sObjectMgr->GetRaceExpansionRequirements();

    SendPacket(response);
}

void WorldSession::SendAuthWaitQue(uint32 position)
{
    WorldPackets::AuthPackets::AuthResponse response;

    if (position == 0)
    {
        response.Result = AUTH_OK;
        response.HasAccountInfo = false;
        response.Queued = false;
    }
    else
    {
        response.Queued = true;
        response.HasAccountInfo = false;
        response.WaitCount = position;
        response.Result = AUTH_WAIT_QUEUE;
    }

    SendPacket(response);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}
