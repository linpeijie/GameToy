#include "Miner.h"
#include "MinerOwnedStates.h"

Miner::Miner(int id):BaseGameEntity(id),
                     m_Location(shack),
                     m_iGoldCarried(0),
                     m_iMoneyInBank(0),
                     m_iThirst(0),
                     m_iFatigue(0),
                     m_pCurrentState(GoHomeAndSleepTilRested::Instance()){}

/* 每个时刻更新一次状态 */
void Miner::Update()
{
  m_iThirst += 1;

  if (m_pCurrentState)
  {
    m_pCurrentState->Execute(this);
  }
}

/* 改变状态 */
void Miner::ChangeState(State* pNewState)
{
  //make sure both states are both valid before attempting to
  //call their methods
  assert (m_pCurrentState && pNewState);

  //call the exit method of the existing state
  m_pCurrentState->Exit(this);

  //change state to the new state
  m_pCurrentState = pNewState;

  //call the entry method of the new state
  m_pCurrentState->Enter(this);
}

/* 计算携带的金子数量 */
void Miner::AddToGoldCarried(const int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

/* 计算银行余额 */
void Miner::AddToWealth(const int val)
{
  m_iMoneyInBank += val;

  if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

/* 判断是否口渴 */
bool Miner::Thirsty()const
{
  if (m_iThirst >= ThirstLevel){return true;}

  return false;
}

/* 判断是否疲劳 */
bool Miner::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}