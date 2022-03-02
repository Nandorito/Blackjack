//Blackjack test

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

#include "Card.h"

int Card::GetValue() const
{
    //if card is face down the value is 0
    int value = 0;
    if(m_IsFaceUp)
    {
        //value is number showing on card
        value = m_Rank;
        //value is 10 for face cards
        if(value > 10) value = 10;
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !m_IsFaceUp;//flips the card
}


#include "Hand.h"

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}

void Hand::Clear()
{
    //iterate through vector, freeing all the memory on the heap
    std::vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete *iter;
        *iter = 0;
    }
    //clear vector of pointers
    m_Cards.clear();
}

int Hand::GetTotal() const
{
    //if no cards in hand, return 0
    if(m_Cards.empty()) return 0;

    //if card is 0, then its face down
    if(m_Cards[0]->GetValue() == 0) return 0;

    //add up card values, treat ace as 1
    int total = 0;
    std::vector<Card*>::const_iterator iter;

    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }

    //determine if hand contains an ace
    bool containsAce = false;
    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if((*iter)->GetValue() == Card::ACE) containsAce = true;
    }

    if(containsAce && total <= 11)
    {
        //add only 10 since we've already added 1
        total += 10;
    }
    return total;
}


#include "GenericPlayer.h"


bool GenericPlayer::IsBusted() const
{
    return (GetTotal() > 21);
}

void GenericPlayer::Busts() const
{
    cout << m_Name << " busts.\n";
}



#include "Player.h"



bool Player::IsHitting() const
{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
    cout << m_Name << " wins!\n";
}

void Player::Loss() const
{
    cout << m_Name << " lost. :(\n";
}

void Player::Pushes() const
{
    cout << m_Name << " pushes.\n";
}




#include "House.h"



bool House::IsHitting() const
{
    return (GetTotal() <= 16);//house hits on 16 or less
}

void House::FlipFirstCard()
{
    if(!(m_Cards.empty())) m_Cards[0]->Flip();
    else cout << "No card to flip.\n";
}



#include "Deck.h"



void Deck::Populate()
{
    Clear();
    //create a standard deck
    for(int s = Card::CLUBS; s <= Card::SPADES; ++s)
        for(int r = Card::ACE; r <= Card::KING; ++r)
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
}

void Deck::Shuffle()
{
    random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Deal(Hand& aHand)
{
    if(!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    { 
        cout << "Out of cards. Unable to deal.\n";
    }
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    cout << endl;
    //continue to deal a cardas long as generic player isnt busted and wants it
    while(!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) //turns out this statement only works while there are cards left in the deck
    {
        Deal(aGenericPlayer);

        //FIRST BUG FIXED HERE. check to see if there are any cards left. if so, break the infinite loop
        if(m_Cards.empty())
        {
            break;
        }

        
        cout << aGenericPlayer << endl;

        if(aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Busts();
        }
    }
}


#include "Blackjack.h"



void Blackjack::Play()
{

    //deal inital 2 cards to everyone
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; i++)
    {
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); pPlayer++)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }

    //hide house's first card
    m_House.FlipFirstCard();
    
    //display everyone's hand
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }

    cout << m_House << endl;


    
    //deal additional cards to players
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); pPlayer++)
        m_Deck.AdditionalCards(*pPlayer);

    //reveal house's first card
    m_House.FlipFirstCard();
    cout << endl << m_House;

    //deal additional cards to house
    m_Deck.AdditionalCards(m_House);

    if(m_House.IsBusted())
    {
        //everyone still playing wins
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); pPlayer++)
            if(!(pPlayer->IsBusted())) pPlayer->Win();
    }
    else
    {
        //compare each player still playing to house
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); pPlayer++)
        {
            if (!(pPlayer->IsBusted()))
            {
                if(pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Loss();
                }
                else
                {
                    pPlayer->Pushes();
                }
            }
        }
    }

    //removes all cards
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); pPlayer++)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}


/*
**********************************************************************
**********************************************************************
**********************************************************************


                         START OF MAIN


**********************************************************************
**********************************************************************
**********************************************************************
*/

//function prototypes
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

int main()
{
    cout << "\t\tWelcome to Blackjack!\n\n";

    int numPlayers = 0;
    while(numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1-7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }

    cout << endl;

    //the game loop
    Blackjack aBlackjack(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aBlackjack.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }

    return 0;
}

//overloads << operator so we can send a Card object to cout
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = 
    {
        "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
    };

    const string SUITS[] = 
    {
        "c", "d", "h", "s"
    };

    if(aCard.m_IsFaceUp) 
    {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else 
    {
        os << "XX";
    }

    return os;
}

ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";

    vector<Card*>::const_iterator pCard;
    if(!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); pCard++)
        {
            os << *(*pCard) << "\t";
        }

        if(aGenericPlayer.GetTotal() != 0) cout << "(" << aGenericPlayer.GetTotal() << ")";
    }
    else
    {
        os << "<empty>";
    }
    return os;
}