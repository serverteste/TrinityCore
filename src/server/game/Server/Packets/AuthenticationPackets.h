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

#ifndef AuthenticationPacketsWorld_h__

#include "Packet.h"

namespace WorldPackets
{
    namespace AuthPackets
    {
        class AuthResponse final : public ServerPacket
        {
        public:
            AuthResponse();

            void Write() override;
            std::string ToString() const override;

            bool HasAccountInfo; ///< true if this packet contains account information. It is always false when Queued is true.
            bool Queued; ///< true if the account is in the login queue. If true then QueuePos must be set
            bool Unknown1; ///< unknown value @todo implement
            uint32 Unknown2; ///< unknown value @todo implement
            uint32 QueuePos; ///< position of the account in the login queue, it is only sent when Queued is true
            uint32 BillingTimeRemaining; ///< the remaining game time that the account has in seconds. It is not currently implemented and probably won't ever be.
            uint8 Expansion; ///< the current expansion of this account, the possible values are in @ref Expansions
            uint32 BillingTimeRested; ///< affects the return value of the GetBillingTimeRested() client API call, it is the number of seconds you have left until the experience points and loot you receive from creatures and quests is reduced. It is only used in the Asia region in retail, it's not implemented in TC and will probably never be.
            uint8 BillingPlanFlags; ///< controls the behavior of the client regarding billing, used in Asia realms, as they don't have monthly subscriptions, possible values are in @ref BillingPlanFlags. It is not currently implemented and will probably never be.
            uint8 Response; ///< the result of the authentication process, it is AUTH_OK if it succeeded and the account is ready to log in. It can also be AUTH_WAIT_QUEUE if the account entered the login queue (Queued, QueuePos), possible values are @ref ResponseCodes
        };
    }
}
#endif