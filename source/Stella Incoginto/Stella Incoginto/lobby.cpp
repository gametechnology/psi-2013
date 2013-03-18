/** Example 005 User Interface

This tutorial shows how to use the built in User Interface of
the Irrlicht Engine. It will give a brief overview and show
how to create and use windows, buttons, scroll bars, static
texts, and list boxes.

As always, we include the header files, and use the irrlicht
namespaces. We also store a pointer to the Irrlicht device,
a counter variable for changing the creation position of a window,
and a pointer to a listbox.
*/
#include "stdafx.h"
#include "net.h"
#include <string.h>
#include <irrlicht.h>
#include "driverChoice.h"
#include "mainscene.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	IrrlichtDevice *device;
	s32				counter;
	IGUIListBox*	listbox;
};
IGUIEditBox *hostIp, *userName;
IGUIButton *host;
IGUIButton *client;
IGUIButton *start;
Net *network;
IGUIListBox * listbox;
BOOLEAN startmainscene; 
//TODO: MOdify to call the list for the net class
list<Client> clientList;
//Client client;
int lastListSize = 0;

// Define some values that we'll use to identify individual GUI controls.
enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,//hostButton
	GUI_ID_FILE_OPEN_BUTTON,//playerButton
	GUI_ID_FILE_START_BUTTON,
	GUI_ID_CONNECT_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR

};

/*
The Event Receiver is not only capable of getting keyboard and
mouse input events, but also events of the graphical user interface
(gui). There are events for almost everything: Button click,
Listbox selection change, events that say that a element was hovered
and so on. To be able to react to some of these events, we create
an event receiver.
We only react to gui events, and if it's such an event, we get the
id of the caller (the gui element which caused the event) and get
the pointer to the gui environment.
*/
class MyEventReceiverLobby : public IEventReceiver
{
public:
	MyEventReceiverLobby(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			

			/*
			If a scrollbar changed its scroll position, and it is
			'our' scrollbar (the one with id GUI_ID_TRANSPARENCY_SCROLL_BAR), then we change
			the transparency of all gui elements. This is a very
			easy task: There is a skin object, in which all color
			settings are stored. We simply go through all colors
			stored in the skin and change their alpha value.
			*/
			if(event.GUIEvent.EventType ==   EGET_SCROLL_BAR_CHANGED){
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					
					for (u32 i=0; i<EGDC_COUNT ; ++i)
					{
						SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
						col.setAlpha(pos);
						env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
					}
					
				}
			}

			/*
			If a button was clicked, it could be one of 'our'
			three buttons. If it is the first, we shut down the engine.
			If it is the second, we create a little window with some
			text on it. We also add a string to the list box to log
			what happened. And if it is the third button, we create
			a file open dialog, and add also this as string to the list box.
			That's all for the event receiver.
			*/
			if(event.GUIEvent.EventType ==  EGET_BUTTON_CLICKED){
				if(id == GUI_ID_QUIT_BUTTON){

					Context.device->closeDevice();
					startmainscene = true;
					return true;
				}
				if(id == GUI_ID_NEW_WINDOW_BUTTON)
					{
						host->setEnabled(true);
						start = env->addButton(rect<s32>(10,360,110,360 + 32), 0, GUI_ID_FILE_START_BUTTON,
						L"Start", L"Start a new game");
						start->setEnabled(false);
						network = new Net();
					/*
					Context.listbox->addItem(L"put list content");
					Context.counter += 30;
					if (Context.counter > 200)
						Context.counter = 0;
						*/
					client->setEnabled(false);
					return true;
					}
					

				if(id ==  GUI_ID_FILE_OPEN_BUTTON){//client
					client->setEnabled(true);
					start = env->addButton(rect<s32>(10,360,110,360 + 32), 0, GUI_ID_FILE_START_BUTTON,
			L"Start", L"Start a new game");
					start->setEnabled(false);
					env->addButton(rect<s32>(10,400,110,400 + 32), 0, GUI_ID_CONNECT_BUTTON,
			L"Connect", L"connect to a server");

					hostIp = env->addEditBox(L"Host IP", rect<s32>(350, 80, 550, 100));
					userName= env->addEditBox(L"user name", rect<s32>(350, 100, 550, 120));

					//Context.listbox->addItem(L"put list content");
					


					host->setEnabled(false);


					return true;
				}
				if(id ==   GUI_ID_FILE_START_BUTTON){
					network->StartGame();
					Context.device->closeDevice();
					startmainscene = true;
					return true;
				}
				if(id ==   GUI_ID_CONNECT_BUTTON){
					
					stringc name = userName->getText();
					stringc  ipaddres = hostIp->getText();
					Client *client = new Client(ipaddres.c_str(),clientList.getSize(), name.c_str());
					clientList.push_back(*client);
					
					network = new Net(ipaddres.c_str());
					//only for test
					//listbox->addItem(userName->getText());


					return true;}
			}

			if(event.GUIEvent.EventType ==   EGET_FILE_SELECTED){
					/*/ show the model filename, selected in the file dialog
					IGUIFileOpenDialog* dialog =
						(IGUIFileOpenDialog*)event.GUIEvent.Caller;
					Context.listbox->addItem(dialog->getFileName());
					*/
				}
				
			
			if(listbox->getItemCount() >=1)
				start->setEnabled(true);
			if(Net::stagegame == 1)
				listbox->setEnabled(true);

		}

		return false;
	}

private:
	SAppContext & Context;
};


/*
Ok, now for the more interesting part. First, create the Irrlicht device. As in
some examples before, we ask the user which driver he wants to use for this
example:
*/
int main()
{
	// ask user for driver
	//video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	//if (driverType==video::EDT_COUNT)
//return 1;

	// create device and exit if creation failed

	IrrlichtDevice * device = createDevice(video::EDT_SOFTWARE, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/* The creation was successful, now we set the event receiver and
		store pointers to the driver and to the gui environment. */

	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);

	video::IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();

	/*
	To make the font a little bit nicer, we load an external font
	and set it as the new default font in the skin.
	To keep the standard font for tool tip text, we set it to
	the built-in font.
	*/

	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

	/*
	We add three buttons. The first one closes the engine. The second
	creates a window and the third opens a file open dialog. The third
	parameter is the id of the button, with which we can easily identify
	the button in the event receiver.
	*/	

	env->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
			L"Quit", L"Exits Program");
	host = env->addButton(rect<s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
			L"Host", L"create a new host");
	client =env->addButton(rect<s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
			L"Client", L"create a new client");
	
	

	/*
	Now, we add a static text and a scrollbar, which modifies the
	transparency of all gui elements. We set the maximum value of
	the scrollbar to 255, because that's the maximal value for
	a color value.
	Then we create an other static text and a list box.
	*/

	env->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
	IGUIScrollBar* scrollbar = env->addScrollBar(true,
			rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
	scrollbar->setMax(255);

	// set scrollbar position to alpha value of an arbitrary element
	scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

	env->addStaticText(L"Connected Players:", rect<s32>(50,110,250,130), true);
	listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
	listbox->setEnabled(false);
	//env->addEditBox(L"Host IP", rect<s32>(350, 80, 550, 100));
	

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;

	// Then create the event receiver, giving it that context structure.
	MyEventReceiverLobby receiver(context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(&receiver);


	/*
	And at last, we create a nice Irrlicht Engine logo in the top left corner. 
	*/
	env->addImage(driver->getTexture("../../media/irrlichtlogo2.png"),
			position2d<int>(10,10));


	/*
	That's all, we only have to draw everything.
	*/

	while(device->run() && driver)
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, SColor(0,200,200,200));

		env->drawAll();

		
		if(clientList.size() > lastListSize){
			std::string str = "player: "+ clientList.getLast()->Name+ " ip: "+ clientList.getLast()->Ipadress;
			std::wstring widestr = std::wstring(str.begin(), str.end());
			const wchar_t* widecstr = widestr.c_str();
			listbox->addItem(widecstr); //updating list
		}
		driver->endScene();
	}

	device->drop();
	if(startmainscene == TRUE)
		MainSceneStart();
	return 0;
}

/*
**/
