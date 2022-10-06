
#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int readCardValue(std::string card);
std::string playerOneName{};            
std::string playerTwoName{};
const std::string faces[13] = { "Deuce",        //array of faces used for the cards, listened in order from least to greatest
"Three", "Four", "Five", "Six", 
"Seven", "Eight",
 "Nine", "Ten", "Jack", "Queen", "King", "Ace" }; 
const std::string suits[4] = { "Clubs",         //array of suits used for the cards, listed in order from greatest to least
"Diamonds", "Hearts", "Spades" };
std::string deckOfCards[52]{};                  //initial deck of cards that will get shuffled and distributed to two players
std::string playerOneDeck[52]{};                //deck of cards used by the first player
std::string playerTwoDeck[52]{};                //deck of cards used by the second player
std::string playerOneDiscard[52]{};             //stores the cards that player one has won from player two
std::string playerTwoDiscard[52]{};             //stores the cards that player two has won from player one
std::string playerOneSelection[4]{};            //array storing the order and value of the 4 cards drawn by first player
std::string playerTwoSelection[4]{};            //array storing the order and value of the 4 cards drawn by second player
int orderOfFour{ 0 };
std::string drawnCards[4]{};                    //the 4 cards drawn by the players before they're reordered
int selectionIndex{};                           //used to transfer user's selected order on to the ordered array from 0-3
int realCardCounter{};
int playerOneDiscardIndex{ 0 };
int playerTwoDiscardIndex{ 0 };
int selectedCardOrder[4]{}; 

void clear()                                    //function used to first ask the user to confirm they've read the text, before clearing the text upon their cue
{
    std::string userClear{};                    
    std::cout << "Enter anything to continue: ";
    std::cin >> userClear;                      //program has no use for what user inputs, just to make sure it clears after they enter something into the variable
    std::cout << "\x1B[2J\x1B[H";               //printing this string will clear the screen
    //system("cls");
}

void createLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void getNames()                                 //function used at start of program to get users' names
{
    createLine();
    std::cout << "Welcome to Evan's war card game!\n";
    std::cout << "Please input player one's name: ";
    std::cin >> playerOneName;
    std::cout << "Perfect, nice to meet you " << playerOneName << "!\n";
    std::cout << "Please input player two's name: ";
    std::cin >> playerTwoName;
    std::cout << "Great, nice to meet you " << playerTwoName << "!\n";
    createLine();
    clear();
    
}


void createDeck()                               //Creates the values of the cards in the deck with string
{
    for (int i = 0; i < 52; i++)
    {
        deckOfCards[i] = faces[i / 4] + " of " + suits[i % 4];
    }
}
void shuffleDeck()
{
    for (int i = 0; i < 52; i++)                //Shuffles deck by randomizing card swaps throughout the deck
    {
        int randomSelection{};
        std::string temp{};
        randomSelection = rand() % 52;
        temp = deckOfCards[i];
        deckOfCards[i] = deckOfCards[randomSelection];
        deckOfCards[randomSelection] = temp;
    }
} 
void createPlayerDecks()
{ 
    for (int i = 0; i < 52; i++)                //fills each element as empty initially before they're filled
    {
        playerOneDeck[i] = "empty";
        playerTwoDeck[i] = "empty";
        playerOneDiscard[i] = "empty";
        playerTwoDiscard[i] = "empty";
    }
    for (int i = 0; i < 52; i++)                //distributes initial deck of cards to the piles of the two players
    {
        if (i % 2 == 0)
        {
            playerOneDeck[i / 2] = deckOfCards[i];
        }
        else
        {
            playerTwoDeck[i / 2] = deckOfCards[i];
        }
        deckOfCards[i] = "empty";           
    }
}
int remainingCardsPlayer(int playerNumber)                   //scans through the deck of player and counts the number of elements with no card       
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {
        if (playerNumber == 1)
        {
            if (playerOneDeck[i] != "empty")
            {
                realCardCounter++;
            }
        }        
        else
        {
            if (playerTwoDeck[i] != "empty")
            {
                realCardCounter++;
            }
        }
    }
    return realCardCounter;
}

void drawCards(int playerNumber)
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {
        if (playerNumber == 2)
        {
            if (playerTwoDeck[i] != "empty")
            {
                realCardCounter++;
                drawnCards[realCardCounter - 1] = playerTwoDeck[i];
                playerTwoDeck[i] = "empty";
            }
        }
        else
        {
            if (playerOneDeck[i] != "empty")
            {
                realCardCounter++;
                drawnCards[realCardCounter - 1] = playerOneDeck[i];
                playerOneDeck[i] = "empty";
            }
        }
        if (realCardCounter == 4)
        {
            break;
        }
    }
}
int remainingDiscardCards(int playerNumber)
{
    realCardCounter = 0;
    for (int i = 51; i >= 0; i--)
    {
        if (playerNumber == 1)
        {
            if (playerOneDiscard[i] != "empty")
            {
                realCardCounter++;
            }
        }
        else
        {
            if (playerTwoDiscard[i] != "empty")
            {
                realCardCounter++;
            }
        }
    }
    return realCardCounter;
}

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void playerOrder(int playerNumber)
{
    int selectedDuplicate{};
    for (int i = 0; i<=3; ++i)
    {
        selectedDuplicate = 0;
        std::cin.clear();
        ignoreLine();
        std::cout << "Select the card (ordered 1-4) you would like to play #" << i+1 << ": \n";
        std::cin >> orderOfFour;
        if (!std::cin || orderOfFour < 1 || orderOfFour>4)
        {
            std::cout << "Please enter a valid input\n";
            --i;
            continue;
        }
        else
        {
            for (int j = 0; j < 4; ++j)
            {
                if (orderOfFour-1 == selectedCardOrder[j])
                {
                    std::cout << "You have already chosen that card! Please enter another one\n";
                    --i;
                    selectedDuplicate = 1;
                }
            }
            if (selectedDuplicate == 0)
            {
                selectedCardOrder[i] = orderOfFour - 1;
                if (playerNumber == 1)
                {
                    playerOneSelection[i] = selectedCardOrder[i];
                }
                else
                {
                    playerTwoSelection[i] = selectedCardOrder[i];
                }
            
            }
            

            
        }
    }
    
}

void transferOrder(int playerNumber)
{
    for (int i = 0; i<=3; ++i)
    {
        if (playerNumber == 1)
        {
            playerOneSelection[i] = drawnCards[selectedCardOrder[i]];
        }
        else
        {
            playerTwoSelection[i] = drawnCards[selectedCardOrder[i]];
        }
    }
}


void compareCards()
{
    for (int i = 0; i <= 3; i++)
    {
        if (readCardValue(playerOneSelection[i]) > readCardValue(playerTwoSelection[i]))
        {
            std::cout << playerOneName << " played the " << playerOneSelection[i] << ", which is greater than " << playerTwoName << "'s selection of the " << playerTwoSelection[i] << ", so both cards will go to " << playerOneName << "'s discard pile!\n\n";
            playerOneDiscard[playerOneDiscardIndex] = playerTwoSelection[i];
            playerOneDiscardIndex++;
            playerOneDiscard[playerOneDiscardIndex] = playerOneSelection[i];
            playerOneDiscardIndex++;
        }
        else
        {
            std::cout << playerTwoName << " played the " << playerTwoSelection[i] << ", which is greater than " << playerOneName << "'s selection of the " << playerOneSelection[i] << ", so both cards will go to " << playerTwoName << "'s discard pile!\n\n";
            playerTwoDiscard[playerTwoDiscardIndex] = playerTwoSelection[i];
            playerTwoDiscardIndex++;
            playerTwoDiscard[playerTwoDiscardIndex] = playerOneSelection[i];
            playerTwoDiscardIndex++;
        }

    }
}

void shuffleDiscard(int remainingCards, int remainingDiscard, int playerNumber)
{
    srand(time(NULL));
    int tempRemain{ remainingCards };
    int tempDiscard{ remainingDiscard };
    while (remainingCards <= 52 && remainingDiscard > 0)
    {
        if (playerNumber == 1)
        {
            playerOneDeck[remainingCards] = playerOneDiscard[remainingDiscard - 1];
            playerOneDiscard[remainingDiscard - 1] = "empty";
        }
        else
        {
            playerTwoDeck[remainingCards] = playerTwoDiscard[remainingDiscard - 1];
            playerTwoDiscard[remainingDiscard - 1] = "empty";
        }
        remainingCards++;
        remainingDiscard--;
    }
    for (int i = 0; i < (tempRemain + tempDiscard); i++)        //Shuffles deck by randomizing card swaps throughout the deck
    {
        int randomSelection{};
        std::string temp{};
        randomSelection = rand() % (tempDiscard+tempRemain);
        if (playerNumber == 1)
        {
            temp = playerOneDeck[i];
            playerOneDeck[i] = playerOneDeck[randomSelection];
            playerOneDeck[randomSelection] = temp;
        }
        else
        {
            temp = playerTwoDeck[i];
            playerTwoDeck[i] = playerTwoDeck[randomSelection];
            playerTwoDeck[randomSelection] = temp;
        }
        
    }
    playerTwoDiscardIndex = 0;
    playerOneDiscardIndex = 0;
}

int readCardValue(std::string card)
{
    std::string cardCopy = card;
    int cardValue{};
    int index = cardCopy.find(' ');
    std::string suit{};
    int suitIndex = index + 4;
    for (int i = 0; i < 13; ++i)
    {
        if (card.substr(0, index) == faces[i])
        {
            cardValue = i * 5;
            for (int j = 0; j < 4; ++j)
            {
                cardValue--;
                if (cardCopy.substr(suitIndex, cardCopy.length()) == suits[j])
                {
                    return cardValue;
                }
            }
        }
        
    }
    
}

void clearSelection()
{
    for (int i = 0; i <= 3; ++i)
    {
        selectedCardOrder[i] = -1;
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
    clearSelection();
    while (gameEnd == false)
    {
        std::cout << "It is now " << playerOneName << "'s turn!\n";
        clear();
        oneCards = remainingCardsPlayer(1);
        oneDiscard = remainingDiscardCards(1);
        createLine();
        std::cout << playerOneName << ", you have " << oneCards << " cards left in your deck, and " << oneDiscard << " cards left in your discard pile.\n";
        if (oneCards < 4)
        {
            if (oneDiscard+oneCards < 4)
            {
                break;
            }
            else
            {
                createLine();
                std::cout << "Because you don't have enough cards in your deck, your discard pile will be shuffled into it.\n";
                createLine();
                shuffleDiscard(oneCards, oneDiscard, 1);
                oneCards = remainingCardsPlayer(1);
                oneDiscard = remainingDiscardCards(1);
                std::cout << playerOneName << ", you now have " << oneCards << " cards left in your deck, and " << oneDiscard << " cards left in your discard pile.\n";
            }
        }
        
        drawCards(1);
        createLine();
        std::cout << playerOneName << ", you drew the " << drawnCards[0] << ", " << drawnCards[1] << ", " << drawnCards[2] << ", " << drawnCards[3] << '\n';
        createLine();
        playerOrder(1);
        transferOrder(1);
        clearSelection();
        selectionIndex = 0;
        createLine();
        std::cout << playerOneName << ", you will play your cards in the order of " << playerOneSelection[0] << ", " << playerOneSelection[1] << ", " << playerOneSelection[2] << ", " << playerOneSelection[3] << '\n';
        createLine();
        clear();
        createLine();
        std::cout << "It is now " << playerTwoName << "'s turn!\n";
        createLine();
        clear();
        twoCards = remainingCardsPlayer(2);
        twoDiscard = remainingDiscardCards(2);
        createLine();
        std::cout << playerTwoName << ", you have " << twoCards << " cards left in your deck, and " << twoDiscard << " cards left in your discard pile.\n";
        createLine();
        if (twoCards < 4)
        {
            if (twoCards+twoDiscard < 4)
            {
                playerOneWin = true;
                break;
            }
            else
            {
                createLine();
                std::cout << "Because you don't have enough cards in your deck, your discard pile will be shuffled into it.\n";
                createLine();
                shuffleDiscard(twoCards, twoDiscard, 2);
                twoCards = remainingCardsPlayer(2);
                twoDiscard = remainingDiscardCards(2);
                createLine();
                std::cout << playerTwoName << ", you now have " << twoCards << " cards left in your deck, and " << twoDiscard << " cards left in your discard pile.\n";
                createLine();
            }
        }
        drawCards(2);
        std::cout << playerTwoName << ", your 4 cards are " << drawnCards[0] << ", " << drawnCards[1] << ", " << drawnCards[2] << ", " << drawnCards[3] << '\n';
        createLine();
        playerOrder(2);
        transferOrder(2);
        clearSelection();
        selectionIndex = 0;
        createLine();
        std::cout << playerTwoName << ", you will play your cards in the order of " << playerTwoSelection[0] << ", " << playerTwoSelection[1] << ", " << playerTwoSelection[2] << ", " << playerTwoSelection[3] << '\n';
        createLine();
        clear();
        compareCards();
        clear();
    }
    
    if (playerOneWin == true)
    {
        std::cout << "\n*******************************************************************************************************\n";
        std::cout << "Congrats " << playerOneName << "! You have won the game, as your opponent does not have enough cards in their deck or discard pile.\n";
        std::cout << "*********************************************************************************************************\n";
    }
    else
    {
        std::cout << "\n*******************************************************************************************************\n";
        std::cout << "Congrats " << playerTwoName << "! You have won the game, as your opponent does not have enough cards in their deck or discard pile.\n";
        std::cout << "*******************************************************************************************************\n";
    }
    return 0;
}
