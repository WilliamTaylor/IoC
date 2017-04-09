#include "main.h"

using std::cout;
using std::endl;
using std::cin;

class PersonPrinter : IPrinter 
{
    IBirthService * birthService;
    INameService * nameService;
    IAgeService * ageService;
public:
    explicit PersonPrinter(dil::container * container) 
    {
        container->query(&birthService, &nameService, &ageService);
    }

    void print() override 
    {
        cout << nameService->name() << ", ";
        cout << ageService->age() << ", ";
        cout << birthService->country() << endl;
    }
};

int main(int argc, char * argv[]) 
{
    cout << endl << "HelloWorld Example " << dil::library_version() << endl << endl;

    const auto container = dil::make_injection_container();
    container->supply<IBirthService, MyBirthService>();
    container->supply<INameService, MyNameService>();
    container->supply<IAgeService, MyAgeService>();
    container->supply<IPrinter, PersonPrinter>();

    const auto printer = container->fetch<IPrinter>();
    printer->print();
    
    return std::cin.get();
}