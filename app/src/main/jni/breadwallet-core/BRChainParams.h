//
//  BRChainParams.h
//
//  Created by Aaron Voisine on 1/10/18.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRChainParams_h
#define BRChainParams_h

#include "BRMerkleBlock.h"
#include "BRPeer.h"
#include "BRSet.h"
#include "BRPeer.h"
#include <assert.h>

typedef struct {
    uint32_t height;
    UInt256 hash;
    uint32_t timestamp;
    uint32_t target;
} BRCheckPoint;

typedef struct {
    const char * const *dnsSeeds; // NULL terminated array of dns seeds
    uint16_t standardPort;
    uint32_t magicNumber;
    uint64_t services;
    int (*verifyDifficulty)(const BRMerkleBlock *block, const BRSet *blockSet); // blockSet must have last 2016 blocks
    const BRCheckPoint *checkpoints;
    size_t checkpointsCount;
} BRChainParams;

static const char *BRMainNetDNSSeeds[] = {
    "seed1.n8vcoin.dev.", "seed2.n8vcoin.dev.", "seed3.n8vcoin.dev.", NULL
};

static const char *BRTestNetDNSSeeds[] = {
    "", NULL
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {
    {      0, uint256("00000B7892E23DE3B819BB38f04CD3FF340E48AD7C379822A4ffA2b6A957EB9C"), 1559461295, 0x1e0ffff0 },
    {    500, uint256("DF0A736659F6BB7C65422A1559209A2DB4DA065586650DE6251A1741A1BC2757"), 1559548330, 0x1c0475d2 },
    {   1000, uint256("8D1287DCEFB1AA71BF6FA973A61F5A537D3BE41B06B4608F39414EE1958D6AAF"), 1559573493, 0x1a699a94 },
    {   2500, uint256("064E52B7419CAAA307FF168B03CA00490B177CD2AB4263F96AA7ED28DE380AF3"), 1559663431, 0x1a4c4107 },
    {   3000, uint256("89539BD72E124EE8DB9066B48682D2EBFB1AD3B610BB693E64A8400812AAD9CB"), 1559693565, 0x1a405b11 },
    {   4500, uint256("DE3F9F382AAE8CFE690622E7DF066316A442AE7C6F794565647FF439A1588AA3"), 1559784659, 0x1a568dca },
    {   6500, uint256("DCDAAA8DB9A24F0F2ED5FF0D112FD145EA3C3FDF6638039112151316E34DEA8D"), 1559906267, 0x1b00ce09 },
    {   8500, uint256("748DD3C0FECC470694A6BC06DED92BD7EDBBE945081E2D10ACA5D16DDE9C7C47"), 1560026537, 0x1b00c62c },
    {  10000, uint256("5BA8CC14AA4F92EA1E36B09657F6C7505CA89E43D2BD829AE88A49C370D23393"), 1560118025, 0x1b01e576 },
    {  13500, uint256("4A5DE183340197B6993AD726A2606756AD01683A2A7A0C7488752C65E2F6E5A5"), 1560328467, 0x1b011d30 },
    {  50000, uint256("f5d3c5033ad097f04da24e099449ac4f6e23d4295c648ac1b1aec17534e76943"), 1562535567, 0x1b013fe5 },
    { 105000, uint256("b34a3274321df783d1364467097108527f1db8189f878f2de1a1ab52d0c7c60a"), 1565856101, 0x1b01f319 }
};

static const BRCheckPoint BRTestNetCheckpoints[] = {
    {      0, uint256("000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"), 1296688602, 0x1d00ffff }
};

static int BRMainNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet) {
    const BRMerkleBlock *previous, *b = NULL;
    uint32_t i;

    assert(block != NULL);
    assert(blockSet != NULL);

    // check if we hit a difficulty transition, and find previous transition block
    if ((block->height % BLOCK_DIFFICULTY_INTERVAL) == 0) {
        for (i = 0, b = block; b && i < BLOCK_DIFFICULTY_INTERVAL; i++) {
            b = BRSetGet(blockSet, &b->prevBlock);
        }
    }

    previous = BRSetGet(blockSet, &block->prevBlock);
    return 1;//return BRMerkleBlockVerifyDifficulty(block, previous, (b) ? b->timestamp : 0);
}

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet) {
    return 1; // XXX skip testnet difficulty check for now
}

static const BRChainParams BRMainNetParams = {
    BRMainNetDNSSeeds,
    8848,                  // standardPort
    // 0xc02356a9          // magicNumber
    0xa95623c0,            // magicNumber
    0,//SERVICES_NODE_WITNESS, // services
    BRMainNetVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints)
};

static const BRChainParams BRTestNetParams = {
    BRMainNetDNSSeeds,
    8848,                  // standardPort
    // 0xc02356a9          // magicNumber
    0xa95623c0,            // magicNumber
    0,//SERVICES_NODE_WITNESS, // services
    BRMainNetVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints)
};

#endif // BRChainParams_h
