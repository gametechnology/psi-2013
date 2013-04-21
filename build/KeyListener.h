#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include "Irrlicht\IEventReceiver.h"

class KeyListener : public IEventReceiver
{

public:

 KeyListener(Ship & context) : _ship(context) { }

 virtual bool OnEvent(const SEvent& event)
 {
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
  {

   switch (event.KeyInput.Key){
   case KEY_KEY_1:
     _ship.setActiveStation(1);
   case KEY_KEY_2:
     _ship.setActiveStation(2);
   }
   
   //if(receiver.IsKeyDown(irr::KEY_KEY_1)){

//   }else if(receiver.IsKeyDown(irr::KEY_KEY_2))


  }

  return false;
 }

private:
 Ship & _ship;
};
#endif