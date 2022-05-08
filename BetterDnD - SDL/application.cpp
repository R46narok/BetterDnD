#include "dnd/combatSystem.h"
#include "utilities/Server.h"
#include "dnd/playerFuncs.h"
#include "ECS/EntityComponentSystem.h"
#include "ECS/SpriteComponent.h"
#include "ECS/TransformComponent.h"
#include "math/vec4.h"
#include "dnd/DM.h"
#include <string>
#include <thread>
#include <GLFW/glfw3.h>
#include <math.h>
#include <mutex>

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

SDL_Texture *NAME, *CR, *SPEED, *STATS;

std::vector<vec2> monstPos;
std::vector<vec2> playerPos;

int x, y;
SDL_Rect src, dest;

Manager manager;

std::vector<Weapon::Weapon> weapons = Weapon::loadWeapons();

SDL_Renderer* Application::renderer = nullptr;
SDL_Event Application::event;
bool Application::isRunning = false;

bool MAIN_MENU;
Sint32 iWheelX;
Sint32 iWheelY;

Server *server  = new Server();

std::vector<Entity*> chSheets;
std::vector<Player::Player*> playersVec;

//define entities
auto& mainMenuStart(manager.addEntity());
auto& mainMenuContinue(manager.addEntity());
auto& mainMenuExit(manager.addEntity());
auto& mainMenu(manager.addEntity());

auto& page1(manager.addEntity());
auto& page2(manager.addEntity());
auto& homeBackground(manager.addEntity());
auto& back_button(manager.addEntity());
auto& playerVisualizationBackground(manager.addEntity());
auto& playerVisualizationBackground2(manager.addEntity());
auto& playerVisualization(manager.addEntity());

auto& rolls_menu(manager.addEntity());
auto& rolls_dragon(manager.addEntity());
auto& rolls_hovered(manager.addEntity());
auto& rolls_backgr(manager.addEntity());

auto& navbar(manager.addEntity());
auto& navbar_home(manager.addEntity());
auto& navbar_books(manager.addEntity());
auto& navbar_rolls(manager.addEntity());
auto& navbar_VP(manager.addEntity());
auto& navbar_Map(manager.addEntity());

auto& books(manager.addEntity());
auto& books_download(manager.addEntity());
auto& books_rule(manager.addEntity());
auto& books_camp(manager.addEntity());

auto& map(manager.addEntity());
auto& map_grid(manager.addEntity());
auto& map_create(manager.addEntity());

auto& monstersMenu(manager.addEntity());

SDL_Texture *smallNavBar;

std::vector<Monsters::Monster*> mapMonsters;



Application::Application() {}
Application::~Application() {}

int visPlayer = -1;

bool menu[5];
bool mainMenuBool[3] = { false, false, false };
bool booksBool[3] = { false, false, false };
bool mapBool[2] = { false, false};

HCURSOR HandCursor;
HCURSOR Cursor;
SDL_Texture* monsterIcon;
int setDestXto = 70;
std::vector<Monsters::Monster> loadedMonsters;
void Application::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	//server->init();
	std::thread InitThread = server->GetinitThread();
	std::thread UpdateThread = server->GetUpdateThread();

	InitThread.detach();
	UpdateThread.detach();
	//SDL initializing
	for (int i = 0; i < 5; i++)
	{
		menu[i] = false;
	}

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem initialized!" << std::endl;
		TTF_Init();

		HandCursor = LoadCursor(NULL, IDC_HAND);
		Cursor = LoadCursor(NULL, IDC_ARROW);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_DisplayMode current;
		SDL_GetCurrentDisplayMode(0, &current);

		// Setup ImGui binding

		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_OPENGL);
		SDL_GL_SetSwapInterval(1); // Enable vsync
		glewInit();
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer Created!" << std::endl;
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		isRunning = true;

		page1.addComponent<TransformComponent>(65, 0, 1632, 1238, 0.5);
		page1.addComponent<SpriteComponent>("database/DMbook/DMDnDBasicRules_v0.1-2.jpg");
		page1.addGroup(groupPages);

		page2.addComponent<TransformComponent>(0, 0, 1238, 1632, 0.7);
		page2.addComponent<SpriteComponent>("database/DMbook/DMDnDBasicRules_v0.1-3.jpg");
		page2.addGroup(groupPages);
		

		homeBackground.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		homeBackground.addComponent<SpriteComponent>("assets/home.jpg");
		homeBackground.addGroup(groupMap);

		back_button.addComponent<TransformComponent>(978 + 88 + 20, 0, 600, 600, 0.1);
		back_button.addComponent<SpriteComponent>("database/arrow-left.png");
		back_button.addGroup(groupPages2);

		navbar.addComponent<TransformComponent>(0, 0, 760, 65, 1);
		navbar.addComponent<SpriteComponent>("database/NavBar/navBar.jpg");
		navbar.addGroup(Application::groupNavBar);

		monsterIcon = TextureManager::LoadTexture("database/MonstersMenu/monsterIcon.png");

		navbar_home.addComponent<TransformComponent>(0, 0, 760, 65, 1);
		navbar_home.addComponent<SpriteComponent>("database/NavBar/navBar-home.jpg");
		navbar_home.addGroup(Application::groupNavBar);

		navbar_books.addComponent<TransformComponent>(0, 0, 760, 65, 1);
		navbar_books.addComponent<SpriteComponent>("database/NavBar/navBar-books.jpg");
		navbar_books.addGroup(Application::groupNavBar);

		navbar_rolls.addComponent<TransformComponent>(0, 0, 760, 65, 1);
		navbar_rolls.addComponent<SpriteComponent>("database/NavBar/navBar-rolls.jpg");
		navbar_rolls.addGroup(Application::groupNavBar);

		navbar_VP.addComponent<TransformComponent>(0, 0, 760, 65, 1);
		navbar_VP.addComponent<SpriteComponent>("database/NavBar/navBar-view.jpg");
		navbar_VP.addGroup(Application::groupNavBar);

		books.addComponent<TransformComponent>(65, 0, 769, 1096, 1);
		books.addComponent<SpriteComponent>("database/Books/books.jpg");

		books_download.addComponent<TransformComponent>(65, 0, 769, 1096, 1);
		books_download.addComponent<SpriteComponent>("database/Books/books-download.jpg");

		books_camp.addComponent<TransformComponent>(65, 0, 769, 1096, 1);
		books_camp.addComponent<SpriteComponent>("database/Books/books-campaign.jpg");

		books_rule.addComponent<TransformComponent>(65, 0, 769, 1096, 1);
		books_rule.addComponent<SpriteComponent>("database/Books/books-rule.jpg");

		map.addComponent<TransformComponent>(65, 0, 769, 505, 1);
		map.addComponent<SpriteComponent>("database/Map/map.jpg");

		map_grid.addComponent<TransformComponent>(65, 0, 769, 505, 1);
		map_grid.addComponent<SpriteComponent>("database/Map/map-grid.jpg");

		map_create.addComponent<TransformComponent>(65, 0, 769, 505, 1);
		map_create.addComponent<SpriteComponent>("database/Map/map-create.jpg");

		rolls_menu.addComponent<TransformComponent>(0, 0, 710, 1154, 1);
		rolls_menu.addComponent<SpriteComponent>("database/Rolls/rolls-menu.png");
		rolls_menu.addGroup(Application::groupRolls);

		rolls_dragon.addComponent<TransformComponent>(290, 760, 35, 43, 1);
		rolls_dragon.addComponent<SpriteComponent>("database/Rolls/rolls-dragon.png");
		rolls_dragon.addGroup(Application::groupRolls);

		rolls_hovered.addComponent<TransformComponent>(0, 0, 710, 1154, 1);
		rolls_hovered.addComponent<SpriteComponent>("database/Rolls/rolls-hovered.png");
		rolls_hovered.addGroup(Application::groupRolls);

		rolls_backgr.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		rolls_backgr.addComponent<SpriteComponent>("database/Rolls/backgr.jpg");
		rolls_backgr.addGroup(Application::groupRolls);

		loadedMonsters = Monsters::loadMonsters();

		playersVec.push_back(&Player::Player(14, 18, 14, 11,13, 9, Classes::Sorcerer, Races::Dragonborn, Background::Criminal, "neutral evil"));
		playersVec.push_back(&Player::Player(14, 18, 14, 11,13, 9, Classes::Bard, Races::Gnome, Background::Criminal, "neutral evil"));
		playersVec.push_back(&Player::Player(14, 18, 14, 11,13, 9, Classes::Cleric, Races::Human, Background::Criminal, "neutral evil"));
		playersVec.push_back(&Player::Player(14, 18, 14, 11,13, 9, Classes::Druid, Races::Tiefling, Background::Criminal, "neutral evil"));
		

		playerVisualizationBackground.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		playerVisualizationBackground.addComponent<SpriteComponent>("database/dnd-background.jpg");
		playerVisualizationBackground.addGroup(groupPlayerVisualization);

		playerVisualizationBackground2.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		playerVisualizationBackground2.addComponent<SpriteComponent>("database/dnd-background2.jpg");
		playerVisualizationBackground2.addGroup(groupPlayerVisualization);

		playerVisualization.addComponent<TransformComponent>(0, 0, 500, 364, 1);
		playerVisualization.addComponent<SpriteComponent>();
		playerVisualization.addGroup(groupPlayerVisualization);

		monstersMenu.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		monstersMenu.addComponent<SpriteComponent>("database/MonstersMenu/monstersMenu.jpg");

		mainMenu.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		mainMenu.addComponent<SpriteComponent>("database/MainMenu/home.jpg");

		mainMenuStart.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		mainMenuStart.addComponent<SpriteComponent>("database/MainMenu/home-start.jpg");

		mainMenuContinue.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		mainMenuContinue.addComponent<SpriteComponent>("database/MainMenu/home-choose.jpg");

		mainMenuExit.addComponent<TransformComponent>(0, 0, 760, 1154, 1);
		mainMenuExit.addComponent<SpriteComponent>("database/MainMenu/home-exit.jpg");
		dest.y = 50;
		MAIN_MENU = true;
		//DM.update();
		int br = 1;
		for (auto& p : playersVec)
		{
			Mat img = imread("database/TWC-DnD-5E-Character-Sheet-v1.3-page-001.jpg", CV_LOAD_IMAGE_COLOR);
			//stats
			if (p->m_Strength <= 9)
			{
				putText(img, std::to_string(p->m_Strength), cvPoint(45, 168), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}
			else {
				putText(img, std::to_string(p->m_Strength), cvPoint(37, 168), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}

			if (p->m_Dexterity <= 9)
			{
				putText(img, std::to_string(p->m_Dexterity), cvPoint(45, 235), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}
			else {
				putText(img, std::to_string(p->m_Dexterity), cvPoint(37, 235), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}

			if (p->m_Constitution <= 9)
			{
				putText(img, std::to_string(p->m_Constitution), cvPoint(45, 300), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}
			else {
				putText(img, std::to_string(p->m_Constitution), cvPoint(37, 300), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}

			if (p->m_Intelligence <= 9)
			{
				putText(img, std::to_string(p->m_Intelligence), cvPoint(45, 368), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}
			else {
				putText(img, std::to_string(p->m_Intelligence), cvPoint(37, 368), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}

			if (p->m_Wisdom <= 9)
			{
				putText(img, std::to_string(p->m_Wisdom), cvPoint(45, 436), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}
			else {
				putText(img, std::to_string(p->m_Wisdom), cvPoint(37, 436), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}

			if (p->m_Charisma <= 9)
			{
				putText(img, std::to_string(p->m_Charisma), cvPoint(45, 504), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}
			else {
				putText(img, std::to_string(p->m_Charisma), cvPoint(37, 504), FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1, LINE_AA);
			}

			//character info
			std::string temp = p->m_CharPlayerClass;
			putText(img, temp.append(" ") + std::to_string(p->m_Level), cvPoint(259, 58), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);
			putText(img, p->m_CharPlayerRace, cvPoint(259, 84), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);
			putText(img, p->m_CharPlayerBackground, cvPoint(355, 58), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_ExperiencePoints), cvPoint(470, 82), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);
			putText(img, p->m_CharAlignment, cvPoint(347, 83), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);

			for (int i = 0; i < p->m_SavingThrows.size(); i++)
			{

				if (p->m_SavingThrows[i] == "Strength")
				{
					circle(img, cvPoint(98, 198), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_SavingThrows[i] == "Dexterity")
				{
					circle(img, cvPoint(98, 212), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_SavingThrows[i] == "Constitution")
				{
					circle(img, cvPoint(98, 224), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_SavingThrows[i] == "Intelligence")
				{
					circle(img, cvPoint(98, 237), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_SavingThrows[i] == "Wisdom")
				{
					circle(img, cvPoint(98, 250), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_SavingThrows[i] == "Charisma")
				{
					circle(img, cvPoint(98, 263), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
			}

			for (int i = 0; i < p->m_Skill.size(); i++)
			{
				if (p->m_Skill[i] == "acrobatics")
				{
					circle(img, cvPoint(98, 307), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "animal_handling")
				{
					circle(img, cvPoint(98, 320), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "arcana")
				{
					circle(img, cvPoint(98, 333), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "athletics")
				{
					circle(img, cvPoint(98, 346), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "deception")
				{
					circle(img, cvPoint(98, 359), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "history")
				{
					circle(img, cvPoint(98, 372), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "insight")
				{
					circle(img, cvPoint(98, 386), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "intimidation")
				{
					circle(img, cvPoint(98, 399), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "investigation")
				{
					circle(img, cvPoint(98, 412), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "medicine")
				{
					circle(img, cvPoint(98, 425), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "nature")
				{
					circle(img, cvPoint(98, 438), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "perception")
				{
					circle(img, cvPoint(98, 451), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "performance")
				{
					circle(img, cvPoint(98, 464), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "persuasion")
				{
					circle(img, cvPoint(98, 477), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "religion")
				{
					circle(img, cvPoint(98, 790), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "sleight_of_hand")
				{
					circle(img, cvPoint(98, 803), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "stealth")
				{
					circle(img, cvPoint(98, 816), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
				if (p->m_Skill[i] == "survival")
				{
					circle(img, cvPoint(98, 829), 4, Scalar(0, 0, 0), CV_FILLED, 8, 0);
				}
			}
			putText(img, std::to_string(p->m_Acrobatics), cvPoint(109, 309), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_AnimalHandling), cvPoint(109, 322), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Arcana), cvPoint(109, 334), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Athletics), cvPoint(109, 346), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Deception), cvPoint(109, 360), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_History), cvPoint(109, 372), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Insight), cvPoint(109, 385), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Intimidation), cvPoint(109, 397), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Investigation), cvPoint(109, 411), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Medicine), cvPoint(109, 423), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Nature), cvPoint(109, 435), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Perception), cvPoint(109, 449), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Performance), cvPoint(109, 461), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Persuasion), cvPoint(109, 474), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Religion), cvPoint(109, 487), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_SleightOfHand), cvPoint(109, 499), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Stealth), cvPoint(109, 511), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_Survival), cvPoint(109, 525), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);

			putText(img, std::to_string(p->m_Speed), cvPoint(330, 155), FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_ArmorClass), cvPoint(221, 152), FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_DexterityBonus), cvPoint(275, 159), FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_ProficiencyBonus), cvPoint(97, 170), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(10 + p->m_WisdomBonus), cvPoint(30, 568), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, LINE_AA);

			putText(img, std::to_string(p->m_HitPointsCurrent), cvPoint(234, 225), FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 0), 1, LINE_AA);
			putText(img, std::to_string(p->m_HitDice + p->m_ConstitutionBonus), cvPoint(290, 193), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
			

			int t = 387;
			for (int i = 0; i < p->m_Traits.size(); i++)
			{
				putText(img, p->m_Traits[i], cvPoint(396, t), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
				t += 13;
			}
			for (int i = 0; i < p->m_Feature.size(); i++)
			{
				putText(img, p->m_Feature[i], cvPoint(396, t), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
				t += 13;
			}

			t = 606;
			for (int i = 0; i < p->m_Tools.size(); i++)
			{
				putText(img, p->m_Tools[i], cvPoint(40, t), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
				t += 13;
			}
			for (int i = 0; i < p->m_Armor.size(); i++)
			{
				putText(img, p->m_Armor[i], cvPoint(40, t), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
				t += 13;
			}
			for (int i = 0; i < p->m_Weapons.size(); i++)
			{
				putText(img, p->m_Weapons[i], cvPoint(40, t), FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 0), 1, LINE_AA);
				t += 13;
			}

			imwrite("image-" + std::to_string(br) + ".jpg", img);
			auto& ent(manager.addEntity());
			ent.addComponent<TransformComponent>(577, 760, 764, 577, 1);
			ent.addComponent<SpriteComponent>(("image-" + std::to_string(br) + ".jpg").c_str());
			ent.addGroup(groupChSheets);
			br++;
		}
		for (int i = 0; i < playersVec.size(); i++)
		{
			playerPos.push_back(vec2(575 + i * 55, 575));
		}
	}
	else { isRunning = false; }
}

auto& tiles(manager.getGroup(Application::groupMap));
auto& players(manager.getGroup(Application::groupPlayers));
auto& enemies(manager.getGroup(Application::groupEnemies));
auto& pages(manager.getGroup(Application::groupPages));
auto& pages2(manager.getGroup(Application::groupPages2));
auto& grid(manager.getGroup(Application::groupGrid));
auto& genetatedMap(manager.getGroup(Application::groupGeneratedMap));
auto& ai(manager.getGroup(Application::groupAI));
auto& playerVis(manager.getGroup(Application::groupPlayerVisualization));
auto& text(manager.getGroup(Application::groupText));
auto& sheets(manager.getGroup(Application::groupChSheets));
auto& navBar(manager.getGroup(Application::groupNavBar));
auto& rolls(manager.getGroup(Application::groupRolls));

bool playerVisMenu = true;
bool movement = false;
bool createMonsterMenu = false;

int T = dest.x;
void Application::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEWHEEL:
		iWheelX = event.wheel.x;
		iWheelY = event.wheel.y;
		if (iWheelY < 0)
		{
			
			iWheelY = 0;
		}
		if (iWheelY > 0)
		{
			iWheelY = 0;
		}
		iWheelY = 0;
		
		break;

	default:
		break;
	}
	if (Application::event.type == SDL_KEYDOWN)
	{
		if (selected == 3)
		{
		T = dest.x;
		switch (Application::event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			 setDestXto -= 5; 
			break;
		case SDLK_LEFT:
			for (auto& p : playersVec)
			{
				T += 276;
			}
			
			if (setDestXto * 10 < T + dest.x) { setDestXto += 5; }
			break;
		default:
			break;
		}
		}
		if (selected == 4)
		{
			switch (Application::event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				map.getComponent<TransformComponent>().position.x -= 7;
				for (int i = 0; i < monstPos.size(); i++)
				{
					monstPos[i].x -= 7;
				}
				for (int i = 0; i < playerPos.size(); i++)
				{
					playerPos[i].x -= 7;
				}
				break;
			case SDLK_LEFT:
				if (map.getComponent<TransformComponent>().position.x <= 58)
				{
					map.getComponent<TransformComponent>().position.x += 7;
					for (int i = 0; i < monstPos.size(); i++)
					{
						monstPos[i].x += 7;
					}
					for (int i = 0; i < playerPos.size(); i++)
					{
						playerPos[i].x += 7;
					}
				}
				
				break;

			case SDLK_UP:
				if (map.getComponent<TransformComponent>().position.x <= -453) 
				{ 
					map.getComponent<TransformComponent>().position.y += 7; 
					for (int i = 0; i < monstPos.size(); i++)
					{
						monstPos[i].y += 7;
					}
					for (int i = 0; i < playerPos.size(); i++)
					{
						playerPos[i].y += 7;
					}
				}
				break;

			case SDLK_DOWN:
				if (map.getComponent<TransformComponent>().position.x <= -453)
				{
					map.getComponent<TransformComponent>().position.y -= 7;
					for (int i = 0; i < monstPos.size(); i++)
					{
						monstPos[i].y -= 7;
					}
					for (int i = 0; i < playerPos.size(); i++)
					{
						playerPos[i].y -= 7;
					}
				}
				break;
			default:
				break;
			}
			if (map.getComponent<TransformComponent>().position.x <= 58 && map.getComponent<TransformComponent>().position.x >= -453)
			{
				map.getComponent<TransformComponent>().position.y = 0;
			}
		}
	}
}
bool small = false;

const char* mapOptions[] = { "Free Draw","Generate Monster" };
int mapSelected = 0;

int page = 2;

bool MANUAL_PLAYER_UPDATE = false;
int BR = 0;

bool hidden = false;
bool slide = false;
bool oneTime = false;
bool rollHovered = false;

int playerSelected = 0;
int br = 0;
cv::Mat image;
int wI = 1154;

bool DRAW_GRID = true;

bool nextMonster = true;
int brMonster = 0;

std::string prd(const double x, const int decDigits) {
	std::stringstream ss;
	ss << std::fixed;
	ss.precision(decDigits); // set # places after decimal
	ss << x;
	return ss.str();
}

bool RightMouseDown()
{
	return SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2);
}

bool holdDown = false;
int movingMonst = -1;
int movingPlayer = -1;
bool onMonster = false;
int readingBook = -1;
int pageId = 50;

SDL_Texture *rolled;

bool firstClick = false;
vec2 attacking(-1, -1);
vec2 defending(-1, -1);
int a = 1;

ImVec4 clear_color = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
void Application::update()
{
	manager.refresh();
	manager.update();


	if (MAIN_MENU)
	{
		//hover
		SDL_GetMouseState(&x, &y);
		if (x >= 330 && x <= 760 && y >= 220 && y <= 290)
		{
			//home
			//navbar.getComponent<SpriteComponent>().texture = TextureManager::LoadTexture("database/NavBar/navBar-home.png");
			SetCursor(HandCursor);
			mainMenuBool[0] = true;

		}
		else
		{
			mainMenuBool[0] = false;
		}
		if (x >= 300 && x <= 760 && y >= 340 && y <= 405)
		{
			//Books
			//navbar.getComponent<SpriteComponent>().texture = TextureManager::LoadTexture("database/NavBar/navBar-books.png");
			SetCursor(HandCursor);
			mainMenuBool[1] = true;
		}
		else
		{
			
			mainMenuBool[1] = false;
		}
		if (x >= 335 && x <= 700 && y >= 445 && y <= 512)
		{
			//Rows
			SetCursor(HandCursor);
			mainMenuBool[2] = true;
		}
		else
		{
			mainMenuBool[2] = false;
		}
		
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&x, &y);
			if (x>= 300 && y >= 220 && x<=760 && y<=290)
			{
				MAIN_MENU = false;
			}
			if (x >= 335 && x <= 700 && y >= 445 && y <= 512)
			{
				//Rows
				clean();
			}
			break;

		default:
			break;
		}

	}
	else
	{
		if (createMonsterMenu)
		{
			if (nextMonster)
			{
				NAME = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", loadedMonsters[brMonster].m_MonsterName, vec3(255, 255, 255));
				CR = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "CR-" + prd(loadedMonsters[brMonster].m_CR, 1), vec3(255, 255, 255));
				SPEED = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "HitPoints-" + loadedMonsters[brMonster].m_HPstring, vec3(255, 255, 255));

				STATS = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "Strength- " + std::to_string(loadedMonsters[brMonster].m_Strength) + "\n" +
					"Dexterity- " + std::to_string(loadedMonsters[brMonster].m_Dexterity) + "\n" +
					"Constitution- " + std::to_string(loadedMonsters[brMonster].m_Constitution) + "\n" +
					"Intelligence- " + std::to_string(loadedMonsters[brMonster].m_Intelligence) + "\n" +
					"Wisdom- " + std::to_string(loadedMonsters[brMonster].m_Wisdom) + "\n" +
					"Charisma- " + std::to_string(loadedMonsters[brMonster].m_Charisma)
					, vec3(255, 255, 255));

				brMonster++;
				nextMonster = false;
			}

			SDL_GetMouseState(&x, &y);
			if (x >= 61 && x <= 150 && y >= 640 && y <= 640 +95)
			{
				SetCursor(HandCursor);
			}
			if (x >= 170 && x <= 170 + 80 && y >= 640 && y <= 640 + 95)
			{
				SetCursor(HandCursor);
			}
			if (x >= 836 && x <= 1120 + 80 && y >= 535  + 90 && y <= 617 + 100)
			{
				SetCursor(HandCursor);
			}


			switch (event.type) 
			{
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&x, &y);

					if (x >= 170 && x <= 170 + 80 && y >= 640 && y <= 640 + 95)
					{
						if (brMonster < loadedMonsters.size())
						{
							brMonster++;
							NAME = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", loadedMonsters[brMonster].m_MonsterName, vec3(255, 255, 255));
							CR = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "CR-" + prd(loadedMonsters[brMonster].m_CR, 1), vec3(255, 255, 255));
							SPEED = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "HitPoints-" + loadedMonsters[brMonster].m_HPstring, vec3(255, 255, 255));
							STATS = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "Strength- " + std::to_string(loadedMonsters[brMonster].m_Strength) + "\n" +
								"Dexterity- " + std::to_string(loadedMonsters[brMonster].m_Dexterity) + "\n" +
								"Constitution- " + std::to_string(loadedMonsters[brMonster].m_Constitution) + "\n" +
								"Intelligence- " + std::to_string(loadedMonsters[brMonster].m_Intelligence) + "\n" +
								"Wisdom- " + std::to_string(loadedMonsters[brMonster].m_Wisdom) + "\n" +
								"Charisma- " + std::to_string(loadedMonsters[brMonster].m_Charisma)
								, vec3(255, 255, 255));
							SDL_Delay(90);
						}
					}
					if (x >= 61 && x <= 150 && y >= 640 && y <= 640 + 95)
					{
						if (brMonster != 0)
						{

							brMonster--;

							NAME = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", loadedMonsters[brMonster].m_MonsterName, vec3(255, 255, 255));
							CR = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "CR-" + prd(loadedMonsters[brMonster].m_CR, 1), vec3(255, 255, 255));
							SPEED = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "HitPoints-" + loadedMonsters[brMonster].m_HPstring, vec3(255, 255, 255));
							STATS = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", "Strength- " + std::to_string(loadedMonsters[brMonster].m_Strength) + "\n" +
								"Dexterity- " + std::to_string(loadedMonsters[brMonster].m_Dexterity) + "\n" +
								"Constitution- " + std::to_string(loadedMonsters[brMonster].m_Constitution) + "\n" +
								"Intelligence- " + std::to_string(loadedMonsters[brMonster].m_Intelligence) + "\n" +
								"Wisdom- " + std::to_string(loadedMonsters[brMonster].m_Wisdom) + "\n" +
								"Charisma- " + std::to_string(loadedMonsters[brMonster].m_Charisma)
								, vec3(255, 255, 255));
							SDL_Delay(90);
						}
					}
					if (x >= 836 && x <= 1120 + 80 && y >= 535 + 90 && y <= 617 + 100)
					{
						Monsters::Monster monst = loadedMonsters[brMonster];
						mapMonsters.push_back(&monst);
						monstPos.push_back(vec2(575, 575));
						createMonsterMenu = false;
					}
					break;
				}
			default:
				break;
			}
		}
		else
		{
			if (selected == 3 && movement == true)
			{
				if (dest.x > 70)
				{
					dest.x -= 15;
				}
				if (dest.x < 70)
				{
					dest.x = 70;
				}
				sheets[visPlayer]->getComponent<TransformComponent>().position.y -= 40;
				if (sheets[visPlayer]->getComponent<TransformComponent>().position.y < 0)
				{
					sheets[visPlayer]->getComponent<TransformComponent>().position.y = 0;
				}
				if (dest.x <= 70 && sheets[visPlayer]->getComponent<TransformComponent>().position.y <= 0)
				{
					movement = false;
				}
			}
			if (selected == 3)
			{
				if (playerVisMenu)
				{
					switch (event.type) {
					case SDL_MOUSEBUTTONDOWN:
						if (event.button.button == SDL_BUTTON_LEFT)
						{
							SDL_GetMouseState(&x, &y);
							for (int i = 0; i < playersVec.size(); i++)
						{
							if (i == 0 && y >= 0 && y <= 385 && x >= 0 && x <= 266 && setDestXto == 70)
							{

								visPlayer = 0;
								src.x = src.y = 0;
								dest.x = 0;
								dest.y = 50;
								movement = true;
								src.h = dest.h = 385;
								src.w = dest.w = 266;
								playerVisMenu = false;
							}
							if (i == 0 && y >= 0 && y <= 385 && x >= 0 + setDestXto && x <= 266 + setDestXto && setDestXto == 70)
							{

								visPlayer = 0;
								src.x = src.y = 0;
								dest.x = 0;
								dest.y = 50;
								movement = true;
								src.h = dest.h = 385;
								src.w = dest.w = 266;
								playerVisMenu = false;
							}

							if (i == 0 && y >= 0 && y <= 385 && x >= 0 + setDestXto && x <= 266 + setDestXto && setDestXto < 70)
							{
								visPlayer = i;
								src.x = src.y = 0;
								dest.x = 266 * i;
								movement = true;
								dest.y = 50;
								src.h = dest.h = 385;
								src.w = dest.w = 266;
								playerVisMenu = false;
							}
							if (i != 0 && y >= 0 && y <= 385 && x >= 266 * i + setDestXto && x <= i * 266 + 266 + 10 * i + setDestXto && setDestXto < 70)
							{
								visPlayer = i;
								src.x = src.y = 0;
								dest.x = 266 * i;
								movement = true;
								dest.y = 50;
								src.h = dest.h = 385;
								src.w = dest.w = 266;
								playerVisMenu = false;
							}

						}
							break;

						}
					}
				}
				else
				{
					{
						switch (event.type) {
						case SDL_MOUSEBUTTONDOWN:
							if (event.button.button == SDL_BUTTON_LEFT)
							{
							
								SDL_GetMouseState(&x, &y);
								if (y >= 0 && y <= 88 && x >= 978 + 88 && x <= 978 + 88 + 88)
								{
									sheets[visPlayer]->getComponent<TransformComponent>().position.y = 760;
									visPlayer = -1;
									playerVisMenu = true;

								}
							}
							break;
						}
					}
				}
			}
			if (selected == 2)
			{
				SDL_GetMouseState(&x, &y);
				if (x >= 290 && x <= 334 && y >= 133 - 50 && y <= 171 - 50) { SetCursor(HandCursor); }
				if (x >= 290 && x <= 334 && y >= 216 - 50 && y <= 260 - 50) { SetCursor(HandCursor); }
				if (x >= 290 && x <= 334 && y >= 302 - 50 && y <= 347 - 50) { SetCursor(HandCursor); }
				if (x >= 290 && x <= 334 && y >= 386 - 50 && y <= 435 - 50) { SetCursor(HandCursor); }
				if (x >= 290 && x <= 334 && y >= 474 - 50 && y <= 521 - 50) { SetCursor(HandCursor); }
				if (x >= 290 && x <= 334 && y >= 549 - 50 && y <= 589 - 50) { SetCursor(HandCursor); }
				if (x >= 290 && x <= 334 && y >= 626 - 50 && y <= 670 - 50) { SetCursor(HandCursor); }
				if( x >= 645 && x <= 940 && y >= 575 && y <= 650){ SetCursor(HandCursor); rollHovered = true; }
				else { rollHovered = false; }

				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:

					SDL_GetMouseState(&x, &y);
					if (x >= 290 && x <= 334 && y >= 133-50 && y <= 171-50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 146 - 50;
					}
					if (x >= 290 && x <= 334 && y >= 216 - 50 && y <= 260 - 50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 223 - 50;
					}
					if (x >= 290 && x <= 334 && y >= 302 - 50 && y <= 347 - 50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 310 - 50;
					}
					if (x >= 290 && x <= 334 && y >= 386 - 50 && y <= 435 - 50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 398 - 50;
					}
					if (x >= 290 && x <= 334 && y >= 474 - 50 && y <= 521 - 50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 481 - 50;
					}
					if (x >= 290 && x <= 334 && y >= 509 - 50 && y <= 589 - 50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 555 - 50;
					}
					if (x >= 290 && x <= 334 && y >= 626 - 50 && y <= 670 - 50)
					{
						rolls_dragon.getComponent<TransformComponent>().position.y = 632 - 50;
					}
					if (x >= 645 && x <= 940 && y >= 575 && y <= 650)
					{
						switch (rolls_dragon.getComponent<TransformComponent>().position.y)
						{
						case 760:
							break;
						case 146 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(4)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						case 223 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(6)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						case 310 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(8)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						case 398 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(10)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						case 481 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(12)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						case 555 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(20)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						case 632 - 50:
							rolled = TextureManager::LoadFont("database/Fonts/TimesNewRoman.ttf", std::to_string(random_numberHardware(100)), vec3(255, 255, 255));
							SDL_Delay(125);
							break;
						default:
							break;
						}
					}
					break;
				default:
					break;
				}
				
			}
			if (selected == 1)
			{
				SDL_GetMouseState(&x, &y);
				if (x >= 123 && x <= 478 && y >= 488 && y <= 555)
				{
					SetCursor(HandCursor);
					booksBool[0] = true;
				}
				else
				{
					booksBool[0] = false;
				}
				if (x >= 720 && x <= 973 && y >= 200 && y <= 255)
				{
					SetCursor(HandCursor);
					booksBool[1] = true;
				}
				else
				{
					booksBool[1] = false;
				}
				if (x >= 695 && x <= 1000 && y >= 274 && y <= 335)
				{
					//Rows
					SetCursor(HandCursor);
					booksBool[2] = true;
				}
				else
				{
					booksBool[2] = false;
				}


				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:

					if (x >= 123 && x <= 478 && y >= 488 && y <= 555)
					{
						system("start https://www.youtube.com/watch?v=PdGi5g2eatk");
					}
					if (x >= 720 && x <= 973 && y >= 200 && y <= 255)
					{
						if (dirExists("database/Books/Rule"))
						{
							system("start database/Books/Rule/DnD_BasicRules_2018.pdf");

						}
					}
					if (x >= 695 && x <= 100 && y >= 280 && y <= 335)
					{
						
					}
					break;
				default:
					break;
				}
			}
			if (selected == 4)
			{
				SDL_GetMouseState(&x, &y);
				if (map.getComponent<TransformComponent>().position.x == 65)
				{

					if (x >= 155 && x <= 415 && y >= 400 && y <= 466)
					{
						SetCursor(HandCursor);
						mapBool[0] = true;
					}
					else
					{
						mapBool[0] = false;
					}
					if (x >= 160 && x <= 415 && y >= 490 && y <= 588)
					{
						SetCursor(HandCursor);
						mapBool[1] = true;
					}
					else
					{
						mapBool[1] = false;
					}

				}
				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{

						SDL_GetMouseState(&x, &y);
						if (x >= 155 && x <= 415 && y >= 400 && y <= 466)
						{
							SetCursor(HandCursor);
							DRAW_GRID = !DRAW_GRID;
							SDL_Delay(125);
							mapBool[0] = true;
						}
						if (x >= 160 && x <= 415 && y >= 490 && y <= 588)
						{
							SetCursor(HandCursor);
							createMonsterMenu = true;
							mapBool[1] = true;
						}
						if (movingMonst == -1)
						{
							for (int i = 0; i < monstPos.size(); i++)
							{
								if (x >= monstPos[i].x && x <= monstPos[i].x + 55 && y >= monstPos[i].y && y <= monstPos[i].y + 55)
								{
									holdDown = true;
									movingMonst = i;
								}
							}
						}
						if (movingPlayer == -1)
						{
							for (int i = 0; i < playerPos.size(); i++)
							{
								if (x >= playerPos[i].x && x <= playerPos[i].x + 55 && y >= playerPos[i].y && y <= playerPos[i].y + 47)
								{
									holdDown = true;
									movingPlayer = i;
								}
							}
						}
						holdDown = true;
						break;

					}
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						SDL_GetMouseState(&x, &y);
						if (firstClick == false)
						{
							SDL_Delay(125);
							for (int i = 0; i < playerPos.size(); i++)
							{
								if (x >= playerPos[i].x && x <= playerPos[i].x + 55 && y >= playerPos[i].y && y <= playerPos[i].y + 47)
								{
									attacking.x = 1;
									attacking.y = i;
									firstClick = true;
								}
							}
							for (int i = 0; i < monstPos.size(); i++)
							{
								if (x >= monstPos[i].x && x <= monstPos[i].x + 55 && y >= monstPos[i].y && y <= monstPos[i].y + 47)
								{
									attacking.x = 2;
									attacking.y = i;
									firstClick = true;
								}
							}
							firstClick = true;
							
						}	
						else if (firstClick == true)
						{
							SDL_Delay(125);
							for (int i = 0; i < playerPos.size(); i++)
							{
								if (x >= playerPos[i].x && x <= playerPos[i].x + 55 && y >= playerPos[i].y && y <= playerPos[i].y + 47)
								{
									defending.x = 1;
									defending.y = i;
									firstClick = false;

									if (attacking.x == 1 && defending.x == 1)
									{
										std::cout << playersVec[defending.y]->m_HitPoints << std::endl;
										CombatSystem::attack(playersVec[attacking.y], playersVec[defending.y], &weapons[0]);
										std::cout << playersVec[defending.y]->m_HitPoints << std::endl;
									}
									if (attacking.x == 1 && defending.x == 2)
									{
										CombatSystem::attack(playersVec[attacking.y], &loadedMonsters[defending.y], &weapons[0]);
									}
									if (attacking.x == 2 && defending.x == 1)
									{
										CombatSystem::attack(&loadedMonsters[attacking.y], playersVec[defending.y], &weapons[0]);
									}
									if (attacking.x == 2 && defending.x == 2)
									{
										CombatSystem::attack(&loadedMonsters[attacking.y], &loadedMonsters[defending.y], &weapons[0]);
									}
								}
							}
							for (int i = 0; i < monstPos.size(); i++)
							{
								if (x >= monstPos[i].x && x <= monstPos[i].x + 55 && y >= monstPos[i].y && y <= monstPos[i].y + 47)
								{
									defending.x = 2;
									defending.y = i;
									firstClick = false;
								}
							}
							
						}
						/*if (oneTimeClick)
						{
							oneTimeClick = false;
						}*/
					}
				case SDL_MOUSEBUTTONUP:
					
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						holdDown = false;
						movingMonst = -1;
						movingPlayer = -1;
					}

					
					break;
				default:
					break;
				}
				
				if (movingMonst != -1 && holdDown == true && createMonsterMenu == false)
				{
					SDL_GetMouseState(&x, &y);
					monstPos[movingMonst].x = x - 20;
					monstPos[movingMonst].y = y - 20;
					
				}
				if (movingPlayer != -1 && holdDown == true && createMonsterMenu == false)
				{
					SDL_GetMouseState(&x, &y);
					playerPos[movingPlayer].x = x - 20;
					playerPos[movingPlayer].y = y - 20;

				}
		}

			//navbar
			SDL_GetMouseState(&x, &y);
			if (x >= 0 && x <= 65 && y >= 100 && y <= 146)
			{
				//home
				//navbar.getComponent<SpriteComponent>().texture = TextureManager::LoadTexture("database/NavBar/navBar-home.png");
				SetCursor(HandCursor);
				menu[0] = true;
			}
			else
			{
				menu[0] = false;
			}
			if (x >= 0 && x <= 65 && y >= 155 && y <= 206)
			{
				//Books
				//navbar.getComponent<SpriteComponent>().texture = TextureManager::LoadTexture("database/NavBar/navBar-books.png");
				SetCursor(HandCursor);
				menu[1] = true;
			}
			else
			{
				menu[1] = false;
			}
			if (x >= 0 && x <= 65 && y >= 220 && y <= 276)
			{
				//Rows
				SetCursor(HandCursor);
				menu[2] = true;
			}
			else
			{
				menu[2] = false;
			}
			if (x >= 0 && x <= 65 && y >= 288 && y <= 355)
			{
				//Player Selected
				SetCursor(HandCursor);
				menu[3] = true;
			}
			else
			{
				menu[3] = false;
			}
			if (x >= 0 && x <= 65 && y >= 348 && y <= 401)
			{
				//Map
				SetCursor(HandCursor);
				menu[4] = true;
			}
			else
			{
				menu[4] = false;
			}

			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (x >= 0 && x <= 65 && y >= 100 && y <= 146)
				{
					//home
					selected = 0;
				}
				if (x >= 0 && x <= 65 && y >= 155 && y <= 206)
				{
					//Books
					selected = 1;
				}
				if (x >= 0 && x <= 65 && y >= 220 && y <= 276)
				{
					//Rows
					selected = 2;
				}
				if (x >= 0 && x <= 65 && y >= 288 && y <= 355)
				{
					//Player Selected
					selected = 3;
				}
				if (x >= 0 && x <= 65 && y >= 348 && y <= 401)
				{
					//Map
					selected = 4;
				}
				break;
			default:
				break;
			}

			if (!playersVec.empty())
			{
				for (auto& p : playersVec)
				{
					p->update();
				}
			}
		}
	//server->update();
	//if (MANUAL_PLAYER_UPDATE) { player->update(); }

	}
}


static const char* list[] = { "Home", "Books", "Rows", "View Player", "Map" };

int ROw = 0;

SDL_Rect srcM, destM;
SDL_Rect SrcRect, DestRect;
SDL_Rect srcRoll, destRoll;

void Application::render()
{
	SDL_RenderClear(renderer);

	if (MAIN_MENU)
	{
		if (mainMenuBool[0])
		{
			mainMenuStart.getComponent<SpriteComponent>().draw();
		}
		if (mainMenuBool[1])
		{
			mainMenuContinue.getComponent<SpriteComponent>().draw();
		}
		if (mainMenuBool[2])
		{
			mainMenuExit.getComponent<SpriteComponent>().draw();
		}
		if (mainMenuBool[0] != true && mainMenuBool[1] != true && mainMenuBool[2] != true)
		{
			mainMenu.getComponent<SpriteComponent>().draw();
		}
	}
	else
	{
		if (createMonsterMenu)
		{
			monstersMenu.draw();

			srcM.x = 0;
			srcM.y = 0;

			SDL_QueryTexture(NAME, NULL, NULL, &srcM.w, &srcM.h);
			destM.w = srcM.w;
			destM.h = srcM.h;

			destM.x = 110;
			destM.y = 70;
			SDL_RenderCopy(renderer, NAME, &srcM, &destM);

			SDL_QueryTexture(CR, NULL, NULL, &srcM.w, &srcM.h);
			destM.w = srcM.w;
			destM.h = srcM.h;

			destM.x = 88;
			destM.y = 187;
			SDL_RenderCopy(renderer, CR, &srcM, &destM);


			SDL_QueryTexture(SPEED, NULL, NULL, &srcM.w, &srcM.h);
			destM.w = srcM.w;
			destM.h = srcM.h;

			destM.x = 260;
			destM.y = 187;
			SDL_RenderCopy(renderer, SPEED, &srcM, &destM);

			SDL_QueryTexture(STATS, NULL, NULL, &srcM.w, &srcM.h);
			destM.w = srcM.w;
			destM.h = srcM.h;

			destM.x = 90;
			destM.y = 390;
			SDL_RenderCopy(renderer, STATS, &srcM, &destM);
		}
		else
		{

			for (auto& t : tiles)
			{
				if (selected == 0 && selected != 4) { t->draw(); }

			}
			
			if (selected == 4)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				if (mapBool[0])
				{
					map_grid.getComponent<SpriteComponent>().draw();
				}
				if (mapBool[1])
				{
					map_create.getComponent<SpriteComponent>().draw();
				}
				if (mapBool[0] != true && mapBool[1] != true)
				{
					map.getComponent<SpriteComponent>().draw();
				}

				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
				if (firstClick == true)
				{
					SDL_GetMouseState(&x, &y);
					if (attacking.x == 1)
					{
						SDL_RenderDrawLine(renderer, x, y, playerPos[attacking.y].x + 25, playerPos[attacking.y].y + 25);
					}	
					if (attacking.x == 2)
					{
						SDL_RenderDrawLine(renderer, x, y, monstPos[attacking.y].x + 25, monstPos[attacking.y].y + 25);
					}
				}
			}
			if (selected == 1)
			{
				if (booksBool[0])
				{
					books_download.getComponent<SpriteComponent>().draw();
				}
				if (booksBool[1])
				{
					books_rule.getComponent<SpriteComponent>().draw();
				}
				if (booksBool[2])
				{
					books_camp.getComponent<SpriteComponent>().draw();
				}
				if (booksBool[0] != true && booksBool[1] != true && booksBool[2] != true)
				{
					books.getComponent<SpriteComponent>().draw();
				}
			}
			
				if (selected == 4 && !mapMonsters.empty())
				{
					for (int i = 0; i < monstPos.size(); i++)
					{

						SrcRect.x = SrcRect.y = 0;
						SrcRect.w = SrcRect.h = DestRect.w = DestRect.h = 55;
						DestRect.x = monstPos[i].x;
						DestRect.y = monstPos[i].y;
						SDL_RenderCopyEx(renderer, monsterIcon, &SrcRect, &DestRect, NULL, NULL, SDL_FLIP_NONE);			
					}
				}
				if (selected == 4 && !playersVec.empty())
				{
					for (int i = 0; i < playerPos.size(); i++)
					{
						
						SrcRect.x = SrcRect.y = 0;
						SrcRect.w = 111;
						SrcRect.h = 95;

						DestRect.w = 55;
						DestRect.h = 47;

						DestRect.x = playerPos[i].x;
						DestRect.y = playerPos[i].y;

						SDL_RenderCopyEx(renderer, playersVec[i]->m_MapIcon, &SrcRect, &DestRect, NULL, NULL, SDL_FLIP_NONE);					
					}
				}
				
			if (selected == 2)
			{
				rolls_backgr.draw();
				if (rollHovered)
				{
					rolls_hovered.getComponent<SpriteComponent>().draw();
				}
				else
				{
					rolls_menu.getComponent<SpriteComponent>().draw();
				}

				rolls_dragon.getComponent<SpriteComponent>().draw();

				if (rolls_dragon.getComponent<TransformComponent>().position.y != 760)
				{
					srcRoll.x = srcRoll.y = 0;
					SDL_QueryTexture(rolled, NULL, NULL, &srcRoll.w, &srcRoll.h);
					destRoll.w = srcRoll.w * 2,5;
					destRoll.h = srcRoll.h * 2,5;


					destRoll.x = 750;
					destRoll.y = 290;
					SDL_RenderCopy(renderer, rolled, &srcRoll, &destRoll);
				}
			}
			if (selected == 4)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				if (DRAW_GRID)
				{
					
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					for (int i = map.getComponent<TransformComponent>().position.x + 465+45; i <= map.getComponent<TransformComponent>().position.x + 769 + 3000; i += 55)
					{
						SDL_RenderDrawLine(renderer, i, map.getComponent<TransformComponent>().position.y - 20, i, 3000);

					}
					for (int i = map.getComponent<TransformComponent>().position.y - 20; i <= map.getComponent<TransformComponent>().position.x + 769 + 3000; i += 55)
					{
						SDL_RenderDrawLine(renderer, map.getComponent<TransformComponent>().position.x + 465 + 45, i, 3000, i);
					}
				}
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}
				
			
			if (selected == 3)
			{
				for (auto& v : playerVis)
				{
					v->draw();
				}
				if (visPlayer != -1)
				{
					playerVisualizationBackground2.draw();
					SDL_RenderCopy(renderer, playersVec[visPlayer]->m_Representation, &src, &dest);
				}
				if (playerVisMenu)
				{
					playerVisualizationBackground.draw();
					src.x = src.y = 0;
					dest.x = setDestXto;
					src.h = dest.h = 385;
					src.w = dest.w = 266;
					for (auto& p : playersVec)
					{
						SDL_RenderCopy(renderer, p->m_Representation, &src, &dest);
						dest.x += 276;
					}
				}
			}
			for (int i = 0; i < sheets.size(); i++)
			{
				if (selected == 3 && i == visPlayer)
				{
					sheets[i]->draw();
				}
			}
			for (auto& c : pages2)
			{
				if (selected == 3 && playerVisMenu == false) { c->draw(); }
			}
			for (auto& c : pages)
			{
				if (readingBook == 1) { c->draw(); }
			}

			//navbar
			if (menu[0])
			{
				navbar_home.getComponent<SpriteComponent>().draw();
			}
			if (menu[1])
			{
				navbar_books.getComponent<SpriteComponent>().draw();
			}
			if (menu[2])
			{
				navbar_rolls.getComponent<SpriteComponent>().draw();
			}
			if (menu[3])
			{
				navbar_VP.getComponent<SpriteComponent>().draw();
			}
			if (menu[0] != true && menu[1] != true && menu[2] != true && menu[3] != true)
			{
				navbar.getComponent<SpriteComponent>().draw();
			}
			
		}
	}
	SDL_RenderPresent(renderer);
	//renderGui();
}

std::string temp = "";
static int row = 1;

int frame;

const char** playersName = new const char*[playersVec.size()];
bool leftMouseButtonDown = false;
bool vertex1 = false, vertex2 = false;
vec4 square;
int vertices[4];

void Application::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	isRunning = false;
	std::cout << "App Cleaned!" << std::endl;
}