#include "Scene.h"


Scene::Scene(Input* m_input, SDL_Renderer* s_Renderer, SDL_Window* s_Window, int window_w, int window_h)
{
	// Window details
	windowWidth = window_w;
	windowHeight = window_h;
	m_Window = s_Window;

	// We set the renderer and the input to the passed variables
	input = m_input;
	m_Renderer = s_Renderer;

	// We initialize our objects and we add them to a vector

	sceneText = new GameObject(m_Renderer, TEXT, "text");
	sceneText->initText("assets/DejaVuSans.ttf");
	sceneText->addObject(sceneObjects);

	background = new GameObject(m_Renderer, SPRITE, "background"); // background image
	background->initSprite("assets/Untitled.bmp",0 , 0, false, 1);
	background->addObject(sceneObjects);
	

	m_monster = new GameObject(m_Renderer, SPRITE, "goal"); // monster that represents the end goal of the game
	m_monster->initSprite("assets/goal.bmp", 1100, 250, true, 1);
	m_monster->addObject(sceneObjects);
	

	m_monsterTrans = new GameObject(m_Renderer, SPRITE, "pickup"); //monster that represents a pickup item 
	m_monsterTrans->initSprite("assets/pickup.bmp", 700, 400, true, 1);
	m_monsterTrans->addObject(sceneObjects);
	

	m_monsterTransKeyed = new GameObject(m_Renderer, SPRITE, "enemy"); //moving enemy that resets the players position if collided with
	m_monsterTransKeyed->initSprite("assets/enemy.bmp", 300, 100, true, 1);
	m_monsterTransKeyed->addObject(sceneObjects);
	

	m_movingMonster = new GameObject(m_Renderer, SPRITE, "player"); //player monster
	m_movingMonster->initSprite("assets/player.bmp", 0, 0, true, 1);
	m_movingMonster->addObject(sceneObjects);
	


	// Variable used to dictate when the enemy will change direction
	AIdirection = 0;
	offset = 400; // distance in pixels that the enemy will travel downwards before returning to initial position
	initialPos = m_monsterTransKeyed->objCoords.y; // initial position of enemy

	//Frametime frameTimes;
	OldTime = SDL_GetTicks();

	// Interface initialization
	interface = new I_GUI(m_Renderer, s_Window);

	nrofObj = 0;
	objectName = "AssetToDrag" + to_string(nrofObj);


	// We go down the assets folder to check for every asset in there
	string path = "./assets";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.path().extension() == ".bmp" || entry.path().extension() == ".jpg" || entry.path().extension() == ".png") // We only take into account
			// files with bmp, jpg or png extensions
		{
			string aux = entry.path().string();
			GameObject* Asset = new GameObject(m_Renderer, SPRITE, objectName);
			Asset->initSprite(aux,0, 0, true, 1);
			content.push_back(Asset);
			nrofObj++;
			objectName = "AssetToDrag" + to_string(nrofObj);

		}
		else if (entry.is_directory())
		{
			std::cout << "dir " << entry << std::endl;
		}



	}


}


Scene::~Scene()
{
	destroyScene();
}


void Scene::destroyScene()
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i]->destroy(); // call the destroy function that will act according to the object's type
	}
	sceneObjects.clear();

	cout << "Current scene has been cleared" << endl;
}


void Scene::saveScene(vector<GameObject*> savedSceneObjects)
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		savedSceneObjects[i] = sceneObjects[i]; // place the objects inside an auxiliary vector to save them
	}
}


void Scene::Update()
{
	// We gather frame time information for debugging
	Frametime frameTimes;
	int NewTime = SDL_GetTicks();
	int delta = NewTime - OldTime;
	frameTimes.push(delta);

	////-----------------------------------------------------------------------------INTERFACE start




	ImGui::NewFrame(); // We start a new IMGUI frame
	ImGui_ImplSDL2_NewFrame(m_Window); // We bind the frame to our window
	ImGui::Begin("Frame Times"); // We begin a "Frame Times" window
	ImGui::PlotLines("Frames", frameTimes.FrameTimeQueue.data(), frameTimes.capacity); // We populate that window with data about frametimes
	char buffer[64];
	snprintf(buffer, 64, "%f ms", frameTimes.averageTime());
	ImGui::Text("Frame Time: "); ImGui::SameLine();
	ImGui::Text(buffer);
	ImGui::End(); // We end the frame

	interface->displayInfo(m_movingMonster->m_Sprite); // We display info about the player object

	objectName = "AssetToDrag";
	// We open an "Editor" window that shows the images in the asset folder.
	ImGui::Begin("Editor");
	ImGui::BeginChild("Content Window", ImVec2(), true);
	
	for (int i = 0; i < content.size(); i++)
	{
		ImGui::PushID(i);

		ImGui::ImageButton((ImTextureID)content[i]->m_Sprite->getSpriteTexture(), { 100,100 });


		// Dragging from the window
		if (ImGui::BeginDragDropSource())
		{
			content[i]->setCoords((int)ImGui::GetMousePos().x, (int)ImGui::GetMousePos().y);
			AssetToDrag = content[i];
			ImGui::Image((ImTextureID)content[i]->m_Sprite->getSpriteTexture(), { 100,100 });
			GameObject* AssetToDrag = new GameObject(m_Renderer, SPRITE, objectName);
			AssetToDrag->initSprite(content[i]->getPathToTexture(), (int)ImGui::GetMousePos().x, (int)ImGui::GetMousePos().y, true, 1);
			//AssetToDrag->setCoords((int)ImGui::GetMousePos().x, (int)ImGui::GetMousePos().y);
			
			ImGui::EndDragDropSource();

		}
		ImGui::PopID();
		ImGui::SameLine();
	}

	ImGui::EndChild();
	ImGui::End();

	// We add the object that we want to drag in the scene vector checking to see if it's already there first
	if (AssetToDrag != nullptr)
	{
		if (AssetToDrag->checkName(sceneObjects) == 0)
		{
			AssetToDrag->addObject(sceneObjects);
			nrofObj++;
		}
	}
	// We change the object name
	objectName = objectName = "AssetToDrag" + to_string(nrofObj);
	
	

	////-----------------------------------------------------------------------------INTERFACE end




	//cout << (int)ImGui::GetMousePos().x <<endl;
	// We clean the renderer to make sure it's blank before rendering our scene
	SDL_RenderClear(m_Renderer);



	
	// We print the average frametime for debugging
	string frameTimeAvg = to_string(frameTimes.averageTime());
	

	// We render all objects inside our sceneObjects vector
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i]->render();
	}

	// We handle the user's input and allow them to move the player around
	m_movingMonster->handleInput(input);



	// We tell the enemy to change direction once they arrive at certain points
	if (m_monsterTransKeyed->objCoords.y == initialPos)
		AIdirection = 0;
	else if (m_monsterTransKeyed->objCoords.y == initialPos+offset)
		AIdirection = 1;
	m_monsterTransKeyed->autoMoveYAxis(AIdirection);

	
	
	// Determine behaviour of scene objects
	if (m_movingMonster->checkCollision(m_monsterTransKeyed))
		m_movingMonster->setCoords(0, 0);

	if (m_movingMonster->checkCollision(m_monsterTrans))
	{
		myString = "Picked up item !";
		m_monsterTrans->setCoords(9999, 9999);
	}


	if (m_movingMonster->checkCollision(m_monster))
	{
		m_monster->setCoords(10000, 10000);
		myString = "YOU WON !! press ESC to exit";
	}

	// Take input from user each frame and handle it
	m_movingMonster->updateInput();




	////-----------------------------------------------------------------------------INTERFACE start


	// We create a scene hierarchy that displays all game objects in the scene
	ImGui::Begin("Scene Hierarchy", 0, ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos({ 0,300 });
	ImGui::SetWindowSize({ 150, 720 - 300 });

	// We go through the game objects and do separate things for each type
	for (GameObject* gameObject : sceneObjects)
	{
		
		if (gameObject->type == SPRITE)
		{
			if (ImGui::TreeNode(gameObject->name.c_str()))
			{
				ImGui::TreePop();
			}
		}
		else if (gameObject->type == TRIGGER)
		{
			string coord = "Trigger at x: " + to_string(gameObject->objCoords.x) + " " + "y: " + to_string(gameObject->objCoords.y);
			if (ImGui::TreeNode(coord.c_str()))
			{
				ImGui::TreePop();

			}
		}
		else if (gameObject->type == TRIGGER)
		{
			if (ImGui::TreeNode("TEXT OBJECT"))
			{
				ImGui::TreePop();
			}
		}

	}
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;

	ImGui::End();

	////-----------------------------------------------------------------------------INTERFACE end



	
	//Draw the text on the screen
	sceneText->UpdateText("Frame time average: " + frameTimeAvg, 10, windowHeight - 20, 10, { 255, 0, 0 }); // for debugging
	sceneText->UpdateText(myString, 50, 70, 50, { 0,255,0 }); // for various events inside the scene




	////-----------------------------------------------------------------------------INTERFACE start

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

	////-----------------------------------------------------------------------------INTERFACE end





	// Render the frame
	SDL_RenderPresent(m_Renderer);
	SDL_Delay(16); // Slightly delay the other frame

	// Reset timer after frame is done
	OldTime = NewTime;

}
