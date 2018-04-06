#ifndef ACTUMCRYPTO_H
#define ACTUMCRYPTO_H

#include "entities/asset.h"
#include "protocol/multichainscript.h"

#include <boost/foreach.hpp>

class CWallet;

void RewardMinedBlock(CWallet* pwallet, int amount);

#endif // ACTUMCRYPTO_H
