class Printer
{
    static int id;
public:
    int get_id() const {return id;}
    void set_id(int value) { id = value; }
};

int main()
{
    Printer p1;
    Printer p2; // its bad that you can create more
    // actually the storage goes to a static int
    // they use the same instance
    // really bad idea, dont use it
    // they will all have the same id
    int id = p1.get_id();
}
