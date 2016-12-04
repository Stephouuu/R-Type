#include "Application.hpp"

Application::Application(void)
	: _client("127.0.0.1", "4242")
{
	//sf::Vector2i reso(800, 480);
	std::pair<short, short> reso = StaticTools::GetResolution();

	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	_window.create(sf::VideoMode(reso.first, reso.second), "R-Type", sf::Style::Default, context);
	_window.setPosition(sf::Vector2i(0, 0));
	_window.setVerticalSyncEnabled(true);
}

Application::~Application(void)
{
	for (auto it : _controllers) {
		it.second->recycle();
		delete (it.second);
	}
}

//#include <Windows.h> // !
void Application::init(std::string host, std::string pwd)
{
  (void)host;
  (void)pwd;
	try {
		StaticTools::Log.open("client.log" /*+ std::to_string(GetCurrentProcessId()) + ".log"*/, std::ios::out | std::ios::app);
		ProjectResource::TheProjectResource.load();

		initIcon();
		initNetwork();
		initControllers();
		
		_fps.init();
		_inputHandler.init();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		throw (std::runtime_error(e.what()));
	}

	_timer.restart();
}

void Application::setState(State state)
{
	switch (state)
	{
	case State::ST_MainMenu:
		st_main_menu();
		break;
	case State::ST_Game:
		st_game();
		break;
	default:
	  break;
	}
}

// les �tats peuvent se changer d'eux m�me => � faire
void Application::loop(void)
{
	sf::Event event;
	float delta = 0;

	while (_window.isOpen())
	{
		delta = _timer.restart();

		while (_window.pollEvent(event))
		{
			_inputHandler.OnEvent(event);
			if (_inputHandler.isExiting()) {
				_client.disconnect();
				_window.close();
			}
		}

		_controllers.at((int)_fsm)->input(_inputHandler);
		_fps.update(delta);
		_controllers.at((int)_fsm)->update(delta);

		draw();
	}
}

void Application::initIcon(void)
{
	sf::Image image;

	if (!image.loadFromFile("./rsrc/sprites/icon.png")) {
		throw (std::runtime_error("can not load icon"));
	}
	_window.setIcon(128, 128, image.getPixelsPtr());
}

void Application::initNetwork(void)
{
	_client.connect();
	_client.run();
}

void Application::initControllers(void)
{
	//_fsm = State::ST_MainMenu;
	_fsm = State::ST_Game;

	GameController *game = new GameController(_client, "name", "pwd");
	_client.setGameController(game);

	_controllers[(int)State::ST_MainMenu] = new MainMenuController();
	_controllers[(int)State::ST_Game] = game;

	_controllers.at((int)_fsm)->init();
}

void Application::st_main_menu(void)
{
	_fsm = State::ST_MainMenu;
}

void Application::st_game(void)
{
	_fsm = State::ST_Game;
}

void Application::draw(void)
{
	_window.clear();

	_controllers.at((int)_fsm)->draw(_window);
	_fps.draw(_window); // !

	_window.display();
}
