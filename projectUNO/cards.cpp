#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "utils.h"
#include <string.h>
#include <Windows.h>
#include "player.h"
//#include "mcts.h"


//////////////////////// TALIA KART ////////////////////////
//reprezentacja karty: 6,5 bit - id koloru , 4,3,2,1 bit - id wartosci
// /////////////////////////////////////////////////////////
// - kolory:		  id:
//			- czerwony  00
//			- niebieski 01
//			- zielony   10
//			- ¿ó³ty     11
// /////////////////////////////////////////////////////////
// - wartoœci 0-9:    id - reprezentacja binarna wartoœæi
// - stop			  id - 10bin
// - zmiana kierunku  id - 11bin
// - weŸ 2 karty	  id - 12bin
// - zmieñ kolor	  id - 13bin
// - zmieñ kolor +4   id - 14bin
// /////////////////////////////////////////////////////////
// - 1 sztuka karty o wartoœci 0 w ka¿dym kolorze
// - 2 sztuki kart o wartoœci 1-9 w ka¿dym kolorze
// - 2 sztuki kart stopu w ka¿dym kolorze
// - 2 sztuki kart zmiana kierunku w ka¿dym kolorze
// - 2 sztuki kart weŸ 2 karty w ka¿dym kolorze
// - 4 sztuki kart zmieñ kolor
// - 4 sztuki kart zmieñ kolor + 4
//UWAGA - karty zmieñ kolor i zmieñ kolor +4 NIE MAJ¥ KOLORU, pryjmujemy id koloru = 00
//przykladowe karty:
// 010011 - niebieska trójka
// 101100 - zielona weŸ 2 karty
// 001101 - zmieñ kolor


struct player;

struct game;

map<int, string>color_names{

    {red,"red"},
    {blue,"blue"},
    {green,"green"},
    {yellow,"yellow"}

};

map<int, string>value_names{
{0,"0"},
{1,"1"},
{2,"2"},
{3,"3"},
{4,"4"},
{5,"5"},
{6,"6"},
{7,"7"},
{8,"8"},
{9,"9"},
{stop,"stop"},
{changeDir,"changeDir"},
{draw2,"draw2"},
{changeCol,"changeCol"},
{changeColDraw4,"changeColDraw4"}
};

#pragma region STOS
unsigned int push(stack** s, card* c)
{
    if (*s == NULL) {
        *s = (stack*)malloc(sizeof(stack));
        (*s)->c = c;
        (*s)->next = NULL;
    }
    else {
        stack* newElement;
        newElement = (stack*)malloc(sizeof(stack));
        newElement->c = c;
        newElement->next = *s;
        *s = newElement;
    }

    return 1;
}

card* pop(stack** s)
{
    if (*s == NULL)
    {
        printf("cards::pop : error - stack is empty\n");
        return 0;
    }

    stack* tmp;
    card* c = (*s)->c;
    tmp = (*s)->next;
    free(*s);
    *s = tmp;

    return c;
}

int empty(stack* s)
{
    if (s == NULL)
        return 1;

    return 0;
}

int size(stack* s)
{
    int counter = 0;
    stack* current = s;

    while (current != NULL)
    {
        counter++;
        current = current->next;
    }

    return counter;
}

void show(stack* top) {

    int num = 1;
    printf("\n");
    if (top == NULL) printf("Stack is empty\n");
    else {
        stack* current = top;
        do {

            printf("%d.",num++);
            getCardFromId(current->c->id);

            current = current->next;
        } while (current != NULL);

    }
}

stack* createStack()
{
    stack* top = NULL;
    return top;
}

void destroyStack(stack** s)
{
    stack* tmp = *s;
    stack* previous = NULL;
    while (tmp != NULL)
    {
        if (previous != NULL)
        {
            free(previous);
        }
        previous = tmp;
        tmp = tmp->next;

    }

}

void reverseStack(stack** s)
{
    int siz = size(*s);
    stack* temp = createStack();

    for (int i = 0; i < siz; i++)
    {
        push(&temp, pop(s));
    }
    free(*s);
    
    *s = temp;
}

stack* stackCopy(stack** head)
{
    stack* newStack = createStack();
    stack* tmp = *head;

    while (tmp != NULL)
    {
        push(&newStack, tmp->c);
        tmp = tmp->next;
    }

    reverseStack(&newStack);

    return newStack;
}

#pragma endregion

#pragma region TALIA I KARTY
card* generateCard(int value, int color)
{
    int id = 0;
    id = id | color;
    id = id << 4;
    id = id | value;
    card* c = new card;
    c->id = id;
    return c;
}



void destroyCard(card* c)
{
    if(c!=NULL)
    delete c;
}

stack* generateStartingDeck()
{
    stack* deck = createStack();

    //dodaj karty z wartoœci¹ 0 - po jednej na kolor
    for (int color = red; color <= yellow; color++)
    {
        push(&deck, generateCard(0, color));
    }


    //dodaj karty z wartoœci¹ 1-9 - po dwie na kolor:
    for (int color = red; color <= yellow; color++)
    {
        for (int value = 1; value <= 9; value++)
        {
            push(&deck, generateCard(value, color));
            push(&deck, generateCard(value, color));
        }
    }

    //dodaj karty stop, zmiana kierunku, weŸ 2 - po dwie na kolor
    for (int color = red; color <= yellow; color++)
    {
        for (int value = stop; value <= draw2; value++)
        {
            push(&deck, generateCard(value, color));
            push(&deck, generateCard(value, color));
        }
    }

    //dodaj karty zmien kolor, zmien kolor +4 - 4 sztuki, id koloru 00
    for (int value = changeCol; value <= changeColDraw4; value++)
    {
        push(&deck, generateCard(value, 0));
        push(&deck, generateCard(value, 0));
        push(&deck, generateCard(value, 0));
        push(&deck, generateCard(value, 0));
    }
    return deck;

}

void getCardFromId(int id)
{
    //bits:
    // _ _ | _ _ _ _
    // col | value

    int v = id & 15;

    int c = id;
    c = c >> 4;

    printf("%s %s ", color_names[c].c_str(), value_names[v].c_str());

    printf("\n");

}

int getCardColorID(int id)
{
    int c = id;
    c = c >> 4;
    return c;

}

int getCardValueID(int id)
{
    int v = id & 15;
    return v;
}


void shuffle(stack** deck)
{
    if (*deck == NULL)
    {
        printf("cards::shuffle: error - stack is empty\n");
        return;
    }

    int deckSize = size(*deck);

    //zdejmij ze stosu i dodaj do listy
    int* positions = (int*)malloc(deckSize * sizeof(int));
    card** temp = (card**)malloc(deckSize * sizeof(card*));


    for (int i = 0; i < deckSize; i++)
    {
        positions[i] = i;
        temp[i] = pop(deck);
    }


    //wymieszaj positions
    int j = 0;
    for (int i = deckSize - 2; i > 0; i--)
    {
        j = randomInt(0, i);
        int tmp = positions[i+1];
        positions[i+1] = positions[j];
        positions[j] = tmp;
    }

    *deck = createStack();

    //poloz na stosie   
    for (int i = 0; i < deckSize; i++)
    {
        push(deck, temp[positions[i]]);
    }

}

void reshuffle(game *g)
{

    if (size(g->deck) > 0)
    {
        return;
    }
    
    printf("Reshuffling the deck...\n");



    if (g->cardsPlayed == NULL)
    {
        printf("cards::reshuffle: error - there are no cards played\n");
        return;
    }

    card* top = pop(&g->cardsPlayed);

    shuffle(&g->cardsPlayed);
    shuffle(&g->cardsPlayed);
    shuffle(&g->cardsPlayed);

    int s = size(g->cardsPlayed);

    card* tmp;

    for(int i =0; i<s;i++)
    {
        //push(&g->deck, pop(&g->cardsPlayed));
        tmp = pop(&g->cardsPlayed);
        if (getCardValueID(tmp->id) == 13)
        {
            tmp->texture = g->gm->textures->cardTextures->blackColor;
        }
        if (getCardValueID(tmp->id) == 14)
        {
            tmp->texture = g->gm->textures->cardTextures->blackColorPlus4;
        }
        push(&g->deck, tmp);


    }

    push(&g->cardsPlayed, top);


}

void putCardOnTop(game *g)
{
    if (g->deck == NULL)
    {
        printf("cards::putCardOnTop : error - no cards in deck!");
        return;
    }

    card* top=NULL;
    stack* temp = createStack();

    //sprawdzenie czy specjalna
    while (size(g->deck) > 0)
    {
        top = pop(&g->deck);
        if (!isCardSpecial(g,top))
        {
            break;
        }
        push(&temp, top);
    }

    //poloz nie specjalna na stosie cardsPlayed
    push(&g->cardsPlayed, top);

    //zwroc specjale do decku
    int siz = size(temp);
    for (int i = 0; i < siz; i++)
    {
        push(&g->deck, pop(&temp));
    }

}


#pragma region SPECJALNE
int isCardSpecial(game* g, card* c)
{
    int cardId = c->id;
  
    int cardVal = cardId & 15;

    //stop
    if (cardVal == 10)
    {
        specialStop(g);
        return 1;
    }

    //changeDir
    if (cardVal == 11)
    {
        specialChangeDir(g);
        return 1;
    }

    //draw2
    if (cardVal == 12)
    {
        specialDraw2(g);
        return 1;
    }

    //changeCol
    if (cardVal == 13)
    {
        specialChangeColor(g,c);
        return 2;
    }

    //changeCol +4
    if (cardVal == 14)
    {
        specialChangeColorDraw4(g,c);
        return 2;
    }

    //not special
    return 0;

}

int isBlackCard(card* c)
{
    int cardId = c->id;

    int cardVal = cardId & 15;

    //changeCol
    if (cardVal == 13)
    {
        return 1;
    }

    //changeCol +4
    if (cardVal == 14)
    {
        return 1;
    }

    return 0;


}

void specialStop(game* g)
{
    if (!g->gameStarted)
    {
        return;
    }

    //skips next player
   // nextTurn(g); powoduje blad jesli skip zostanie zagrane jako ostatnie - wtedy wygra kolejny gracz
    g->skipTurn = 1;
    printf("Player %d skips turn!\n", nextPlayerId(g));

}

void specialChangeDir(game* g)
{
    if (!g->gameStarted)
    {
        return;
    }
    //changes direction of play
    printf("Player %d skips changes the direction of play!\n", g->players[g->turn]->id);
    g->playDirection = g->playDirection *-1;
}

void specialDraw2(game* g)
{
    if (!g->gameStarted)
    {
        return;
    }

    //next player draws 2 cards

    drawCard(g,nextPlayerId(g));
    drawCard(g,nextPlayerId(g));

    g->players[nextPlayerId(g)]->uno=0;

    printf("Player %d draws 2 cards!\n", nextPlayerId(g));

}

void specialChangeColor(game* g, card* c)
{
    if (!g->gameStarted)
    {
        return;
    }

    int color = g->newColorOfCard;
    //printf("New color? 0 - red, 1 - blue, 2 - green, 3 - yellow\n");
   // scanf("%d", &color);

    int newID = 0;

    int oldValue = c->id & 15;

    newID = newID | color;
    newID = newID << 4;
    newID = newID | oldValue;

    getCardFromId(newID);


    if (getCardValueID(c->id) == 13) //change col
    {
        if (color == 0)
        {
            c->texture = g->gm->textures->cardTextures->blackColorRed;
        }
        if (color == 1)
        {
            c->texture = g->gm->textures->cardTextures->blackColorBlue;
        }
        if (color == 2)
        {
            c->texture = g->gm->textures->cardTextures->blackColorGreen;
        }
        if (color == 3)
        {
            c->texture = g->gm->textures->cardTextures->blackColorYellow;
        }
    }

    if (getCardValueID(c->id) == 14) //change col +4
    {
        if (color == 0)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4red;
        }
        if (color == 1)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4blue;
        }
        if (color == 2)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4green;
        }
        if (color == 3)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4yellow;
        }
    }


    c->id = newID;


}

void specialChangeColorDraw4(game* g, card* c)
{
    if (!g->gameStarted)
    {
        return;
    }

    specialChangeColor(g, c);
    specialDraw2(g);
    specialDraw2(g);

}

void AiSpecialChangeColor(game* g, card* c, int color)
{
    if (!g->gameStarted)
    {
        return;
    }


    int newID = 0;

    int oldValue = c->id & 15;

    newID = newID | color;
    newID = newID << 4;
    newID = newID | oldValue;

    getCardFromId(newID);

    if (getCardValueID(c->id) == 13) //change col
    {
        if (color == 0)
        {
            c->texture = g->gm->textures->cardTextures->blackColorRed;
        }
        if (color == 1)
        {
            c->texture = g->gm->textures->cardTextures->blackColorBlue;
        }
        if (color == 2)
        {
            c->texture = g->gm->textures->cardTextures->blackColorGreen;
        }
        if (color == 3)
        {
            c->texture = g->gm->textures->cardTextures->blackColorYellow;
        }
    }

    if (getCardValueID(c->id) == 14) //change col +4
    {
        if (color == 0)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4red;
        }
        if (color == 1)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4blue;
        }
        if (color == 2)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4green;
        }
        if (color == 3)
        {
            c->texture = g->gm->textures->cardTextures->blackColorPlus4yellow;
        }
    }


    c->id = newID;
}

void AiSpecialChangeColorDraw4(game* g, card* c,int color)
{
    if (!g->gameStarted)
    {
        return;
    }

    AiSpecialChangeColor(g, c,color);
    specialDraw2(g);
    specialDraw2(g);

}

#pragma endregion

#pragma endregion

