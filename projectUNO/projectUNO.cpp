#include <iostream>
#include "player.h"
#include "mcts.h"
#include "cards.h"
#include "utils.h"
#include "gameManager.h"
#include <windows.h>
#include <conio.h>
//sfml
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//UI
#include "HandDisplay.h"
#include "TopCard.h"
#include "button.h"
#include "PlayButton.h"
#include "ExitButton.h"
#include "IncrementButton.h"
#include "CheckboxButton.h"
#include "DrawCardButton.h"
#include "ChooseColorButton.h"
#include "YesNoButton.h"
#include "TextButton.h"
#include "scene.h"




void scenesSetup(gameManager* gm, HandDisplay* handDisplay);
void AITurn(game* g, gameManager*);
void humanTurn(game* g, HandDisplay* handDisplay, gameManager* gm);

void handDisplaySetup(HandDisplay* handDisplay, gameManager* gm);
void setTurnIndicator(gameManager* gm);
void setVeil(gameManager* gm);
void sortCurrentPlayerHandDisplay(gameManager* gm, HandDisplay* handDisplay);
void refreshAtTurnStart(gameManager* gm, HandDisplay* handDisplay);
void refreshTillNextTurn(gameManager* gm, HandDisplay* handDisplay);

void drawScene(gameManager* gm, HandDisplay* handDisplay, sf::RenderWindow &window);
void handleEvents(gameManager* gm, sf::Event event, sf::RenderWindow& window);

struct game;


using namespace std;

int main()
{
 
    gameManager* gm;
    gm = createGameManager();
 
    HandDisplay* handDisplay = new HandDisplay(710, 210, 80, 70);
    handDisplaySetup(handDisplay, gm);


    scenesSetup(gm,handDisplay);
    int lastScene = 0;

    int lastTurn = -1;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Uno! By Bartosz Nowak",sf::Style::Close);
    window.setIcon(gm->textures->icon->getSize().x, gm->textures->icon->getSize().y, gm->textures->icon->getPixelsPtr());
    window.setMouseCursor(*gm->textures->cursor);



    //timer mierzacy czas miedzy klatkami
    sf::Clock clock;
    bool refreshOnce = true;
    sf::Event event;

    while (window.isOpen())
    {
        //czas miedzy klatkami
        sf::Time elapsed = clock.restart();

        //exit
        if (gm->exitGame)
        {
            window.close();
        }

        //zmiana sceny
        if (lastScene != gm->sceneManager->currentScene)
        {
            lastScene = gm->sceneManager->currentScene;
            changeScene(gm, gm->sceneManager->currentScene,handDisplay);
        }


        //eventy
        while (window.pollEvent(event))
        {
            handleEvents(gm, event, window);
        }


        //DRAW SCENE
        drawScene(gm, handDisplay, window);


        //update klas button
        Button::update();

        //display
        window.display();


        //przerwa miedzy turami - wykonuje sie na koniec tury
        if (gm->currentWaitTime < gm->waitTime && gm->startTurn)
        {
            gm->currentWaitTime = gm->currentWaitTime + elapsed.asSeconds();
            if (refreshOnce)
            {
                refreshOnce = false;
                refreshTillNextTurn(gm, handDisplay);
            }
            Button::update();
            continue;
        }

        //NOWA TURA
        if (gm->game != NULL && gm->game->gameStarted)
        {
            if (gm->startTurn)
            {
                refreshOnce = true;
                refreshAtTurnStart(gm,handDisplay);
            }
        }

       

        if (gm->game != NULL && gm->game->gameStarted)
        {
            lastTurn = gm->game->turn;
        }

    }

    return 0;
}


void scenesSetup(gameManager* gm,HandDisplay* handDisplay)
{

    sf::Color bgColor = sf::Color(67, 58, 58, 255);


    //wypelnianie pol struktur
    //menu
    PlayButton* menuButton = new PlayButton(sf::Vector2f(300, 300), gm->textures->btn_play);
    ExitButton* exitButton = new ExitButton(sf::Vector2f(300, 700), gm->textures->btn_exit);
    sf::RectangleShape* background = new sf::RectangleShape(sf::Vector2f(600, 1200));
    background->setFillColor(bgColor);
    background->setPosition(0, 0);
    background->setOutlineColor(sf::Color::Black);
    background->setOutlineThickness(-5);

    sf::Sprite* logo = new sf::Sprite(*gm->textures->logo);
    logo->setPosition(sf::Vector2f(600,90 ));


    //setupMenu
    sf::RectangleShape* setupBg = new sf::RectangleShape(sf::Vector2f(1000, 1200));
    setupBg->setFillColor(bgColor);
    setupBg->setPosition(0, 0);
    setupBg->setOutlineColor(sf::Color::Black);
    setupBg->setOutlineThickness(-5);

    sf::Sprite* s_players_label = new sf::Sprite(*gm->textures->playersLabel);
    s_players_label->setPosition(20, 20);


    int *IncrementPointer = new int;
    IncrementPointer = &gm->playerCount;


    int* checkboxValue2 = new int;
    checkboxValue2 = &gm->playerType[1];
    int* checkboxValue3 = new int;
    checkboxValue3 = &gm->playerType[2];
    int* checkboxValue4 = new int;
    checkboxValue4 = &gm->playerType[3];


    IncrementButton* playersPlus = new IncrementButton(sf::Vector2f(600, 120), gm->textures->box_plus, 2, 4, 1, IncrementPointer);
    IncrementButton* playersMinus = new IncrementButton(sf::Vector2f(710, 120), gm->textures->box_minus, 2, 4, -1, IncrementPointer);


    sf::Sprite* s_player1_label = new sf::Sprite(*gm->textures->player1Label);
    s_player1_label->setPosition(20, 290);
    gm->player0text = new TextButton (sf::Vector2f(420, 340), gm->textures->emptyLabel,0);
    (*gm->player0text).textBox.setCharacterSize(36);
    (*gm->player0text).textBox.setFont(*gm->font);
    (*gm->player0text).textBox.setFillColor(sf::Color(212, 197, 10, 255));
    (*gm->player0text).textBox.setPosition(sf::Vector2f(320, 320));

    sf::Sprite* s_player2_label = new sf::Sprite(*gm->textures->player2Label);
    s_player2_label->setPosition(20, 480);

    
    gm->player1text = new TextButton(sf::Vector2f(420, 530), gm->textures->emptyLabel, 1);
    (*gm->player1text).textBox.setCharacterSize(36);
    (*gm->player1text).textBox.setFont(*gm->font);
    (*gm->player1text).textBox.setFillColor(sf::Color(212, 197, 10, 255));
    (*gm->player1text).textBox.setPosition(sf::Vector2f(320, 510));
    CheckboxButton* player2_checkbox = new CheckboxButton(sf::Vector2f(610, 530), gm->textures->box_human, checkboxValue2);

    sf::Sprite* s_player3_label = new sf::Sprite(*gm->textures->player3Label);
    s_player3_label->setPosition(20, 670);


    gm->player2text = new TextButton(sf::Vector2f(420, 720), gm->textures->emptyLabel, 2);
    (*gm->player2text).textBox.setCharacterSize(36);
    (*gm->player2text).textBox.setFont(*gm->font);
    (*gm->player2text).textBox.setFillColor(sf::Color(212, 197, 10, 255));
    (*gm->player2text).textBox.setPosition(sf::Vector2f(320, 700));
    CheckboxButton* player3_checkbox = new CheckboxButton(sf::Vector2f(610, 720), gm->textures->box_human, checkboxValue3);


    sf::Sprite* s_player4_label = new sf::Sprite(*gm->textures->player4Label);
    s_player4_label->setPosition(20, 860);
    sf::Sprite* s_player4_name_label = new sf::Sprite(*gm->textures->emptyLabel);
    s_player4_name_label->setPosition(280, 860);

    gm->player3text = new TextButton(sf::Vector2f(420, 910), gm->textures->emptyLabel, 3);
    (*gm->player3text).textBox.setCharacterSize(36);
    (*gm->player3text).textBox.setFont(*gm->font);
    (*gm->player3text).textBox.setFillColor(sf::Color(212, 197, 10, 255));
    (*gm->player3text).textBox.setPosition(sf::Vector2f(320, 890));

    CheckboxButton* player4_checkbox = new CheckboxButton(sf::Vector2f(610, 910), gm->textures->box_human, checkboxValue4);

    PlayButton* startGameButton = new PlayButton(sf::Vector2f(1600, 800), gm->textures->btn_play);


    

    //gameUI
   
    //topCArd
    TopCard* topCard = new TopCard(sf::Vector2f(665, 230));

    //directionIndicator
    sf::Sprite* directionIndicator = new sf::Sprite(*gm->textures->directionIndicator);
    directionIndicator->setPosition(sf::Vector2f(545, 350));

    //drawButton
    DrawCardButton* drawCardButton = new DrawCardButton(sf::Vector2f(1710, 100), gm->textures->drawCardButtonTexture);

    sf::Sprite* changeColorLabel = new sf::Sprite;
    changeColorLabel->setTexture(*(gm->textures->changeColorLabelTexture));
    changeColorLabel->setPosition(215, 50);
    //changeCol bg
    sf::RectangleShape* changeColorBg = new sf::RectangleShape(sf::Vector2f(330, 530));
    changeColorBg->setFillColor(sf::Color(100, 100, 100, 255));
    changeColorBg->setPosition(sf::Vector2f(180, 40));
    changeColorBg->setOutlineColor(sf::Color::Black);
    changeColorBg->setOutlineThickness(-5);

    ChooseColorButton* colorRedButton = new ChooseColorButton(sf::Vector2f(265, 255), gm->textures->colorRedButtonTexture, 0);
    ChooseColorButton* colorBlueButton = new ChooseColorButton(sf::Vector2f(425, 255), gm->textures->colorBlueButtonTexture, 1);
    ChooseColorButton* colorGreenButton = new ChooseColorButton(sf::Vector2f(265, 460), gm->textures->colorGreenButtonTexture, 2);
    ChooseColorButton* colorYellowButton = new ChooseColorButton(sf::Vector2f(425, 460), gm->textures->colorYellowButtonTexture, 3);


    //tu poprawic ewentualnie
    sf::Sprite* playDrawnCardLabel = new sf::Sprite;
    playDrawnCardLabel->setTexture(*(gm->textures->playInstantLabel));
    playDrawnCardLabel->setPosition(sf::Vector2f(1580, 170));
    
    sf::Sprite* drawnCard = new sf::Sprite;
    drawnCard->setTexture(*(gm->textures->cardTextures->blackColor));
    drawnCard->setPosition(sf::Vector2f(1635, 275));

    YesNoButton* yesButton = new YesNoButton(sf::Vector2f(1630, 530), gm->textures->checkbox_yes, 1);
    YesNoButton* noButton = new YesNoButton(sf::Vector2f(1790, 530), gm->textures->checkbox_no, 0);

    sf::RectangleShape* playDrawnMenuBg = new sf::RectangleShape(sf::Vector2f(300, 430));
    playDrawnMenuBg->setFillColor(sf::Color(100, 100, 100, 255));
    playDrawnMenuBg->setPosition(sf::Vector2f(1560, 160));
    
    //hand bg
    sf::RectangleShape* handBg = new sf::RectangleShape(sf::Vector2f(1920,1080));
    handBg->setFillColor(sf::Color(100, 100, 100, 255));
    handBg->setPosition(sf::Vector2f(0, 600));

    //rightSideBg
    sf::RectangleShape* rightSideBg = new sf::RectangleShape(sf::Vector2f(420, 1080));
    rightSideBg->setFillColor(sf::Color(100, 100, 100, 255));
    rightSideBg->setPosition(sf::Vector2f(1500, 0));

    //lines
    sf::RectangleShape* horizontalLine = new sf::RectangleShape(sf::Vector2f(1920, 5));
    horizontalLine->setFillColor(sf::Color::Black);
    horizontalLine->setPosition(0, 600);

    sf::RectangleShape* verticalLine = new sf::RectangleShape(sf::Vector2f(5, 600));
    verticalLine->setFillColor(sf::Color::Black);
    verticalLine->setPosition(1500, 0);

    //playerData

    sf::RectangleShape* player0bg = new sf::RectangleShape(sf::Vector2f(410, 60));
    player0bg->setFillColor(sf::Color(50, 50, 50, 255));
    player0bg->setPosition(sf::Vector2f(540, 530));
    player0bg->setOutlineColor(sf::Color::Black);
    player0bg->setOutlineThickness(-5);
    gm->sceneManager->gameUI->player0bg = player0bg;

    sf::Sprite* turnIndicator0 = new sf::Sprite(*gm->textures->turnIndicator);
    turnIndicator0->setPosition(sf::Vector2f(960,540));

    gm->sceneManager->gameUI->player0name->setPosition(sf::Vector2f(550, 550));
    gm->sceneManager->gameUI->player0cards->setPosition(sf::Vector2f(720, 550));
    gm->sceneManager->gameUI->player0uno->setPosition(sf::Vector2f(880, 550));

    sf::RectangleShape* player1bg = new sf::RectangleShape(sf::Vector2f(150, 150));
    player1bg->setFillColor(sf::Color(50, 50, 50, 255));
    player1bg->setPosition(sf::Vector2f(0, 220));
    player1bg->setOutlineColor(sf::Color::Black);
    player1bg->setOutlineThickness(-5);
    gm->sceneManager->gameUI->player1bg = player1bg;

    sf::Sprite* turnIndicator1 = new sf::Sprite(*gm->textures->turnIndicator);
    turnIndicator1->setPosition(sf::Vector2f(90, 370));

    gm->sceneManager->gameUI->player1name->setPosition(sf::Vector2f(20, 250));
    gm->sceneManager->gameUI->player1cards->setPosition(sf::Vector2f(20,300));
    gm->sceneManager->gameUI->player1uno->setPosition(sf::Vector2f(50,335));

    sf::RectangleShape* player2bg = new sf::RectangleShape(sf::Vector2f(410, 60));
    player2bg->setFillColor(sf::Color(50, 50, 50, 255));
    player2bg->setPosition(sf::Vector2f(540, 30));
    player2bg->setOutlineColor(sf::Color::Black);
    player2bg->setOutlineThickness(-5);
    gm->sceneManager->gameUI->player2bg = player2bg;

    sf::Sprite* turnIndicator2 = new sf::Sprite(*gm->textures->turnIndicator);
    turnIndicator2->setPosition(sf::Vector2f(960, 40));

    gm->sceneManager->gameUI->player2name->setPosition(sf::Vector2f(550, 50));
    gm->sceneManager->gameUI->player2cards->setPosition(sf::Vector2f(720,50));
    gm->sceneManager->gameUI->player2uno->setPosition(sf::Vector2f(880,50));
 
    sf::RectangleShape* player3bg = new sf::RectangleShape(sf::Vector2f(150, 150));
    player3bg->setFillColor(sf::Color(50, 50, 50, 255));
    player3bg->setPosition(sf::Vector2f(1350, 220));
    player3bg->setOutlineColor(sf::Color::Black);
    player3bg->setOutlineThickness(-5);
    gm->sceneManager->gameUI->player3bg = player3bg;

    sf::Sprite* turnIndicator3 = new sf::Sprite(*gm->textures->turnIndicator);
    turnIndicator3->setPosition(sf::Vector2f(1370, 370));

    gm->sceneManager->gameUI->player3name->setPosition(sf::Vector2f(1370, 250));
    gm->sceneManager->gameUI->player3cards->setPosition(sf::Vector2f(1370,300));
    gm->sceneManager->gameUI->player3uno->setPosition(sf::Vector2f(1400,335));


    //zaslona
    sf::RectangleShape* veil = new sf::RectangleShape(sf::Vector2f(1920, 1080));
    veil->setFillColor(sf::Color(50, 50, 50, 255));
    veil->setPosition(sf::Vector2f(0, 605));

    sf::RectangleShape* veilBg = new sf::RectangleShape(sf::Vector2f(600,300));
    veilBg->setFillColor(sf::Color(100, 100, 100, 255));
    veilBg->setPosition(sf::Vector2f(660, 705));

    sf::Text* veilLabel = new sf::Text();
    veilLabel->setFont(*gm->font);
    veilLabel->setPosition(sf::Vector2f(960, 755));
    veilLabel->setCharacterSize(24);
    veilLabel->setFillColor(sf::Color(212, 197, 10, 255));

    CloseButton* veilClose = new CloseButton(sf::Vector2f(960, 850), gm->textures->checkbox_no);
    veilClose->isVeilButton = true;

    sf::RectangleShape* veilBorder0 = new sf::RectangleShape(sf::Vector2f(605, 5));
    veilBorder0->setFillColor(sf::Color::Black);
    veilBorder0->setPosition(sf::Vector2f(655, 700));

    sf::RectangleShape* veilBorder1 = new sf::RectangleShape(sf::Vector2f(5, 305));
    veilBorder1->setFillColor(sf::Color::Black);
    veilBorder1->setPosition(sf::Vector2f(655, 700));

    sf::RectangleShape* veilBorder2 = new sf::RectangleShape(sf::Vector2f(605, 5));
    veilBorder2->setFillColor(sf::Color::Black);
    veilBorder2->setPosition(sf::Vector2f(655, 1000));

    sf::RectangleShape* veilBorder3 = new sf::RectangleShape(sf::Vector2f(5, 305));
    veilBorder3->setFillColor(sf::Color::Black);
    veilBorder3->setPosition(sf::Vector2f(1255, 700));

    sf::RectangleShape* endGameBg = new sf::RectangleShape(sf::Vector2f(605, 400));
    endGameBg->setFillColor(sf::Color(50, 50, 50, 255));
    endGameBg->setPosition(sf::Vector2f(655, 300));
    endGameBg->setOutlineColor(sf::Color::Black);
    endGameBg->setOutlineThickness(-5);

    sf::Text* winnerText = new sf::Text();
    winnerText->setCharacterSize(60);
    winnerText->setFont(*gm->font);
    winnerText->setFillColor(sf::Color(212, 197, 10, 255));
    winnerText->setPosition(sf::Vector2f(960,350));

    PlayButton* returnToMenu = new PlayButton(sf::Vector2f(960, 500), gm->textures->checkbox_no);
    returnToMenu->isVeilButton = true;



    //wypelnij strukture scenemanager
    //menu
    gm->sceneManager->mainMenu->playButton = menuButton;
    gm->sceneManager->mainMenu->exitButton = exitButton;
    gm->sceneManager->mainMenu->background = background;
    gm->sceneManager->mainMenu->logo =logo ;


    //setupMneu
    gm->sceneManager->setupMenu->background = setupBg;
    
    gm->sceneManager->setupMenu->players_label = s_players_label;
    
    gm->sceneManager->setupMenu->box_plus = playersPlus;
    gm->sceneManager->setupMenu->box_minus = playersMinus;

    
    gm->sceneManager->setupMenu->player1_label = s_player1_label;
    gm->sceneManager->setupMenu->player2_label = s_player2_label;
    gm->sceneManager->setupMenu->player3_label = s_player3_label;
    gm->sceneManager->setupMenu->player4_label = s_player4_label;

    gm->sceneManager->setupMenu->player2_checkbox = player2_checkbox;
    gm->sceneManager->setupMenu->player3_checkbox = player3_checkbox;
    gm->sceneManager->setupMenu->player4_checkbox = player4_checkbox;

    gm->sceneManager->setupMenu->startGameButton = startGameButton;




    //gameUI
    //gm->sceneManager->gameUI->button = gameButton;
    gm->sceneManager->gameUI->topCard = topCard;
    gm->sceneManager->gameUI->drawCardButton = drawCardButton;

    gm->sceneManager->gameUI->changeColorLabel = changeColorLabel;
    gm->sceneManager->gameUI->colorRedButton = colorRedButton;
    gm->sceneManager->gameUI->colorBlueButton = colorBlueButton;
    gm->sceneManager->gameUI->colorGreenButton = colorGreenButton;
    gm->sceneManager->gameUI->colorYellowButton = colorYellowButton;

    gm->sceneManager->gameUI->drawnCardLabel = playDrawnCardLabel;
    gm->sceneManager->gameUI->PlayDrawnMenuBg = playDrawnMenuBg;
    gm->sceneManager->gameUI->drawnCard = drawnCard;
    gm->sceneManager->gameUI->yesButton = yesButton;
    gm->sceneManager->gameUI->noButton = noButton;

    gm->sceneManager->gameUI->handBg = handBg;
    gm->sceneManager->gameUI->changeColorBg = changeColorBg;
    gm->sceneManager->gameUI->rightSideBg = rightSideBg;


    gm->sceneManager->gameUI->turnIndicator0 = turnIndicator0;
    gm->sceneManager->gameUI->turnIndicator1 = turnIndicator1;
    gm->sceneManager->gameUI->turnIndicator2 = turnIndicator2;
    gm->sceneManager->gameUI->turnIndicator3 = turnIndicator3;

    gm->sceneManager->gameUI->horizontalLine = horizontalLine;
    gm->sceneManager->gameUI->verticalLine = verticalLine;

    gm->sceneManager->gameUI->directionIndicator = directionIndicator;

    gm->sceneManager->gameUI->veil = veil;
    gm->sceneManager->gameUI->veilBg = veilBg;
    gm->sceneManager->gameUI->veilLabel = veilLabel;
    gm->sceneManager->gameUI->veilClose = veilClose;
    gm->sceneManager->gameUI->veilBorder0 = veilBorder0;
    gm->sceneManager->gameUI->veilBorder1 = veilBorder1;
    gm->sceneManager->gameUI->veilBorder2 = veilBorder2;
    gm->sceneManager->gameUI->veilBorder3 = veilBorder3;

    gm->sceneManager->gameUI->endGameBg = endGameBg;
    gm->sceneManager->gameUI->winnerText = winnerText;
    gm->sceneManager->gameUI->button = returnToMenu;


    //wczytaj scene 0
    changeScene(gm, 0,handDisplay);
}

void humanTurn(game* g, HandDisplay* handDisplay,gameManager* gm)
{
    handDisplay->refreshHandDisplay(gm);
    g->players[g->turn]->playerDidAnAction = false;

    printf("\n");
    printf("this is player %d turn\n", gm->game->turn);
    printf("is uno: %d\n", g->players[g->turn]->uno);
    printf("\n");
    printf("PILE OF CARDS PLAYED:\n");
    show(g->cardsPlayed);
    printf("\n");
    printf("DECK:\n");
    show(g->deck);
    printf("\n");
    printf("player %d hand:\n",gm->game->turn);
    showList(gm->game->players[gm->game->turn]->hand);
    printf("\n");
    
}

void AITurn(game* g, gameManager* gm)
{

    g->players[g->turn]->compDidAnAction = false;
    printf("\n");
    printf("this is player %d turn\n", gm->game->turn);
    //printf("PILE OF CARDS PLAYED:\n");
    //show(g->cardsPlayed);
    printf("player %d hand:\n", gm->game->turn);
    showList(gm->game->players[gm->game->turn]->hand);
    //printf("AI - Rozpoczynam proces szukania karty\n");
    MCTS* mcts = createMCTS(&g->players[g->turn]->hand, &g->cardsPlayed);
    //printf("AI - szukam dostepnych ruchow\n");
    list* possiblePlays = createList();
    possiblePlays = MCTSfindPossiblePlays(mcts->cardsPlayed, mcts->hand);
    //printf("AI - znalazlam dostepne ruchy\n");
    list* specials = createList();
    //printf("AI -szukam kart specjalnych \n");
    specials = findSpecialCards(g->players[g->turn]->hand);
    //printf("AI -znalazlam karty specjalne \n");



    //jesli przeciwnik ma UNO:
    if (g->players[nextPlayerId(g)]->uno)
    {
        //printf("AI - PRZECIWNIK MA UNO! - podejmuje probe przeszkodzenia\n");
        card* blackCard = AIEnemyHasUno(g);

        if (blackCard != NULL)
        {
            destroyList(&specials);
        }
       // printf("AI - PRZECIWNIK MA UNO! - nie mam jak przeszkodzic :/\n");
    }


    //jesli ma dostepny ruch:
    if (listSize(possiblePlays) > 0  && !g->players[g->turn]->compDidAnAction )
    {
       // printf("AI - Rozpoczynam MCTS\n");
        //ruch komputera
        card* c = findBestCard(mcts, gm->mctsDepth, gm->mctsSimDepth);

        //printf("AI - Skonczylam wyszukiwanie MCTS \n");

        //printf("AI zagrywa: ");
       // getCardFromId(c->id);
        int pos = findPositionOfCard(g->players[g->turn]->hand, c) + 1;

        playCard(g, pos);
    }
    //sprawdz czy ma specjala
    else if (listSize(specials) > 0 && !g->players[g->turn]->compDidAnAction)
    {
       // printf("AI - Zmieniam kolor\n");
        card* c = specials->c;
        int pos = findPositionOfCard(g->players[g->turn]->hand, c) + 1;
        //wybierz kolor, ktorego masz najwiecej i zagraj specjala zmieniajacego kolor( 1 z listy specials)
        AiPlayBlackCard(g, pos);
    }
    else if(!g->players[g->turn]->compDidAnAction)
    {
        //printf("AI - Dobieram karte\n");
        drawCard(g, g->turn);
    }

    destroyList(&specials);

    //jesli ktos zagral skip
    if (g->skipTurn)
    {
        g->skipTurn = 0;
        nextTurn(g);
    }
    nextTurn(g);

}

void refreshTillNextTurn(gameManager* gm, HandDisplay* handDisplay)
{
    gm->sceneManager->gameUI->topCard->refreshTopCard(gm);
    handDisplay->refreshHandDisplayLastPlayer(gm);

    if (gm->game->playerCount >= 1)
    {
        gm->sceneManager->gameUI->player0cards->setString("Cards: " + to_string(listSize(gm->game->players[0]->hand)));
    }
    if (gm->game->playerCount >= 2)
    {
        gm->sceneManager->gameUI->player1cards->setString("Cards: " + to_string(listSize(gm->game->players[1]->hand)));
    }
    if (gm->game->playerCount >= 3)
    {
        gm->sceneManager->gameUI->player2cards->setString("Cards: " + to_string(listSize(gm->game->players[2]->hand)));
    }
    if (gm->game->playerCount >= 4)
    {
        gm->sceneManager->gameUI->player3cards->setString("Cards: " + to_string(listSize(gm->game->players[3]->hand)));
    }

    if (gm->game->playDirection == 1)
    {
        gm->sceneManager->gameUI->directionIndicator->setTexture(*gm->textures->directionIndicator);
    }
    else
    {
        gm->sceneManager->gameUI->directionIndicator->setTexture(*gm->textures->directionIndicatorReversed);
    }

    string pname; //winner text

    //sprawdz czy koniec gry
    if (gm->game != NULL)
    {
        switch (gm->game->playerCount)
        {
        case 2:
        {
            if (listEmpty(gm->game->players[0]->hand))
            {
                pname = gm->game->players[0]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + "  wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            if (listEmpty(gm->game->players[1]->hand))
            {
                pname = gm->game->players[1]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            break;
        }

        case 3:
        {
            if (listEmpty(gm->game->players[0]->hand))
            {
                pname = gm->game->players[0]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            if (listEmpty(gm->game->players[1]->hand))
            {
                pname = gm->game->players[1]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            if (listEmpty(gm->game->players[2]->hand))
            {
                pname = gm->game->players[2]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            break;
        }
        case 4:
        {
            if (listEmpty(gm->game->players[0]->hand))
            {
                pname = gm->game->players[0]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            if (listEmpty(gm->game->players[1]->hand))
            {
                pname = gm->game->players[1]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            if (listEmpty(gm->game->players[2]->hand))
            {
                pname = gm->game->players[2]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            if (listEmpty(gm->game->players[3]->hand))
            {
                pname = gm->game->players[3]->name->toAnsiString();
                gm->sceneManager->gameUI->winnerText->setString(pname + " wins!");
                gm->sceneManager->gameUI->button->setActive(true);
                gm->sceneManager->gameUI->veilClose->setActive(false);
                gm->sceneManager->gameUI->showEndGame = true;
                gm->game->gameStarted = false;
                break;
            }
            break;
        }




        }
    }
}

void refreshAtTurnStart(gameManager* gm, HandDisplay* handDisplay)
{
    //posortuj karty
    sortCurrentPlayerHandDisplay(gm, handDisplay);


    //zaslona
    setVeil(gm);


    //turnIndicator
    setTurnIndicator(gm);



    gm->sceneManager->gameUI->showPlayDrawnCardMenu = false;
    gm->sceneManager->gameUI->showOnlyCardDrawn = false;
    gm->game->playerClickedYesNo = false;
    gm->sceneManager->gameUI->showPlayDrawnCardMenu = false;


    //przetasuj karty jesli wszystkie juz zostaly zagrane z talii
    reshuffle(gm->game);

    gm->sceneManager->gameUI->topCard->refreshTopCard(gm);


    if (gm->game->players[gm->game->turn]->comp)
    {

        AITurn(gm->game, gm);
    }
    else
    {
        humanTurn(gm->game, handDisplay, gm);
        gm->startTurn = false;
    }
}

void sortCurrentPlayerHandDisplay(gameManager* gm, HandDisplay* handDisplay)
{
    if (gm->game->players[gm->game->turn]->comp == false)
    {
        printf("sortuje liste %d z MAIN\n", gm->game->turn);
        sortList(gm->game->players[gm->game->turn]->hand);
        handDisplay->refreshHandDisplay(gm);
    }
}

void setVeil(gameManager* gm)
{
    gm->sceneManager->gameUI->showVeilButton = !gm->game->players[gm->game->turn]->comp;
    string playerName = gm->game->players[gm->game->turn]->name->toAnsiString();
    string veilLabel = playerName + "'s turn";
    gm->sceneManager->gameUI->veilLabel->setString(veilLabel);
    gm->sceneManager->gameUI->showVeil = true;
    if (gm->game->players[gm->game->turn]->comp)
    {
        ;
    }
    else
    {


        switch (gm->game->playerCount)
        {
        case 2:
        {
            if (gm->game->players[1]->comp)
            {
                gm->sceneManager->gameUI->showVeil = false;
                gm->sceneManager->gameUI->showVeilButton = false;
            }
            break;
        }

        case 3:
        {
            if (gm->game->players[1]->comp && gm->game->players[2]->comp)
            {
                gm->sceneManager->gameUI->showVeil = false;
                gm->sceneManager->gameUI->showVeilButton = false;
            }
            break;
        }
        case 4:
        {
            if (gm->game->players[1]->comp && gm->game->players[2]->comp && gm->game->players[3]->comp)
            {
                gm->sceneManager->gameUI->showVeil = false;
                gm->sceneManager->gameUI->showVeilButton = false;
            }
            break;
        }

        }
    }
}

void setTurnIndicator(gameManager* gm)
{
    switch (gm->game->turn)
    {
    case 0:
    {
        gm->sceneManager->gameUI->draw0indicator = true;
        gm->sceneManager->gameUI->draw1indicator = false;
        gm->sceneManager->gameUI->draw2indicator = false;
        gm->sceneManager->gameUI->draw3indicator = false;
        break;
    }
    case 1:
    {
        gm->sceneManager->gameUI->draw0indicator = false;
        gm->sceneManager->gameUI->draw1indicator = true;
        gm->sceneManager->gameUI->draw2indicator = false;
        gm->sceneManager->gameUI->draw3indicator = false;
        break;
    }
    case 2:
    {
        gm->sceneManager->gameUI->draw0indicator = false;
        gm->sceneManager->gameUI->draw1indicator = false;
        gm->sceneManager->gameUI->draw2indicator = true;
        gm->sceneManager->gameUI->draw3indicator = false;
        break;
    }
    case 3:
    {
        gm->sceneManager->gameUI->draw0indicator = false;
        gm->sceneManager->gameUI->draw1indicator = false;
        gm->sceneManager->gameUI->draw2indicator = false;
        gm->sceneManager->gameUI->draw3indicator = true;
        break;
    }
    default:
    {
        break;
    }
    }
}

void drawScene(gameManager* gm, HandDisplay* handDisplay, sf::RenderWindow &window)
{
    switch (gm->sceneManager->currentScene)
    {
    case 0:
    {
        drawMainMenu(gm, window);
        break;
    }
    case 1:
    {

        drawSetupMenu(gm, window);
        break;
    }
    case 2:
    {
        drawGameUiBg(gm, handDisplay, window);
        drawHandDisplay(gm, handDisplay, window);
        drawGame(gm, window);
        break;
    }
    default:
    {
        break;
    }
    }
}

void handleEvents(gameManager* gm, sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::Closed)
        window.close();

    if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        gm->textures->cursor->loadFromPixels(gm->textures->cur_cl->getPixelsPtr(), gm->textures->cur_cl->getSize(), sf::Vector2u(0, 0));
        window.setMouseCursor(*gm->textures->cursor);
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        gm->textures->cursor->loadFromPixels(gm->textures->cur->getPixelsPtr(), gm->textures->cur->getSize(), sf::Vector2u(0, 0));
        window.setMouseCursor(*gm->textures->cursor);
    }

    if (gm->sceneManager->currentScene == 1)
    {
        if (event.type == sf::Event::TextEntered)
        {
            (*gm->player0text).typedOn(event);
            (*gm->player1text).typedOn(event);
            (*gm->player2text).typedOn(event);
            (*gm->player3text).typedOn(event);
        }
    }


    //obsluga eventow dla klas button 
    Button::mouseInput(gm, event);
}

void handDisplaySetup(HandDisplay* handDisplay,gameManager* gm)
{
    handDisplay->createCardButtons(gm);
    handDisplay->bg = new sf::RectangleShape(sf::Vector2f(0, 100));
    handDisplay->bg->setPosition(sf::Vector2f(0, 600));
    handDisplay->bg->setFillColor(sf::Color(100, 100, 100, 255));
    handDisplay->bg->setSize(sf::Vector2f(2000, 500));
}