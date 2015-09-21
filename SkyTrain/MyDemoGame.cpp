// ----------------------------------------------------------------------------
//  A few notes on project settings
//
//  - The project is set to use the UNICODE character set
//    - This was changed in Project Properties > Config Properties > General > Character Set
//    - This basically adds a "#define UNICODE" to the project
//
//  - The include directories were automagically correct, since the DirectX 
//    headers and libs are part of the windows SDK
//    - For instance, $(WindowsSDK_IncludePath) is set as a project include 
//      path by default.  That's where the DirectX headers are located.
//
//  - Two libraries had to be manually added to the Linker Input Dependencies
//    - d3d11.lib
//    - d3dcompiler.lib
//    - This was changed in Project Properties > Config Properties > Linker > Input > Additional Dependencies
//
//  - The Working Directory was changed to match the actual .exe's 
//    output directory, since we need to load the compiled shader files at run time
//    - This was changed in Project Properties > Config Properties > Debugging > Working Directory
//
// ----------------------------------------------------------------------------

#include "MyDemoGame.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

#pragma region Win32 Entry Point (WinMain)
// --------------------------------------------------------
// Win32 Entry Point - Where your program starts
// --------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Create the game object.
	MyDemoGame game(hInstance);

	// This is where we'll create the window, initialize DirectX, 
	// set up geometry and shaders, etc.
	if (!game.Init())
		return 0;

	// All set to run the game loop
	return game.Run();
}

#pragma endregion

#pragma region Constructor / Destructor
// --------------------------------------------------------
// Base class constructor will set up all of the underlying
// fields, and then we can overwrite any that we'd like
// --------------------------------------------------------
MyDemoGame::MyDemoGame(HINSTANCE hInstance)
	: DirectXGameCore(hInstance)
{
	// Set up a custom caption for the game window.
	// - The "L" before the string signifies a "wide character" string
	// - "Wide" characters take up more space in memory (hence the name)
	// - This allows for an extended character set (more fancy letters/symbols)
	// - Lots of Windows functions want "wide characters", so we use the "L"
	windowCaption = L"My Super Fancy GGP Game";

	// Custom window size - will be created by Init() later
	windowWidth = 800;
	windowHeight = 600;
}

// --------------------------------------------------------
// Cleans up our DirectX stuff and any objects we need to delete
// - When you make new DX resources, you need to release them here
// - If you don't, you get a lot of scary looking messages in Visual Studio
// --------------------------------------------------------
MyDemoGame::~MyDemoGame()
{
	delete camera;
}

#pragma endregion

#pragma region Initialization

// --------------------------------------------------------
// Initializes the base class (including the window and D3D),
// sets up our geometry and loads the shaders (among other things)
// --------------------------------------------------------
bool MyDemoGame::Init()
{
	// Call the base class's Init() method to create the window,
	// initialize DirectX, etc.
	if (!DirectXGameCore::Init())
		return false;

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives we'll be using and how to interpret them
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	XMFLOAT3 positions[] = {
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(2.0f, 5.0f, -15.0f),
		XMFLOAT3(-1.5f, -2.2f, -2.5f),
		XMFLOAT3(-3.8f, -2.0f, -12.3f),
		XMFLOAT3(2.4f, -0.4f, -3.5f),
		XMFLOAT3(-1.7f, 3.0f, -7.5f)
	};

	std::string modelNames[] = {
		"cube.obj",
		"cone.obj",
		"cylinder.obj",
		"helix.obj",
		"sphere.obj",
		"torus.obj"
	};

	for (size_t i = 0; i < 6; i++)
	{
		XMFLOAT3 position = positions[i];
		gameObjects.push_back(std::shared_ptr<IGameObject>(new Entity(std::shared_ptr<Transform>(new Transform(position.x, position.y, position.z)),
			new Model(modelNames[i], device),
			device,
			deviceContext)));
	}

	light1.AmbientColor = XMFLOAT4(0.1, 0.1, 0.1, 1.0);
	light1.DiffuseColor = XMFLOAT4(1, 0, 0, 1);
	light1.Direction = XMFLOAT3(1, -1, 0);
	
	light2.AmbientColor = XMFLOAT4(0.1, 0.1, 0.1, 1.0);
	light2.DiffuseColor = XMFLOAT4(0, 0, 1, 1);
	light2.Direction = XMFLOAT3(1, -1, 0);

	camera = new Camera(aspectRatio);
	// Successfully initialized
	return true;
}
#pragma endregion

#pragma region Window Resizing

// --------------------------------------------------------
// Handles resizing DirectX "stuff" to match the (usually) new
// window size and updating our projection matrix to match
// --------------------------------------------------------
void MyDemoGame::OnResize()
{
	// Handle base-level DX resize stuff
	DirectXGameCore::OnResize();
	if (camera != NULL)
		camera->UpdateProjectionMatrix();
}
#pragma endregion

#pragma region Game Loop

// --------------------------------------------------------
// Update your game here - take input, move objects, etc.
// --------------------------------------------------------
void MyDemoGame::UpdateScene(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
	if (GetAsyncKeyState('A') & 0x8000)
		camera->Move(CameraDirections::Left, deltaTime);
	else if (GetAsyncKeyState('W') & 0x8000)
		camera->Move(CameraDirections::Forward, deltaTime);
	else if (GetAsyncKeyState('S') & 0x8000)
		camera->Move(CameraDirections::Backward, deltaTime);
	else if (GetAsyncKeyState('D') & 0x8000)
		camera->Move(CameraDirections::Right, deltaTime);
	else if (GetAsyncKeyState(VK_CONTROL))
		camera->Move(CameraDirections::Down, deltaTime);
	else if (GetAsyncKeyState(VK_SPACE))
		camera->Move(CameraDirections::Up, deltaTime);

	for (auto& entity : gameObjects) {
		entity->GetTransform()->RotateX(deltaTime);
		entity->GetTransform()->RotateY(deltaTime);
		entity->GetTransform()->RotateZ(deltaTime);
		entity->Update(deltaTime);
	}
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void MyDemoGame::DrawScene(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of DrawScene (before drawing *anything*)
	deviceContext->ClearRenderTargetView(renderTargetView, color);
	deviceContext->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	for (auto& gameObject : gameObjects) {
		auto entity = std::static_pointer_cast<Entity>(gameObject);
		if (entity != NULL) {
			entity->GetMaterial()->GetPixelShader()->SetData("light1", &light1, sizeof(DirectionalLight));
			entity->GetMaterial()->GetPixelShader()->SetData("light2", &light2, sizeof(DirectionalLight));
			entity->Draw(deviceContext, camera->GetViewMatrix(), camera->GetProjectionMatrix());
		}
	}

	// Present the buffer
	//  - Puts the image we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME
	//  - Always at the very end of the frame
	HR(swapChain->Present(0, 0));
}

#pragma endregion

#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
//
// Feel free to add code to this method
// --------------------------------------------------------
void MyDemoGame::OnMouseDown(WPARAM btnState, int x, int y)
{
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hMainWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
//
// Feel free to add code to this method
// --------------------------------------------------------
void MyDemoGame::OnMouseUp(WPARAM btnState, int x, int y)
{
	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
//
// Feel free to add code to this method
// --------------------------------------------------------
void MyDemoGame::OnMouseMove(WPARAM btnState, int x, int y)
{
	if (firstMouse)
	{
		prevMousePos.x = x;
		prevMousePos.y = y;
		firstMouse = false;
	}

	auto xOffset = x - prevMousePos.x;
	auto yOffset = prevMousePos.y - y;

	prevMousePos.x = x;
	prevMousePos.y = y;
	
	camera->Update(xOffset, yOffset);
}
#pragma endregion