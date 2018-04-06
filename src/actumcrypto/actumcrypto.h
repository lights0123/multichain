#ifndef ACTUMCRYPTO_H
#define ACTUMCRYPTO_H

#include "entities/asset.h"
#include "protocol/multichainscript.h"

#include <boost/assign/list_of.hpp>

class CWallet;

void RewardMinedBlock(CWallet* pwallet, int amount);

#endif // ACTUMCRYPTO_H
