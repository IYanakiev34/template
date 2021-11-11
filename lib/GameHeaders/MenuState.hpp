#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "GameHeaders/State.hpp"

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void updateOptionsText();

private:
	enum OptionNames
	{
		Play,
		Exit,
	};

private:
	sf::Sprite mBackgroundSprite;

	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;
};

#endif