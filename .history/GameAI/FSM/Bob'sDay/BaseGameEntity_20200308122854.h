//------------------------------------------------------------------------
//
//  Name:   BaseGameEntity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#ifndef BASE_GAME_ENTITY_H
#define BASE_GAME_ENTITY_H

class BaseGameEntity
{

private:

  //每个人都有唯一的id
  int m_ID;

  //每增加一个人，id都要更新一次，且保证在程序运行过程中 id 相匹配，否则发出警报
  static int  m_iNextValidID;
  void SetID(int val);

public:

  /* 初始化, 设置人物的id */
  BaseGameEntity(int id)
  {
    SetID(id);
  }

  /* 虚类，表示继承了该类的子类必须执行以下所有虚函数 */
  virtual ~BaseGameEntity(){}

  /* 纯虚函数 */
  virtual void  Update()=0;

  int ID()const{return m_ID;}
};

#endif