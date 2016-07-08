/***
 * 
 * Copyright 10/12/2015 William Taylor wi11berto@yahoo.co.uk
 *  
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
***/

#include "main.h"

using namespace std;
using namespace ioc;

class PersonPrinter : IPrinter 
{
    IoC_Container * container;
    IBirthService * birthService;
    INameService * nameService;
    IAgeService * ageService;
public:
    explicit PersonPrinter(IoC_Container * container)
        : birthService(nullptr), nameService(nullptr), ageService(nullptr)
    {
        this->container = container;
    }

    ~PersonPrinter() {
        std::cout << "delete PersonPrinter" << std::endl;
\
    }

    void print() override {
        container->query(&birthService, &nameService, &ageService);

        cout << endl << nameService->name() << " is ";
        cout << ageService->age() << " and was born in ";
        cout << birthService->country() << endl << endl;
    }
};

template<class BirthService, class NameService, class AgeService>
void run(IoC_Container * container) {
    container->unlock();
    container->supply<IBirthService, BirthService>();
    container->supply<INameService, NameService>();
    container->supply<IAgeService, AgeService>();

    container->fetch<IPrinter>()->print();
    container->lock();
}

int main(int argc, char * argv[]) {
    cout << endl << " - IoC.HelloWorld Example " << library_version() << endl;
    cout << "--------------------------" << endl;
    
    {
        auto container = make_injection_container();
        container->supply<IPrinter, PersonPrinter>(make_single_instance());

        run<DummyBirthService, DummyNameService, DummyAgeService>(container.get());
        run<MyBirthService, MyNameService, MyAgeService>(container.get());
    }

    return cin.get();
}
