class Layer {

    // think of return type if we need it
    // const here indicates that the function is not modifying the state of the object calling the method
    public:
        virtual void forward() const = 0;
        virtual void backward() const = 0;

};