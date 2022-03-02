class Card
{
public: 
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX,
                SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};

    //overloading the "<<" operator so we can send Card object to standard output
    friend std::ostream& operator<<(std::ostream& os, const Card& aCard);
    
    Card(rank r = ACE, suit s = SPADES, bool ifu = true);

    //returns the value of a card, 1-11
    int GetValue() const;

    //flips a card
    void Flip();

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu): m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}