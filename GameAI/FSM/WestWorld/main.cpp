#include "Miner.h"
#include "EntityNames.h"

int main()
{
  //create a miner
  Miner miner(ent_Miner_Bob);

  //simply run the miner through a few Update calls
  for (int i=0; i<20; ++i)
  {
    miner.Update();

    //Sleep(1);
  }

  return 0;
}