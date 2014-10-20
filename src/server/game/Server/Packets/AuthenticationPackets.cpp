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

WorldPackets::AuthPackets::AuthResponse::AuthResponse(ExpansionRequirementContainer const& raceExpans, ExpansionRequirementContainer const& classExpans) : ServerPacket(SMSG_AUTH_RESPONSE, 1 + 4 + 1 + 4 + 1 + 4 + 1 + 1 + 4), 
RaceExpansions(raceExpans), ClassExpansions(classExpans)
{
    // Initialize the default fields
    HasAccountInfo = true;
    Queued = false;
    BillingTimeRemaining = 0;
    BillingPlanFlags = 0;
    BillingTimeRested = 0;
    AccountCurrency = 0;
    TimeSecondsUntilPCKick = 0;
    Trial = false;
    ForceCharacterTemplate = false;
    IsVeteranTrial = false;
    HasFCM = false;
    NumPlayersHorde = 0;
    NumPlayersAlliance = 0;
}

void WorldPackets::AuthPackets::AuthResponse::Write()
{
    _worldPacket << Response;
    _worldPacket.WriteBit(Response == AUTH_OK);
    _worldPacket.WriteBit(Queued);

    if (Response == AUTH_OK)
    {
        _worldPacket << uint32(VirtualRealmAddress);
        _worldPacket << uint32(ConnectedRealms.size());
        _worldPacket << uint32(BillingTimeRemaining);
        _worldPacket << uint32(BillingPlanFlags);
        _worldPacket << uint32(BillingTimeRested);
        _worldPacket << uint8(ActiveExpansion);
        _worldPacket << uint8(AccountExpansion);
        _worldPacket << uint32(TimeSecondsUntilPCKick);
        _worldPacket << uint32(RaceExpansions.size());
        _worldPacket << uint32(ClassExpansions.size());
        _worldPacket << uint32(CharacterTemplates.size());
        _worldPacket << uint32(AccountCurrency);

        for (auto& realm : ConnectedRealms)
        {
            _worldPacket << uint32(realm.RealmId);
            _worldPacket.WriteBit(realm.IsHomeRealm);
            _worldPacket.WriteBit(realm.IsInternalRealm);
            _worldPacket.WriteBits(realm.RealmNameActual.length(), 8);
            _worldPacket.WriteBits(realm.RealmNameNormalized.length(), 8);
            _worldPacket.WriteString(realm.RealmNameActual);
            _worldPacket.WriteString(realm.RealmNameNormalized);
        }

        for (auto& race : RaceExpansions)
        {
            _worldPacket << uint8(race.first); /// the current race
            _worldPacket << uint8(race.second); /// the required Expansion
        }

        for (auto& klass : ClassExpansions)
        {
            _worldPacket << uint8(klass.first); /// the current class
            _worldPacket << uint8(klass.second); /// the required Expansion
        }

        for (auto& templat : CharacterTemplates)
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

        _worldPacket.WriteBit(Trial);
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
        _worldPacket << uint32(QueuePos);
        _worldPacket.WriteBit(HasFCM);
    }
    
    _worldPacket.FlushBits();
}

std::string WorldPackets::AuthPackets::AuthResponse::ToString() const
{
    // Perhaps write some additional data here
    return "WorldPackets::AuthenticationPackets::AuthResponse";
}
