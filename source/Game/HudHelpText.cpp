#include "HudHelpText.h"
#include "Stations\Station.h"

enum{
		GUI_ID_HELP_BUTTON = 8008
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
				if(id == GUI_ID_HELP_BUTTON){
					Context.buttonFlag = true;
					return Context.buttonFlag;
				}
		}
		return false;
	}

private:
	SAppContext & Context;
};

HudHelpText::HudHelpText(std::string* helpText, irr::core::rect<s32> position )
{
	this->position_ = position;
	this->helpTextStr = helpText;
}


HudHelpText::~HudHelpText(void)
{

}
bool HudHelpText::isButtonPressed(){
	//H key
	if(this->getGame()->input->isKeyboardButtonPressed(irr::KEY_KEY_H)){
		this->pressed = true;
		return true;
	}else this->pressed = false;
	if(	button->isPressed()) return true;
	else return false;

	//button clicked
	SAppContext context;
	context.env = getGame()->guiEnv;
	context.buttonFlag = false;
	ButtonEventReceiver receiver(context);

	this->getGame()->input->setCustomEventReceiver(&receiver);
	HudHelpText::pressed = context.buttonFlag;

	
	return HudHelpText::pressed;
}

void HudHelpText::init(){
	button = getGame()->guiEnv->addButton(position_,0,GUI_ID_HELP_BUTTON,L"Help",L"Click this for tips");
	this->pressed = false;
	this->visible = true;
}

void HudHelpText::update(){

}

void HudHelpText::draw(){

}
