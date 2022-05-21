#include "TopCard.h"


void TopCard::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}

void TopCard::refreshTopCard(gameManager* gm)
{
	sprite.setTexture(*gm->game->cardsPlayed->c->texture);
	printf("zmiana karty\n");

}