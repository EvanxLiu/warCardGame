
#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

std::string convertCardName(int cardValue);
std::string playerOneName{};            
std::string playerTwoName{};
const std::string faces[13] = { "Deuce", "Three", "Four",
    "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
const std::string suits[4] = { "Spades", "Hearts",
    "Diamonds", "Clubs" };
int deckOfCards[52]{};                  //initial deck of cards that will get shuffled and distributed to two players
int playerOneDeck[52]{};                //deck of cards used by the first player
int playerTwoDeck[52]{};                //deck of cards used by the second player
int playerOneDiscard[52]{};             //stores the cards that player one has won from player two
int playerTwoDiscard[52]{};             //stores the cards that player two has won from player one
int playerOneSelection[4]{};            //array storing the order and value of the 4 cards drawn by first player
int playerTwoSelection[4]{};            //array storing the order and value of the 4 cards drawn by second player
int orderOfFour{ 0 };
int drawnCards[4]{};                    //the 4 cards drawn by the players before they're reordered
int selectionIndex{};                   //used to transfer user's selected order on to the ordered array from 0-3
int realCardCounter{};
int playerOneDiscardIndex{ 0 };
int playerTwoDiscardIndex{ 0 };

void getNames()
{
    std::cout << "Welcome to Evan's war card game!\n";
    std::cout << "Please input player one's name: ";
    std::cin >> playerOneName;
    std::cout << "Perfect, nice to meet you " << playerOneName << "!\n";
    std::cout << "Please input player two's name: ";
    std::cin >> playerTwoName;
    std::cout << "Great, nice to meet you " << playerTwoName << "!\n";
}
void createDeck()   
{
    for (int i = 0; i < 52; i++)        //Creates the deck of cards with integer values from 0 to 51     
    {
        deckOfCards[i] = i;
    }
}

void createDeckString()
{
    for (int i = 0; i < 52; i++)
    {

    }
}
void shuffleDeck()
{
    for (int i = 0; i < 52; i++)        //Shuffles deck by randomizing card swaps throughout the deck
    {
        int randomSelection{};
        int temp{};
        randomSelection = rand() % 52;
        temp = deckOfCards[i];
        deckOfCards[i] = deckOfCards[randomSelection];
        deckOfCards[randomSelection] = temp;
    }
} 
void createPlayerDecks()
{ 
    for (int i = 0; i < 52; i++)        //-1 symbolizes that the element of the deck is empty
    {
        playerOneDeck[i] = -1;
        playerTwoDeck[i] = -1;
        playerOneDiscard[i] = -1;
        playerTwoDiscard[i] = -1;
    }
    for (int i = 0; i < 52; i++)        //distributes initial deck of cards to the piles of the two players
    {
        if (i % 2 == 0)
        {
            playerOneDeck[i / 2] = deckOfCards[i];
        }
        else
        {
            playerTwoDeck[i / 2] = deckOfCards[i];
        }
        deckOfCards[i] = -1;           
    }
}
int remainingCardsPlayerOne()
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {

        if (playerOneDeck[i] != -1)
        {
            realCardCounter++;
        }
    }
    return realCardCounter;
}
int remainingCardsPlayerTwo()
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {

        if (playerTwoDeck[i] != -1)
        {
            realCardCounter++;
        }
    }
    return realCardCounter;
    
}
void drawCardsOne()
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)       //Outputs remaining amount of cards in player One's deck
    {

        if (playerOneDeck[i] != -1)
        {
            realCardCounter++;
            drawnCards[realCardCounter - 1] = playerOneDeck[i];
            playerOneDeck[i] = -1;
        }
        if (realCardCounter == 4)
        {

            break;
        }
    }
    realCardCounter = 0;
}
void drawCardsTwo()
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {

        if (playerTwoDeck[i] != -1)
        {
            realCardCounter++;
            drawnCards[realCardCounter - 1] = playerTwoDeck[i];
            playerTwoDeck[i] = -1;
        }
        if (realCardCounter == 4)
        {
            break;
        }
    }
}
int remainingDiscardCardsOne()
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {

        if (playerOneDiscard[i] != -1)
        {
            realCardCounter++;
        }
    }
    return realCardCounter;
}
int remainingDiscardCardsTwo()
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {

        if (playerTwoDiscard[i] != -1)
        {
            realCardCounter++;
        }
    }
    return realCardCounter;
}
int playerOrder()
{
    int playerOrderWOW{0};
    std::cout << "Select the order by entering any order of 1, 2, 3, 4: ";
    std::cin >> playerOrderWOW;
    if (std::cin.eof())
    {
        std::cout << "Please enter a valid input\n";
        std::cin.clear();
        std::cin.ignore(600, '\n');
        playerOrder();
        
    }
    else
    {
        if (playerOrderWOW != 1234 && playerOrderWOW != 1243 && playerOrderWOW != 1324 && playerOrderWOW != 1342 && playerOrderWOW != 1432 && playerOrderWOW != 1423 && playerOrderWOW != 2143 && playerOrderWOW != 2134
            && playerOrderWOW != 2431 && playerOrderWOW != 2413 && playerOrderWOW != 2341 && playerOrderWOW != 2314 && playerOrderWOW != 3124 && playerOrderWOW != 3142 && playerOrderWOW != 3241 && playerOrderWOW != 3214 && playerOrderWOW != 3421 &&
            playerOrderWOW != 3412 && playerOrderWOW != 4321 && playerOrderWOW != 4312 && playerOrderWOW != 4231 && playerOrderWOW != 4213 && playerOrderWOW != 4132 && playerOrderWOW != 4123)
        {
            std::cout << "Please enter a valid order\n";
            playerOrder();
        }
        else
        {
            return playerOrderWOW;
        }
    }
  
}

void transferOrderOne()
{
    for (int i = 1000; i >= 1; i = i / 10)
    {
        playerOneSelection[selectionIndex] = drawnCards[orderOfFour / i - 1];
        orderOfFour = orderOfFour % i;
        selectionIndex++;
    }
}

void transferOrderTwo()
{
    for (int i = 1000; i >= 1; i = i / 10)
    {
        playerTwoSelection[selectionIndex] = drawnCards[orderOfFour / i - 1];
        orderOfFour = orderOfFour % i;
        selectionIndex++;
    }
}

void compareCards()
{
    for (int i = 0; i <= 3; i++)
    {
        if (playerOneSelection[i] > playerTwoSelection[i])
        {
            std::cout << convertCardName(playerOneSelection[i]) << " is greater than " << convertCardName(playerTwoSelection[i]) << ", so both cards will go to " << playerOneName << "'s discard pile!\n";
            playerOneDiscard[playerOneDiscardIndex] = playerTwoSelection[i];
            playerOneDiscardIndex++;
            playerOneDiscard[playerOneDiscardIndex] = playerOneSelection[i];
            playerOneDiscardIndex++;
        }
        else
        {
            std::cout << convertCardName(playerTwoSelection[i]) << " is greater than " << convertCardName(playerOneSelection[i]) << ", so both cards will go to " << playerTwoName << "'s discard pile!\n";
            playerTwoDiscard[playerTwoDiscardIndex] = playerTwoSelection[i];
            playerTwoDiscardIndex++;
            playerTwoDiscard[playerTwoDiscardIndex] = playerOneSelection[i];
            playerTwoDiscardIndex++;
        }

    }
}

void shuffleDiscardOne(int remainingCards, int remainingDiscard)
{
    srand(time(NULL));
    int tempRemain{ remainingCards };
    int tempDiscard{ remainingDiscard };
    while (remainingCards <= 52&&remainingDiscard>0)
    {
        playerOneDeck[remainingCards] = playerOneDiscard[remainingDiscard - 1];
        playerOneDiscard[remainingDiscard - 1] = -1;
        remainingCards++;
        remainingDiscard--;
    }
    for (int i = 0; i < (tempRemain+tempDiscard); i++)        //Shuffles deck by randomizing card swaps throughout the deck
    {
        int randomSelection{};
        int temp{};
        randomSelection = rand() % (tempRemain+tempDiscard);
        temp = playerOneDeck[i];
        playerOneDeck[i] = playerOneDeck[randomSelection];
        playerOneDeck[randomSelection] = temp;
    }
    playerOneDiscardIndex = 0;
}

void shuffleDiscardTwo(int remainingCards, int remainingDiscard)
{
    srand(time(NULL));
    int tempRemain{ remainingCards };
    int tempDiscard{ remainingDiscard };
    while (remainingCards <= 52 && remainingDiscard > 0)
    {
        playerTwoDeck[remainingCards] = playerTwoDiscard[remainingDiscard - 1];
        playerTwoDiscard[remainingDiscard - 1] = -1;
        remainingCards++;
        remainingDiscard--;
    }
    for (int i = 0; i < (tempRemain + tempDiscard); i++)        //Shuffles deck by randomizing card swaps throughout the deck
    {
        int randomSelection{};
        int temp{};
        randomSelection = rand() % (tempDiscard+tempRemain);
        temp = playerTwoDeck[i];
        playerTwoDeck[i] = playerTwoDeck[randomSelection];
        playerTwoDeck[randomSelection] = temp;
    }
    playerTwoDiscardIndex = 0;
}
std::string convertCardName(int cardValue)
{
    return faces[cardValue / 4] + " of " + suits[cardValue % 4];
}

int readCardValue(std::string card)
{
    int index = card.find(' ');
    for (int i = 0; i < 13; i++)
    {
        if (card.substr(0, index) == faces[i])
        {
            return i + 2;
        }
    }
}
int main()
{
    std:: string stringDeck[52]{};
    int oneCards{};
    int twoCards{};
    int oneDiscard{};
    int twoDiscard{};
    bool gameEnd{ false };
    bool playerOneWin{ false };
    srand(time(NULL));
    getNames();
    for (int i = 0; i < 52; i++)
    {
        stringDeck[i] = faces[i / 4] + " of " + suits[i % 4];
    }
    createDeck();
    shuffleDeck();
    createPlayerDecks();
    while (gameEnd == false)
    {
        oneCards = remainingCardsPlayerOne();
        oneDiscard = remainingDiscardCardsOne();
        std::cout << playerOneName << ", you have " << oneCards << " cards left in your deck, and " << oneDiscard << " cards left in your discard pile.\n";
        if (oneCards < 4)
        {
            if (oneDiscard+oneCards < 4)
            {
                break;
            }
            else
            {
                std::cout << "Because you don't have enough cards in your deck, your discard pile will be shuffled into it.\n";
                shuffleDiscardOne(oneCards, oneDiscard);
                oneCards = remainingCardsPlayerOne();
                oneDiscard = remainingDiscardCardsOne();
                std::cout << playerOneName << ", you now have " << oneCards << " cards left in your deck, and " << oneDiscard << " cards left in your discard pile.\n";
            }
        }
        drawCardsOne();
        std::cout << playerOneName << ", you drew the " << convertCardName(drawnCards[0]) << ", " << convertCardName(drawnCards[1]) << ", " << convertCardName(drawnCards[2]) << ", " << convertCardName(drawnCards[3]) << '\n';
        orderOfFour = playerOrder();
        transferOrderOne();
        selectionIndex = 0;
        std::cout << playerOneName << ", you will play your cards in the order of " << convertCardName(playerOneSelection[0]) << ", " << convertCardName(playerOneSelection[1]) << ", " << convertCardName(playerOneSelection[2]) << ", " << convertCardName(playerOneSelection[3]) << '\n';

        twoCards = remainingCardsPlayerTwo();
        twoDiscard = remainingDiscardCardsTwo();
        std::cout << playerTwoName << ", you have " << twoCards << " cards left in your deck, and " << twoDiscard << " cards left in your discard pile.\n";
        if (twoCards < 4)
        {
            if (twoCards+twoDiscard < 4)
            {
                playerOneWin = true;
                break;
            }
            else
            {
                std::cout << "Because you don't have enough cards in your deck, your discard pile will be shuffled into it.\n";
                shuffleDiscardTwo(twoCards, twoDiscard);
                twoCards = remainingCardsPlayerTwo();
                twoDiscard = remainingDiscardCardsTwo();
                std::cout << playerOneName << ", you now have " << twoCards << " cards left in your deck, and " << twoDiscard << " cards left in your discard pile.\n";
            }
        }
        drawCardsTwo();
        std::cout << playerTwoName << ", your 4 cards are " << convertCardName(drawnCards[0]) << ", " << convertCardName(drawnCards[1]) << ", " << convertCardName(drawnCards[2]) << ", " << convertCardName(drawnCards[3]) << '\n';
        orderOfFour = playerOrder();
        transferOrderTwo();
        selectionIndex = 0;
        std::cout << playerTwoName << ", you will play your cards in the order of " << convertCardName(playerTwoSelection[0]) << ", " << convertCardName(playerTwoSelection[1]) << ", " << convertCardName(playerTwoSelection[2]) << ", " << convertCardName(playerTwoSelection[3]) << '\n';

        compareCards();
    }
    
    if (playerOneWin == true)
    {
        std::cout << "Congrats " << playerOneName << "! You have won the game, as your opponent does not have enough cards in their deck or discard pile.\n";
    }
    else
    {
        std::cout << "Congrats " << playerTwoName << "! You have won the game, as your opponent does not have enough cards in their deck or discard pile.\n";
    }
    return 0;
}
