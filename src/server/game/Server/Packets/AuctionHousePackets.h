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

#ifndef AuctionHousePacketsWorld_h__

#include "Packet.h"

namespace WorldPackets
{
    namespace AuctionHousePackets
    {
        class AuctionCommandResult final : public ServerPacket
        {
            public:
                AuctionCommandResult();

                void Write() override;
                std::string ToString() const override;

                uint32 AuctionId; ///< the id of the auction that triggered this notification
                uint32 Action; ///< the type of action that triggered this notification. Possible values are @ref AuctionAction
                uint32 ErrorCode; ///< the error code that was generated when trying to perform the action. Possible values are @ref AuctionError
                uint64 Bid; ///< the amount of money that the player bid in copper
                uint32 BidError; ///< the bid error. Possible values are @ref AuctionError
                uint64 Bidder; ///< the GUID of the bidder for this auction.
                uint64 AuctionOutBid; ///< the sum of outbid is (1% of current bid) * 5, if the bid is too small, then this value is 1 copper.
        };
    }
}
#endif