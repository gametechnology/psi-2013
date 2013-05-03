#include "HudHelpText.h"


HudHelpText::HudHelpText(Composite* parent) : Component(parent)
{
	//parent is hudComposite.	HudComposite Parent should be station~
	station_ = (Station*)((parent->parent));
	helpTextString = &station_->helpTextString;
}


HudHelpText::~HudHelpText(void)
{
}
