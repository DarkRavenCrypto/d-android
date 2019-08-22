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
    "testnet-seed.bitcoin.jonasschnelli.ch.", "seed.testnet.bitcoin.sprovoost.nl.",
    "testnet-seed.bluematt.me.", NULL
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
    {       0, uint256("000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"), 1296688602, 0x1d00ffff },
    {  100800, uint256("0000000000a33112f86f3f7b0aa590cb4949b84c2d9c673e9e303257b3be9000"), 1376543922, 0x1c00d907 },
    {  201600, uint256("0000000000376bb71314321c45de3015fe958543afcbada242a3b1b072498e38"), 1393813869, 0x1b602ac0 },
    {  302400, uint256("0000000000001c93ebe0a7c33426e8edb9755505537ef9303a023f80be29d32d"), 1413766239, 0x1a33605e },
    {  403200, uint256("0000000000ef8b05da54711e2106907737741ac0278d59f358303c71d500f3c4"), 1431821666, 0x1c02346c },
    {  504000, uint256("0000000000005d105473c916cd9d16334f017368afea6bcee71629e0fcf2f4f5"), 1436951946, 0x1b00ab86 },
    {  604800, uint256("00000000000008653c7e5c00c703c5a9d53b318837bb1b3586a3d060ce6fff2e"), 1447484641, 0x1a092a20 },
    {  705600, uint256("00000000004ee3bc2e2dd06c31f2d7a9c3e471ec0251924f59f222e5e9c37e12"), 1455728685, 0x1c0ffff0 },
    {  806400, uint256("0000000000000faf114ff29df6dbac969c6b4a3b407cd790d3a12742b50c2398"), 1462006183, 0x1a34e280 },
    {  907200, uint256("0000000000166938e6f172a21fe69fe335e33565539e74bf74eeb00d2022c226"), 1469705562, 0x1c00ffff },
    { 1008000, uint256("000000000000390aca616746a9456a0d64c1bd73661fd60a51b5bf1c92bae5a0"), 1476926743, 0x1a52ccc0 },
    { 1108800, uint256("00000000000288d9a219419d0607fb67cc324d4b6d2945ca81eaa5e739fab81e"), 1490751239, 0x1b09ecf0 },
    { 1209600, uint256("0000000000000026b4692a26f1651bec8e9d4905640bd8e56056c9a9c53badf8"), 1507353706, 0x1973e180 },
    { 1310400, uint256("0000000000013b434bbe5668293c92ef26df6d6d4843228e8958f6a3d8101709"), 1527063804, 0x1b0ffff0 },
    { 1411200, uint256("00000000000000008b3baea0c3de24b9333c169e1543874f4202397f5b8502cb"), 1535560970, 0x194ac105 }
    //{ 1512000, 
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
    BRTestNetDNSSeeds,
    18333,                 // standardPort
    0xc02356a9,            // magicNumber
    0,//SERVICES_NODE_WITNESS, // services
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints)/sizeof(*BRTestNetCheckpoints)
};

#endif // BRChainParams_h
