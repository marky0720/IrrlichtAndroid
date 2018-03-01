/** Example 001 HelloWorld

This Tutorial shows how to set up the IDE for using the Irrlicht Engine and how
to write a simple HelloWorld program with it. The program will show how to use
the basics of the VideoDriver, the GUIEnvironment, and the SceneManager.
Microsoft Visual Studio is used as an IDE, but you will also be able to
understand everything if you are using a different one or even another
operating system than windows.

You have to include the header file <irrlicht.h> in order to use the engine. The
header file can be found in the Irrlicht Engine SDK directory \c include. To let
the compiler find this header file, the directory where it is located has to be
specified. This is different for every IDE and compiler you use. Let's explain
shortly how to do this in Microsoft Visual Studio:

- If you use Version 6.0, select the Menu Extras -> Options.
  Select the directories tab, and select the 'Include' Item in the combo box.
  Add the \c include directory of the irrlicht engine folder to the list of
  directories. Now the compiler will find the Irrlicht.h header file. We also
  need the irrlicht.lib to be found, so stay in that dialog, select 'Libraries'
  in the combo box and add the \c lib/VisualStudio directory.
  \image html "vc6optionsdir.jpg"
  \image latex "vc6optionsdir.jpg"
  \image html "vc6include.jpg"
  \image latex "vc6include.jpg"

- If your IDE is Visual Studio .NET, select Tools -> Options.
  Select the projects entry and then select VC++ directories. Select 'show
  directories for include files' in the combo box, and add the \c include
  directory of the irrlicht engine folder to the list of directories. Now the
  compiler will find the Irrlicht.h header file. We also need the irrlicht.lib
  to be found, so stay in that dialog, select 'show directories for Library
  files' and add the \c lib/VisualStudio directory.
  \image html "vcnetinclude.jpg"
  \image latex "vcnetinclude.jpg"

That's it. With your IDE set up like this, you will now be able to develop
applications with the Irrlicht Engine.

Lets start!

After we have set up the IDE, the compiler will know where to find the Irrlicht
Engine header files so we can include it now in our code.
*/
#define _IRR_COMPILE_WITH_ANDROID_DEVICE_ 1
#define _IRR_COMPILE_WITH_GUI_ 1
#include <irrlicht.h>
#include "os.h"
#ifdef _IRR_COMPILE_WITH_ANDROID_DEVICE_
#include "os.h"
#include <android/log.h>
#include <android/window.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "sensor", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#endif
/*
In the Irrlicht Engine, everything can be found in the namespace 'irr'. So if
you want to use a class of the engine, you have to write irr:: before the name
of the class. For example to use the IrrlichtDevice write: irr::IrrlichtDevice.
To get rid of the irr:: in front of the name of every class, we tell the
compiler that we use that namespace from now on, and we will not have to write
irr:: anymore.
*/
using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look at them, you can
read a detailed description of them in the documentation by clicking on the top
menu item 'Namespace List' or by using this link:
http://irrlicht.sourceforge.net/docu/namespaces.html
Like the irr namespace, we do not want these 5 sub namespaces now, to keep this
example simple. Hence, we tell the compiler again that we do not want always to
write their names.
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
To be able to use the Irrlicht.DLL file, we need to link with the Irrlicht.lib.
We could set this option in the project settings, but to make it easy, we use a
pragma comment lib for VisualStudio. On Windows platforms, we have to get rid
of the console window, which pops up when starting a program with main(). This
is done by the second pragma. We could also use the WinMain method, though
losing platform independence then.
*/
#if 0
//#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#if 0
struct SHelloTriangleData
{
	IrrlichtDevice *device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IAnimatedMesh* mesh;
	bool bAnimating;
	struct android_app* pApp;
};


void *pWindow; 
static void handle_cmd(struct android_app* app, int32_t cmd)
{
    struct SHelloTriangleData* data = (struct SHelloTriangleData*) app->userData;

    switch (cmd)
    {
        case APP_CMD_INIT_WINDOW:
			{
				{char msg[512]; sprintf(msg, "test %s %d", __FILE__, __LINE__); os::Printer::print(msg);};
				pWindow = (void*)data->pApp->window;
				data->device = createDevice( video::EDT_OGLES2, dimension2d<u32>(640, 480), 16,
					false, false, false, 0);
				data->driver = data->device->getVideoDriver();
				data->smgr = data->device->getSceneManager();
				data->mesh = data->smgr->getMesh("/sdcard/irr/media/sydney.md2");
				if (!data->mesh)
				{
					data->device->drop();
					return;
				}
				IAnimatedMeshSceneNode* node = data->smgr->addAnimatedMeshSceneNode( data->mesh );
				if (node)
				{
					node->setMaterialFlag(EMF_LIGHTING, false);
					node->setMD2Animation(scene::EMAT_RUN);
					node->setMaterialTexture( 0, data->driver->getTexture("/sdcard/irr/media/sydney.bmp") );
				}
				data->smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
        	}
            break;

        case APP_CMD_TERM_WINDOW:
//        	DeInitAPI(*data);
            break;
        case APP_CMD_GAINED_FOCUS:
            data->bAnimating = true;
            break;
        case APP_CMD_LOST_FOCUS:
            data->bAnimating = false;
            break;
    }
}
#endif




struct AppData
{
	IrrlichtDevice *device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* smgr;
	gui::IGUIFont* font;
	gui::IGUIFont* font2;
	video::ITexture* images;
	bool bAnimating;
	struct android_app* pApp;
	IAnimatedMesh* mesh;
	IAnimatedMeshSceneNode* node;
};
static void handle_cmd(struct android_app* app, int32_t cmd)
{
    struct AppData* data = (struct AppData*) app->userData;

    LOGI("marky handle_cmd");
    switch (cmd)
    {
        case APP_CMD_INIT_WINDOW:
			{
        LOGI("marky APP_CMD_INIT_WINDOW 0");
        /* TODO debug here why initial will crash
        data->device = createDevice( video::EDT_SOFTWARE,
								core::dimension2d<u32>(ANativeWindow_getWidth(app->window), ANativeWindow_getHeight(app->window)), //TODO[reizen]: doesn't work at the moment, always max resolution
								16,
								false,
								false,
								false,
								0);//,
								//(void*)data->pApp->window);
                     */
                    data->device = createDevice();
					data->driver = data->device->getVideoDriver();
					data->smgr = data->device->getSceneManager();

					if (!data->device) {
					    LOGI("marky APP_CMD_INIT_WINDOW 0-1 -> data->device=NULL");
					}
					if (!data->driver) {
					    LOGI("marky APP_CMD_INIT_WINDOW 0-2 -> data->driver=NULL");
					}
					if (!data->smgr) {
					    LOGI("marky APP_CMD_INIT_WINDOW 0-3 ->data->smgr=NULL");
					}

					data->images = data->driver->getTexture("/sdcard/irr/media/2ddemo.png");
					if (!data->images) {
					    LOGI("marky APP_CMD_INIT_WINDOW 0 -> data->images=NULL");
					}
					data->driver->makeColorKeyTexture(data->images, core::position2d<s32>(0,0));

#ifdef _IRR_COMPILE_WITH_GUI_
					data->font = data->device->getGUIEnvironment()->getBuiltInFont();
					data->font2 = data->device->getGUIEnvironment()->getBuiltInFont();//getFont("/sdcard/irr/media/fonthaettenschweiler.bmp");
#endif

					data->driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
					data->driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;
					LOGI("marky ANativeWindow_getWidth = %d,%d ", ANativeWindow_getWidth(app->window), ANativeWindow_getHeight(app->window));
                    LOGI("marky APP_CMD_INIT_WINDOW 1");
                    data->mesh = data->smgr->getMesh("/sdcard/irr/media/sydney.md2");
                    if (data->mesh) {
                        LOGI("marky APP_CMD_INIT_WINDOW 2");
                        data->node = data->smgr->addAnimatedMeshSceneNode( data->mesh );
				        LOGI("marky APP_CMD_INIT_WINDOW 3");
				        if (data->node)
				        {
					        data->node->setMaterialFlag(EMF_LIGHTING, false);
					        data->node->setMD2Animation(scene::EMAT_RUN);
					        data->node->setMaterialTexture( 0, data->driver->getTexture("/sdcard/irr/media/sydney.bmp") );
					        LOGI("marky APP_CMD_INIT_WINDOW 4");
				        }
                    }
                    data->smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
                    LOGI("marky APP_CMD_INIT_WINDOW 5");
        	}
            break;

        case APP_CMD_TERM_WINDOW:
            LOGI("marky APP_CMD_TERM_WINDOW");
            break;
        case APP_CMD_GAINED_FOCUS:
            LOGI("marky APP_CMD_GAINED_FOCUS");
            data->bAnimating = true;
            break;
        case APP_CMD_LOST_FOCUS:
            LOGI("marky APP_CMD_LOST_FOCUS");
            data->bAnimating = false;
            break;
    }
}

static int32_t handle_input(struct android_app* app, AInputEvent* event) {
    struct AppData* engine = (struct AppData*)app->userData;
	float x = 0.0f;
	float y = 0.0f;
	int pc = 0;
	int action = 0;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		pc = AMotionEvent_getPointerCount(event);
		action = AMotionEvent_getAction(event);
        x = AMotionEvent_getX(event, 0);
        y = AMotionEvent_getY(event, 0);
		LOGI("marky %x count: %d  x:%f y:$f", action, pc, x, y);
        return 1;
    }
    return 0;
}

/*
This is the main method. We can now use main() on every platform.
*/
void android_main(struct android_app* state)
{
    //SHelloTriangleData data;
	//memset(&data, 0, sizeof(SHelloTriangleData));

    AppData data;
	memset(&data, 0, sizeof(AppData));

	// Make sure glue isn't stripped.
	app_dummy();

	state->userData = &data;
	state->onAppCmd = handle_cmd;
	data.pApp = state;
	state->onInputEvent = handle_input;

	for(;;)
	{
		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while((ident=ALooper_pollAll(data.bAnimating ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
		{
			// Process this event.
			if (source != NULL)
			{
				source->process(state, source);
			}

			// Check if we are exiting.
			if (state->destroyRequested != 0)
			{
//				DeInitAPI(data);
				return;
			}
		}
        if(data.bAnimating && data.device->run())
        {
			//LOGI("marky drawAll ");
			data.driver->beginScene(true, true, SColor(255,0,0,1));
			data.smgr->drawAll();
			data.driver->endScene();
        }		
	}
}

#if 0
int main()
{
	/*
	The most important function of the engine is the createDevice()
	function. The IrrlichtDevice is created by it, which is the root
	object for doing anything with the engine. createDevice() has 7
	parameters:

	- deviceType: Type of the device. This can currently be the Null-device,
	   one of the two software renderers, D3D8, D3D9, or OpenGL. In this
	   example we use EDT_SOFTWARE, but to try out, you might want to
	   change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8,
	   EDT_DIRECT3D9, or EDT_OPENGL.

	- windowSize: Size of the Window or screen in FullScreenMode to be
	   created. In this example we use 640x480.

	- bits: Amount of color bits per pixel. This should be 16 or 32. The
	   parameter is often ignored when running in windowed mode.

	- fullscreen: Specifies if we want the device to run in fullscreen mode
	   or not.

	- stencilbuffer: Specifies if we want to use the stencil buffer (for
	   drawing shadows).

	- vsync: Specifies if we want to have vsync enabled, this is only useful
	   in fullscreen mode.

	- eventReceiver: An object to receive events. We do not want to use this
	   parameter here, and set it to 0.

	Always check the return value to cope with unsupported drivers,
	dimensions, etc.
	*/
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);  //EDT_OGLES2

	if (!device)
		return 1;

	/*
	Set the caption of the window to some nice text. Note that there is an
	'L' in front of the string. The Irrlicht Engine uses wide character
	strings when displaying text.
	*/
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	/*
	Get a pointer to the VideoDriver, the SceneManager and the graphical
	user interface environment, so that we do not always have to write
	device->getVideoDriver(), device->getSceneManager(), or
	device->getGUIEnvironment().
	*/
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	/*
	We add a hello world label to the window, using the GUI environment.
	The text is placed at the position (10,10) as top left corner and
	(260,22) as lower right corner.
	*/
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10,10,260,22), true);

	/*
	To show something interesting, we load a Quake 2 model and display it.
	We only have to get the Mesh from the Scene Manager with getMesh() and add
	a SceneNode to display the mesh with addAnimatedMeshSceneNode(). We
	check the return value of getMesh() to become aware of loading problems
	and other errors.

	Instead of writing the filename sydney.md2, it would also be possible
	to load a Maya object file (.obj), a complete Quake3 map (.bsp) or any
	other supported file format. By the way, that cool Quake 2 model
	called sydney was modelled by Brian Collins.
	*/
	IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

	/*
	To let the mesh look a little bit nicer, we change its material. We
	disable lighting because we do not have a dynamic light in here, and
	the mesh would be totally black otherwise. Then we set the frame loop,
	such that the predefined STAND animation is used. And last, we apply a
	texture to the mesh. Without it the mesh would be drawn using only a
	color.
	*/
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
	}

	/*
	To look at the mesh, we place a camera into 3d space at the position
	(0, 30, -40). The camera looks from there to (0,5,0), which is
	approximately the place where our md2 model is.
	*/
	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	/*
	Ok, now we have set up the scene, lets draw everything: We run the
	device in a while() loop, until the device does not want to run any
	more. This would be when the user closes the window or presses ALT+F4
	(or whatever keycode closes a window).
	*/
	while(device->run())
	{
		/*
		Anything can be drawn between a beginScene() and an endScene()
		call. The beginScene() call clears the screen with a color and
		the depth buffer, if desired. Then we let the Scene Manager and
		the GUI Environment draw their content. With the endScene()
		call everything is presented on the screen.
		*/
		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/
	device->drop();

	return 0;
}
#endif
/*
That's it. Compile and run.
**/
