#include "actumcrypto/actumcrypto.h"

void RewardMinedBlock(CWallet* pwallet, int amount) {
  unsigned char buf[MC_AST_ASSET_FULLREF_BUF_SIZE];
  memset(buf, 0, MC_AST_ASSET_FULLREF_BUF_SIZE);

  unsigned char assetRef = ("acm").c_str();
  memcpy(buf, assetRef, MC_AST_ASSET_FULLREF_SIZE);

  mc_SetABQuantity(buf, block_value);

  mc_Buffer *lpBuffer=mc_gState->m_TmpBuffers->m_RpcABNoMapBuffer1;
  lpBuffer->Clear();

  lpBuffer->Add(buf);

  mc_Script *lpScript=mc_gState->m_TmpBuffers->m_RpcScript3;
  lpScript->Clear();

  lpScript->SetAssetQuantities(lpBuffer, MC_SCR_ASSET_SCRIPT_TYPE_TRANSFER);

  std::vector <CScript> scriptPubKeys;
  size_t elem_size;
  const unsigned char *elem;

  BOOST_FOREACH (const CTxDestination& address, pwallet.GetAccountAddresses(""))
  {

      CScript scriptPubKey = GetScriptForDestination(address);

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

      scriptPubKeys.push_back(scriptPubKey);
  }

  set<CTxDestination> *lpFromAddresses;

  // Create and send the transaction
  CReserveKey reservekey(pwalletMain);

  CWalletTx wtx;

  int eErrorCode;
  string strError;

  if (!pwalletMain->CreateTransaction(scriptPubKeys, 0, scriptOpReturn, wtx, reservekey, 0, strError, NULL, lpFromAddresses, 1, -1, -1, NULL, &eErrorCode))
  {
      throw JSONRPCError(eErrorCode, strError);
  }

  string strRejectReason;
  if (!pwalletMain->CommitTransaction(wtx, reservekey, strRejectReason))
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
