#include "main.h"

using namespace std;

class PersonPrinter : IPrinter 
{
    dil::container * container;

    IBirthService * birthService;
    INameService * nameService;
    IAgeService * ageService;
public:
    explicit PersonPrinter(dil::container * container)
        : birthService(nullptr), nameService(nullptr), ageService(nullptr)
    {
        this->container = container;
    }

    ~PersonPrinter() {
        std::cout << "delete PersonPrinter" << std::endl;
    }

    void print() override {
        container->query(&birthService, &nameService, &ageService);

        cout << endl << nameService->name() << " is ";
        cout << ageService->age() << " and was born in ";
        cout << birthService->country() << endl << endl;
    }
};

template<class BirthService, class NameService, class AgeService>
void run(dil::container * container) {
    container->unlock();
    container->supply<IBirthService, BirthService>();
    container->supply<INameService, NameService>();
    container->supply<IAgeService, AgeService>();

    container->fetch<IPrinter>()->print();
    container->lock();
}

int main(int argc, char * argv[]) {
    cout << endl << " - IoC.HelloWorld Example " << dil::library_version() << endl;
    cout << "--------------------------" << endl;
    
    {
        auto container = dil::make_injection_container();
        container->supply<IPrinter, PersonPrinter>(dil::make_single_instance());

        run<DummyBirthService, DummyNameService, DummyAgeService>(container.get());
        run<MyBirthService, MyNameService, MyAgeService>(container.get());
    }

    return cin.get();
}
