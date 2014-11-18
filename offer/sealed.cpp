class SealedClass1
{
public:
    static SealedClass1* getInstance() {
        return new SealedClass1();
    }
    
    static void DeleteInstance(SealedClass1* pInstance) {
        delete pInstance;
    }
    
private:
    SealedClass1(){};
    
    ~SealedClass1(){};
};

template <typename T>
class MakeSealed
{
    friend T;
private:
    MakeSealed() {};
    
    ~MakeSealed() {};
};


class SealedClass2 : virtual public MakeSealed<SealedClass2>
{
public:
    SealedClass2() {};
    
    ~SealedClass2() {};
};

