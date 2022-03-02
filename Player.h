class Player: public GenericPlayer
{
public:
    Player(const string& name = "");

    virtual ~Player();

    //returns whether or not the player wanst to hit
    virtual bool IsHitting() const;

    //announces that the player wins
    void Win() const;

    //announces that the player loses
    void Loss() const;

    //announces that the player pushes
    void Pushes() const;
};

Player::Player(const string& name): GenericPlayer(name)
{}

Player::~Player()
{}