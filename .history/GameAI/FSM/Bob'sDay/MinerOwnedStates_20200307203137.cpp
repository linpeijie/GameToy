#include "MinerOwnedStates.h"
#include "Miner.h"
#include "EntityNames.h"

#include <iostream>
using namespace std;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


/* methods for EnterMineAndDigForNugget */
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
  //如果Miner不在矿场，则走到矿场
  if (pMiner->Location() != goldmine)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "走到金矿场";

    pMiner->ChangeLocation(goldmine);
  }
}

void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
  //Miner挖满金子后，会改变状态为“到银行存钱”；如果渴了，会改变状态为“到酒馆解渴”
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "挖到一块金块！";

  if (pMiner->PocketsFull())
  {
    pMiner->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pMiner->Thirsty())
  {
    pMiner->ChangeState(QuenchThirst::Instance());
  }
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
       << "口袋里装满了黄金，哼着小曲离开了矿场。";
}



//----------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}


void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "该把沉甸甸的金子存到银行里了！";

    pMiner->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{

  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());

  pMiner->SetGoldCarried(0);

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
       << "存好黄金，银行账户里的金额为: "<< pMiner->Wealth();

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
         << "已经十分有钱了，是时候下班回家了！";

    pMiner->ChangeState(GoHomeAndSleepTilRested::Instance());
  }

  //otherwise get more gold
  else
  {
    pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "离开银行。";
}


//----------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
  if (pMiner->Location() != shack)
  {

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "走回家,准备好好休息一下。";

    pMiner->ChangeLocation(shack);
  }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued())
  {

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
          << "睡了一个好觉，该去继续挖金子了！";

     pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else
  {
    //sleep
    pMiner->DecreaseFatigue();


    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ... ";
  }
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "离开家。";
}




//------------------------------------------------methods for QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
  if (pMiner->Location() != saloon)
  {
    pMiner->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "快渴死了！他走向了酒馆！";
  }
}

void QuenchThirst::Execute(Miner* pMiner)
{
   if (pMiner->Thirsty())
   {
     pMiner->BuyAndDrinkAWhiskey();

     cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "灌满了酒杯，痛饮了一番！";

     pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else
  {
    cout << "\nERROR!\nERROR!\nERROR!";
  }
}

void QuenchThirst::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "酒足饭饱之后，他离开了酒馆。";
}

