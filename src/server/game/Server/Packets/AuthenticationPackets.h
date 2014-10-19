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
    namespace AuthenticationPackets
    {
        class AuthResponse final : public ServerPacket
        {
        public:
            AuthResponse() : ServerPacket(SMSG_AUTH_RESPONSE, 1 + 4 + 1 + 4 + 1 + 4 + 1 + 1 + 4)
            { 
            }

            void Write() override;
            std::string ToString() const override;

            /* Description etc etc etc*/
            bool HasAccountInfo;
            /* Description etc etc etc */
            bool Queued;
            /* Unknown value, when sending X, Y, or Z, the client reacts in W, M, or S ways  @TODO: Not implemented */
            bool Unknown1;
            /* Unknown value, when sending X, Y, or Z, the client reacts in W, M, or S ways  @TODO: Not implemented*/
            uint32 Unknown2;
            /* Represents the client's position in the login queue */
            uint32 QueuePos;
            /* Description. @TODO: Not implemented */
            uint32 BillingTimeRemaining;
            /* This field makes the client aware of the current account's expansion, possible values are 1, 2, 3, 4 or 5 */
            uint8 Expansion;
            /* Description  @TODO: Not implemented */
            uint32 BillingTimeReset;
            /* Description.  @TODO: Not implemented */
            uint8 BillingPlanFlags;
            /* The actual authentication response code, possible values are X, Y or Z (or a link to the enum that contain them in Doxygen style) */
            uint8 Response;
        };
    }
}
#endif