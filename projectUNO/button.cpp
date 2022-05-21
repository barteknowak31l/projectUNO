#include "button.h"
#include "gameManager.h"
#include "scene.h"



using namespace std;
using namespace sf;

set<Button*> Button::instances;



//ctor
Button::Button(Vector2f position, Texture *texture)
{
	if (getInstances().size()==0)
	{
		instances = std::set<Button*>();
	}


	sprite.setTexture(*texture);
	sprite.setPosition(position);
	sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	
	instances.insert(this);

	isActive = true;
	isVeilButton = false;
	isClicked = false;

	useCustomField = false;
	customField = sf::FloatRect(position, sf::Vector2f(0,0));

}

//copy ctor
Button::Button(const Button& other){

	sprite.setTexture(*other.sprite.getTexture());
	sprite.setPosition(other.sprite.getPosition());
	sprite.setOrigin(other.sprite.getOrigin());

	isActive = other.isActive;

	instances.insert(this);
}

//dtor
Button::~Button()
{
	instances.erase(this);
}

const std::set<Button*>& Button::getInstances()
{
	return instances;
}


void Button::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->sprite, state);
}

void Button::mouseInput(gameManager* gm,Event& event)
{
	for (Button* b : Button::getInstances())
	{
		if (b->isActive == false)
		{
			continue;
		}

		if (gm->sceneManager->gameUI->showVeil)
		{
			if (b->isVeilButton == false)
			{
				continue;
			}
		}


		//ruch myszki
		if (event.type == Event::MouseMoved)
		{

			if (b->useCustomField)
			{
				//porownaj pozycje
				if (b->customField.contains(Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					b->hovered = true;
				}
				else
				{
					b->hovered = false;
				}

			}
			else
			{
				//porownaj pozycje
				if (b->sprite.getGlobalBounds().contains(Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					b->hovered = true;
				}
				else
				{
					b->hovered = false;
				}
			}
		}

		//kilkniecie
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{

			if (b->useCustomField)
			{

				//porownaj pozycje
				if (b->customField.contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					b->onClick(gm);
					b->isClicked = true;
					b->hovered = false;
				}
				else
				{
					b->isClicked = false;
				}
			}
			else
			{
				//porownaj pozycje
				if (b->sprite.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					b->onClick(gm);
					b->hovered = false;
					b->isClicked = true;
				}
				else
				{
					b->isClicked = false;
				}
			}


		}
	}

}

void Button::update()
{
	for (Button* b : Button::getInstances())
	{
		if (b->hovered)
		{
			b->hover();
		}
		else
		{
			b->reset();
		}
	}
}


 void Button::hover()
 {
	 sprite.setColor(Color(180,180,180,255));
 }

 void Button::reset()
 {
	 sprite.setColor(Color::White);
 }


 void Button::setPos(sf::Vector2f position)
 {
	 sprite.setPosition(position);
	 sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2));
 }

 sf::Vector2f Button::getPos()
 {
	 return sprite.getPosition();
 }

 void Button::setActive(bool active)
 {
	 if (active)
	 { 

		isActive = true;
		//unsetHover();
		//unsetPressed();


	 }
	 else
	 {
		 unsetHover();
		 unsetPressed();
		 isActive = false;
	 }
 }