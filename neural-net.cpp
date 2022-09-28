class Net {
    public:
        void net(topology);
        void backProp(targetVals);
        void getResults(resultVals) const;

    private:
};

int main() {
   Net myNet(topology);
   myNet.feedForward(inputVals);
   myNet.backProp(targetVals);
   myNet.getResults(resultVals);
}
