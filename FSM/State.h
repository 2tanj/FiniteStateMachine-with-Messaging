#ifndef STATE_H
#define STATE_H

struct Telegram;

template <class entity_type>
class State
{
public:

  virtual ~State(){}

  //this will execute when the state is entered
  virtual void Enter(entity_type*)=0;

  //this is the states normal update function
  virtual void Execute(entity_type*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void Exit(entity_type*)=0;

  //this executes if the agent receives a message from the 
  //message dispatcher
  virtual bool OnMessage(entity_type*, const Telegram&)=0;
};

#endif