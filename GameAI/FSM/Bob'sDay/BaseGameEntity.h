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

  //every entity must have a unique identifying number
  int m_ID;

  //this is the next valid ID. Each time a BaseGameEntity is instantiated
  //this value is updated
  static int  m_iNextValidID;

  //this must be called within the constructor to make sure the ID is set
  //correctly. It verifies that the value passed to the method is greater
  //or equal to the next valid ID, before setting the ID and incrementing
  //the next valid ID
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
  //all entities must implement an update function
  virtual void  Update()=0;

  int ID()const{return m_ID;}
};

#endif