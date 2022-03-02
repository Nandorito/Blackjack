class Hand
{
public:
    Hand();
    virtual ~Hand();

    //adds card to the hand
    void Add(Card* pCard);
    //clears hand of all cards
    void Clear();
    //gets hand total value, intelligently treats aces as 1 or 11
    int GetTotal() const;
protected:
    std::vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}

Hand::~Hand()
{
    Clear();
}