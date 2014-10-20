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

                /* Id of the auction */
                uint32 AuctionId;
                /* enum AuctionAction { AUCTION_SELL_ITEM, AUCTION_CANCEL, AUCTION_PLACE_BID } */
                uint32 Action;
                /* enum AuctionError { ERR_AUCTION_OK, ERR_AUCTION_INVENTORY, ERR_AUCTION_DATABASE_ERROR, ERR_AUCTION_NOT_ENOUGHT_MONEY, ERR_AUCTION_ITEM_NOT_FOUND, ERR_AUCTION_HIGHER_BID, ERR_AUCTION_BID_INCREMENT, ERR_AUCTION_BID_OWN, ERR_AUCTION_RESTRICTED_ACCOUNT } */
                uint32 ErrorCode;
                /* Amount of money bid in copper */
                uint64 Bid;
                /* Enum AuctionError */
                uint32 BidError;
                /* LowGUID of the bidder */
                uint64 Bidder;
                /* The sum of outbid is (1% from current bid)*5, if bid is very small, it is 1c */
                uint64 ActionOutBid;
        };
    }
}
#endif