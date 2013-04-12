#include <Engine\Input.h>
#include <Windows.h>

bool Input::KeyIsDown[KEY_KEY_CODES_COUNT];

bool Input::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	//OutputDebugString(L"Event happened");
	if (event.EventType == irr::EET_KEY_INPUT_EVENT){
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		//std::cout << " PRESSED" << event.KeyInput.Key;
	}
	return false;
}
bool Input::IsKeyDown(EKEY_CODE keyCode) const
{
	//std::cout << "SOME KEY PRESSED";
	return KeyIsDown[keyCode];
}

Input::Input(void)
{
	//OutputDebugString(L"Input made");
	//std::cout << "Input made"<<std::endl;
	//for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			//KeyIsDown[i] = false;

}


Input::~Input(void)
{
}
