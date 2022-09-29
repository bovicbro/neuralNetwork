#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

struct Connection {
    double weight;
    double deltaWeight;
};

class Neuron;

typedef vector<Neuron> Layer;

// ************** class Neuron ****************
class Neuron {
    public:
        Neuron(unsigned numOutputs, unsigned index) {
            m_index = index;
            for (unsigned c = 0; c < numOutputs; ++c){
               m_connections.push_back(Connection());
               m_connections.back().weight = randomWeight();
            }
        };
        double getOutputVal(void) const { return m_outputVal; }
        void setOutputVal(double val) { m_outputVal = val; }
        void feedForward(const Layer &prevLayer){
            double sum = 0.0;
            //loop through all of the neurons from the previous layers
            for (unsigned n=0; n < prevLayer.size(); n++) {
                sum+=prevLayer[n].getOutputVal() * prevLayer[n].m_connections[m_index].weight;
            }
        };

      private:
        static double randomWeight(void) { return rand() /  double(RAND_MAX);}
        unsigned m_index;
        double m_outputVal;
        vector<Connection> m_connections;
};


// ************** class Net ****************
class Net {
    public:

        Net(const vector<unsigned> &topology) {
            unsigned numLayers = topology.size();
            for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
                m_layers.push_back(Layer());
                unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum +1];
                for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
                    m_layers.back().push_back(Neuron(numOutputs, neuronNum));
                    cout << "Made a Neuron!" << endl;
                }
            }
        };

        void feedForward(const vector<double> &inputVals) {

            assert(inputVals.size() == m_layers[0].size() - 1);

            for (unsigned i = 0; i <inputVals.size(); ++i) {
                m_layers[0][i].setOutputVal(inputVals[i]);
            }

            //Forward propagation - for each neuron in each layer, updated forward

            for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
                Layer &prevLayer = m_layers[layerNum-1];
                for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
                    m_layers[layerNum][n].feedForward(prevLayer);
                }
            }

        };

        void backProp(const vector<double> &targetVals) {

        };

        void getResults(vector<double> &resultVals) const {

        };

    private:
        vector<Layer> m_layers;
};

int main() {
    vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);
    Net myNet(topology);

    vector<double> inputVals;
    myNet.feedForward(inputVals);

    vector<double> targetVals;
    myNet.backProp(targetVals);

    vector<double> resultVals;
    myNet.getResults(resultVals);
}
