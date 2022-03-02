class GenericPlayer: public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

public:
    GenericPlayer(const string& name = "");

    virtual ~GenericPlayer();

    //indicates whether or not generic player wants to keep hitting
    virtual bool IsHitting() const = 0;
    
    //returns whether generic player has busted
    bool IsBusted() const;

    //announces that the generic player busts
    void Busts() const;

protected:
    string m_Name;
};

GenericPlayer::GenericPlayer(const string& name): m_Name(name)
{}

GenericPlayer::~GenericPlayer()
{}