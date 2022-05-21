#pragma once
#ifndef BUTTON_C
#define BUTTON_C

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <set>

struct gameManager;




class Button: public sf::Drawable
{
protected:
	//zbior wskaznikow na wszystkie obiekty button
	static std::set<Button*> instances;
	bool pressed;
	bool hovered;

private:


	sf::Sprite sprite;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void hover();
	void reset();





public:
	Button() = delete;
	Button(sf::Vector2f position, sf::Texture *texture);
	Button(const Button& other);
	~Button();


	static void mouseInput(gameManager*, sf::Event& event);
	static void update();

	virtual void onClick(gameManager*)=0;

	static const std::set<Button*>& getInstances();

	bool isActive;

	bool isClicked;

	bool isVeilButton;

	bool useCustomField;
	sf::FloatRect customField;

	void setHover() { hovered = true; }
	void unsetHover() { hovered = false; }

	void setPressed() { pressed = true; };
	void unsetPressed() { pressed = false; }

	void setSprite(sf::Texture* texture) { sprite.setTexture(*texture); }
	sf::Sprite getSprite() {return sprite; }

	void setPos(sf::Vector2f possition);
	sf::Vector2f getPos();

	void setActive(bool);


};
#endif

