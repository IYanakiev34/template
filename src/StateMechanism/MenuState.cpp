#include "GameHeaders/MenuState.hpp"
#include "GameHeaders/ResourceHolder.hpp"
#include "GameHeaders/Util.hpp"

MenuState::MenuState(StateStack& stack, Context context) :
	State(stack, context),
	mOptions(),
	mOptionIndex(0)

{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

	updateOptionsText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	for (sf::Text& text : mOptions)
	{
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt)
{
	dt = sf::Time::Zero;
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{

	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		if (mOptionIndex > 0)
		{
			mOptionIndex--;
		}
		else
		{
			mOptionIndex = mOptions.size() - 1;
		}
		updateOptionsText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionsText();
	}

	return true;
}

void MenuState::updateOptionsText()
{
	if (mOptions.empty())
		return;

	// White all texts
	for (sf::Text& text : mOptions)
		text.setFillColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}