class Blackjack
{
public:
    Blackjack(const vector<string>& names);
    ~Blackjack();

    //plays the game of Blackjack
    void Play();
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

Blackjack::Blackjack(const vector<string>& names)
{
    //create a vector of players from a vector of names
    vector<string>::const_iterator pName;
    for(pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(Player(*pName));
    }

    //seed the random generator
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Blackjack::~Blackjack()
{}