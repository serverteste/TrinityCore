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

WorldPackets::AuthPackets::AuthResponse::AuthResponse()
    : ServerPacket(SMSG_AUTH_RESPONSE, 1 + 4 + 1 + 4 + 1 + 4 + 1 + 1 + 4) { }

void WorldPackets::AuthPackets::AuthResponse::Write()
{
    _worldPacket << uint8(Result);
    _worldPacket.WriteBit(Result == AUTH_OK);
    _worldPacket.WriteBit(Queued);

    if (Result == AUTH_OK)
    {
        _worldPacket << uint32(VirtualRealmAddress);
        _worldPacket << uint32(VirtualRealms.size());
        _worldPacket << uint32(TimeRemain);
        _worldPacket << uint32(TimeOptions);
        _worldPacket << uint32(TimeRested);
        _worldPacket << uint8(ActiveExpansionLevel);
        _worldPacket << uint8(AccountExpansionLevel);
        _worldPacket << uint32(TimeSecondsUntilPCKick);
        _worldPacket << uint32(AvailableRaces->size());
        _worldPacket << uint32(AvailableClasses->size());
        _worldPacket << uint32(Templates.size());
        _worldPacket << uint32(CurrencyID);

        for (auto& realm : VirtualRealms)
        {
            _worldPacket << uint32(realm.RealmId);
            _worldPacket.WriteBit(realm.IsHomeRealm);
            _worldPacket.WriteBit(realm.IsInternalRealm);
            _worldPacket.WriteBits(realm.RealmNameActual.length(), 8);
            _worldPacket.WriteBits(realm.RealmNameNormalized.length(), 8);
            _worldPacket.WriteString(realm.RealmNameActual);
            _worldPacket.WriteString(realm.RealmNameNormalized);
        }

        for (auto& race : *AvailableRaces)
        {
            _worldPacket << uint8(race.first); /// the current race
            _worldPacket << uint8(race.second); /// the required Expansion
        }

        for (auto& klass : *AvailableClasses)
        {
            _worldPacket << uint8(klass.first); /// the current class
            _worldPacket << uint8(klass.second); /// the required Expansion
        }

        for (auto& templat : Templates)
        {
            _worldPacket << uint32(templat.TemplateSetId);
            _worldPacket << uint32(templat.TemplateClasses.size());
            for (auto& templatClass : templat.TemplateClasses)
            {
                _worldPacket << uint8(templatClass.Class);
                _worldPacket << uint8(templatClass.FactionGroup);
            }

            _worldPacket.FlushBits();
            _worldPacket.WriteBits(templat.Name.length(), 7);
            _worldPacket.WriteBits(templat.Description.length(), 10);
            _worldPacket.WriteString(templat.Name);
            _worldPacket.WriteString(templat.Description);
        }

        _worldPacket.FlushBits();

        _worldPacket.WriteBit(IsExpansionTrial);
        _worldPacket.WriteBit(ForceCharacterTemplate);
        _worldPacket.WriteBit(NumPlayersHorde != 0);
        _worldPacket.WriteBit(NumPlayersAlliance != 0);
        _worldPacket.WriteBit(IsVeteranTrial);

        if (NumPlayersHorde)
            _worldPacket << uint16(NumPlayersHorde);

        if (NumPlayersAlliance)
            _worldPacket << uint16(NumPlayersAlliance);
    }

    if (Queued)
    {
        _worldPacket << uint32(WaitCount);
        _worldPacket.WriteBit(HasFCM);
    }

    _worldPacket.FlushBits();
}

std::string WorldPackets::AuthPackets::AuthResponse::ToString() const
{
    // Perhaps write some additional data here
    return "WorldPackets::AuthenticationPackets::AuthResponse";
}
