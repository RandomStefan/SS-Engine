#include "I_GUI.h"
#include "I_GUI.h"

I_GUI::I_GUI(SDL_Renderer* game, SDL_Window* win)
{
	currentWindow = win;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	SDL_DisplayMode DisplayMode;
	SDL_GetCurrentDisplayMode(0, &DisplayMode);
	ImGuiSDL::Initialize(game, 800, 600);
	io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(currentWindow, SDL_GL_GetCurrentContext());
}

I_GUI::~I_GUI()
{
}



SDL_Window* I_GUI::getWindow()
{
	return currentWindow;
}

void I_GUI::displayDemo()
{
	ImGui::ShowDemoWindow();
}

void I_GUI::displayInfo(Sprite* m_sprite)
{
	//vector<int> aux;
	//aux = m_sprite->getPosition();
	int x = m_sprite->xCoord;
	int y = m_sprite->yCoord;
	static int ex = m_sprite->xCoord;
	static int ey = m_sprite->yCoord;
	//startFrame();
	ImGui::Begin("my first window");
	if (ImGui::Button("Print Hello World"))
	{
		cout << "Hello world" << endl;
	}
	ImGui::Text("sample text");
	ImGui::Text("x: %d", x);
	ImGui::Text("y: %d", y);
	ImGui::DragInt("drag along the x axis", &ex, 1);
	//cout << "EX IS " << ex << "\n";
	m_sprite->setPosition(m_sprite->xCoord + ex, m_sprite->yCoord);
	ImGui::DragInt("drag along the y axis", &ey, 1);
	m_sprite->setPosition(m_sprite->xCoord, m_sprite->yCoord + ey);
	ImGui::Text("Sprite name: %s", m_sprite->getPathToTexture().c_str()); //ImGui::SameLine(); ImGui::Text(m_movingMonster->getFile().c_str());
	ImGui::End();

	if (m_sprite->isPointerOver(ImGui::GetMousePos().x, ImGui::GetMousePos().y, ImGui::IsMouseClicked(0)))
	{
		cout << "mess" << endl;
	}
	//endFrame();
}



void I_GUI::startFrame()
{
	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(currentWindow);
}

void I_GUI::endFrame()
{
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}

