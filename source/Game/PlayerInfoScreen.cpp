#include "PlayerInfoScreen.h"
#include "PlayerManager.h"

#include <sstream>

PlayerInfoScreen::PlayerInfoScreen(irr::core::vector2df position, irr::core::vector2df size)
{
	visible = false;
	_teamInfoTxt= L"No Data availeble";
	_position = position;
	_size = size;
}

PlayerInfoScreen::~PlayerInfoScreen(void)
{

}


void PlayerInfoScreen::init() {
	stringObj = getGame()->guiEnv->addStaticText(L"", irr::core::rect<irr::s32>(_position.X, _position.Y, _position.X + _size.X, _position.Y + _size.Y), false, true,(irr::gui::IGUIElement*)0, -1, true);
	stringObj->setOverrideColor(video::SColor(255, 0,0,0));
	stringObj->setBackgroundColor(video::SColor(200, 255, 255, 255));
}

void PlayerInfoScreen::update() 
{
	visible = getGame()->input->isKeyboardButtonDown(KEY_TAB);

	if (visible)
	{
		std::stringstream list;
		std::vector<PlayerData*> playerInfo = PlayerManager::GetInstance()->GetAllPlayers();
		
		_teamInfoTxt = L"";
		for(std::vector<PlayerData*>::iterator it = playerInfo.begin(); it != playerInfo.end(); ++it) 
		{
			list << (*it)->id << "- Player " << (*it)->name << "\t is in the ";
			char *stationInfo;
			switch ( (*it)->stationType ) 
			{
				case -1:
					stationInfo = "Hallway";
					break;
				case 0:
					stationInfo = "Power Station";
					break;
				case 1:
					stationInfo = "Defence Station";
					break;
				case 2:
					stationInfo = "Weapon Station";
					break;
				case 3:
					stationInfo = "Helm Station";
					break;
				case 4:
					stationInfo = "Navigation Station";
					break;
			}
			list << stationInfo << "\t and in team " << (*it)->team_id;
		}

		const size_t cSize = strlen(list.str().c_str())+1;
		_teamInfoTxt = new wchar_t[cSize];
		mbstowcs(_teamInfoTxt, list.str().c_str(), cSize);
	}
}

irr::core::stringw PlayerInfoScreen::varToString(irr::core::stringw str1, float var, irr::core::stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}


void PlayerInfoScreen::draw() {
	if (!visible || _teamInfoTxt == L"")  
	{
		stringObj->setText(L"");
		stringObj->setMaxSize(irr::core::dimension2du(1, 1));
		stringObj->setBackgroundColor(video::SColor(0, 255, 255, 255));
	} 
	else 
	{
		wstring str = L"hallo";
		stringObj->setText(_teamInfoTxt);
		stringObj->setMaxSize(irr::core::dimension2du(_size.X, _size.Y));
		stringObj->setBackgroundColor(video::SColor(255, 255, 255, 255));
		stringObj->setDrawBorder(true);
	}
}

void PlayerInfoScreen::setVisibility(bool visible) {
	this->visible = visible;
}
bool PlayerInfoScreen::isVisible() {
	return this->visible;
}


