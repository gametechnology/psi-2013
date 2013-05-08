#include "BackButton.h"



enum{
		GUI_ID_BACK_BUTTON = 101
};

struct SAppContext
{
	IGUIEnvironment* env;
	bool buttonFlag; // boolean to pass the return of the OnEvent to the main class
};

class ButtonEventReceiver : public IEventReceiver{
public:
	ButtonEventReceiver(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.env;

			if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
				if(id == GUI_ID_BACK_BUTTON){
					Context.buttonFlag = true;
					return Context.buttonFlag;
				}
		}
		return false;
	}

private:
	SAppContext & Context;


};

BackButton::BackButton(rect< s32 > position) : Component()
{
	position_ = position;
	
	
	//button->setImage(video::ITexture("../assets/Textures/Stations/backButton.png");
}


BackButton::~BackButton(void){
	visible = false;
	this->getGame()->input->unsetCustomEventReceiver();
}
bool BackButton::isButtonPressed(){
	//ESC key
	if(this->getGame()->input->isKeyboardButtonPressed(irr::KEY_ESCAPE)){
		BackButton::pressed = true;
		return true;
	}else BackButton::pressed = false;
	if(	button->isPressed()) return true;
	else return false;

	//button clicked
	SAppContext context;
	context.env = getGame()->guiEnv;
	context.buttonFlag = false;
	ButtonEventReceiver receiver(context);

	this->getGame()->input->setCustomEventReceiver(&receiver);
	BackButton::pressed = context.buttonFlag;

	
	return BackButton::pressed;
}

void BackButton::update(){
	
}

void BackButton::init(){
	button = getGame()->guiEnv->addButton(position_,0,GUI_ID_BACK_BUTTON,L"Esc to Back",L"Go back to 2d shipmap");
	BackButton::pressed = false;
	BackButton::visible = true;
}
void BackButton::draw(){

}