#include "Miner.h"
#include "EntityNames.h"

int main()
{
  /*创建一个对象Bob*/
  Miner minerBob(ent_Miner_Bob);

  /* 一天中，Bob每个小时更新一次状态 */
  for (int i=0; i<20; ++i)
  {
    minerBob.Update();

    //Sleep(1);
  }

  return 0;
}