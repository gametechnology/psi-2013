#include "HudHelpText.h"


HudHelpText::HudHelpText(Composite* parent)
{
	//parent is hudComposite.	HudComposite Parent should be station~
	
	helpTextString = &station_->helpTextString;
}


HudHelpText::~HudHelpText(void)
{
}
