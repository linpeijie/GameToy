//------------------------------------------------------------------------
//
//  Name:   State.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#ifndef STATE_H
#define STATE_H

class Miner;

class State
{
public:

  virtual ~State(){}

  virtual void Enter(Miner*)=0;

  virtual void Execute(Miner*)=0;

  virtual void Exit(Miner*)=0;

};

#endif