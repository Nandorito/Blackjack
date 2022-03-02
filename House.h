class House: public GenericPlayer
{
public:
    House(const std::string& name = "House");

    virtual ~House();

    //indicates whether house is hitting
    virtual bool IsHitting() const;

    //flips over first card
    void FlipFirstCard();
};

House::House(const std::string& name): GenericPlayer(name)
{}

House::~House()
{}