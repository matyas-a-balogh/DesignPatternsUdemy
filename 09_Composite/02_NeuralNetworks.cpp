#include "../header.h"

// fwd decl
struct Neuron;

// CRTP base
template <typename Self> 
struct SomeNeurons
{
    template <typename T> 
    void connect_to(T& other)
    {
        // static cast so that we iterate the right kind of collection
        // this object can be a single Neuron or a NeuronLayer
        for (Neuron& from : *static_cast<Self*>(this))
        {
            // other can also be a single Neuron or a NeuronLayer
            for (Neuron& to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

// ordering has to cahnge, fwd decl is not enough

// scalar 
// Single neuron, but it behaves like a collection of 1 element
struct Neuron : SomeNeurons<Neuron>
{
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron() { 
        static int id{1};
        this->id = id++;
    }

    // void connect_to(Neuron& other)
    // {
    //     out.push_back(&other);
    //     other.in.push_back(this);
    // }

    // for the range-based for loop
    // begin and end needed
    Neuron* begin() {return this;}
    Neuron* end() {return this+1;}
    
    friend ostream &operator<<(ostream &os, const Neuron &obj)
    {
        for (Neuron* n : obj.in){
            os << n->id << "\t-->\t[" << obj.id << "]" << endl;
        }
        for (Neuron* n : obj.out){
            os << "[" << obj.id << "]\t-->\t" << n->id << endl;
        }
        return os;
    }
};

// A layer is a collection of Neurons
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while(count --> 0) 
            emplace_back(Neuron{});
    }

    friend ostream &operator<<(ostream &os, const NeuronLayer &obj)
    {
        for (auto& n : obj) os << n;
        return os;
    }
};

int main()
{
    Neuron n1, n2;
    n1.connect_to(n2);
    cout << n1 << n2 << endl;

    NeuronLayer layer1{2}, layer2{3};

    n1.connect_to(layer1);      // one neuron to many neurons
    layer2.connect_to(n2);      // many neurons to one neuron
    layer1.connect_to(layer2);  // many neurons to many neurons

    return 0;
}
