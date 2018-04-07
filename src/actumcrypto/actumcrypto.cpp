#include "actumcrypto/actumcrypto.h"

#include <boost/foreach.hpp>

using namespace std;

void RewardMinedBlock(CWallet* pwallet, int amount) {
  unsigned char buf[MC_AST_ASSET_FULLREF_BUF_SIZE];
  memset(buf, 0, MC_AST_ASSET_FULLREF_BUF_SIZE);

  char* assetRef = "acm";
  memcpy(buf, assetRef, MC_AST_ASSET_FULLREF_SIZE);

  mc_SetABQuantity(buf, amount);

  mc_Buffer *lpBuffer=mc_gState->m_TmpBuffers->m_RpcABNoMapBuffer1;
  lpBuffer->Clear();

  lpBuffer->Add(buf);

  mc_Script *lpScript=mc_gState->m_TmpBuffers->m_RpcScript3;
  lpScript->Clear();

  lpScript->SetAssetQuantities(lpBuffer, MC_SCR_ASSET_SCRIPT_TYPE_TRANSFER);

  CScript scriptPubKey;
  size_t elem_size;
  const unsigned char *elem;

  if(lpScript)
  {
      if(fDebug)LogPrint("mchnminor","mchn: Sending script with %d OP_DROP element(s)",lpScript->GetNumElements());
      if(lpScript->GetNumElements() > MCP_STD_OP_DROP_COUNT )
          throw JSONRPCError(RPC_INTERNAL_ERROR, "Invalid number of elements in script");

      for(int element=0;element < lpScript->GetNumElements();element++)
      {
          elem = lpScript->GetData(element,&elem_size);
          if(elem)
          {
              scriptPubKey << vector<unsigned char>(elem, elem + elem_size) << OP_DROP;
          }
          else
              throw JSONRPCError(RPC_INTERNAL_ERROR, "Invalid script");
      }
  }

  CScript scriptOpReturn=CScript();

  mc_Script opreturnscript;

  if(opreturnscript)
  {
      elem = opreturnscript->GetData(0,&elem_size);
      if(elem_size > 0)
      {
          scriptOpReturn << OP_RETURN << vector<unsigned char>(elem, elem + elem_size);
      }
  }
/* MCHN END */

  CWalletTx wtx;

  // Create and send the transaction
  CReserveKey reservekey(pwallet);
  string strError;
  if (!pwallet->CreateTransaction(scriptPubKey, 0, scriptOpReturn, wtx, reservekey, 0, strError))
  {
      LogPrintf("SendMoney() : %s\n", strError);
      throw JSONRPCError(RPC_WALLET_INSUFFICIENT_FUNDS, strError);
  }
/* MCHN START */
  string strRejectReason;
  if (!pwallet->CommitTransaction(wtx, reservekey, strRejectReason))
  {
      if(strRejectReason.size())
      {
          throw JSONRPCError(RPC_TRANSACTION_REJECTED, "Error: The transaction was rejected: " + strRejectReason);
      }
      else
      {
          throw JSONRPCError(RPC_TRANSACTION_REJECTED, "Error: this transaction was rejected. This may be because you are sharing private keys between nodes, and another node has spent the funds used by this transaction.");
      }
  }
}
