## Dependency Injection Container for C++.

IoC is a dependency injection container for C++ applications.

![alt tag](http://www.brandsoftheworld.com/sites/default/files/styles/logo-thumbnail/public/042014/c_0.png?itok=NGrw5nRV)

## Overview

This project is just a simple implementation of constructor based dependency injection in C++. It’s small and lightweight and will be taken forward and improved as time progresses. Type information is captured in lambdas and then constructed and deallocated when new instances of this type are asked for from the container.

It allows you to easily create mocks of abstractions for easier testing and allows you to write new exciting implementations which can sit alongside older code without the need to change allocations.

## Example

```c++
class Mapping : public Interface {
 Abstraction * abs;
 Mapping(ioc::IoC_Container * container) {
  // Request them
  container->query(&abs);
 }
}

void bootstrapper() {
  auto container = ioc::make_injection_container();
  container->supply<Abstraction, Dependency>(); // Supply implementations
  container->supply<Interface, Mapping>();
  ...
}
```

## Installation

You can get a copy with your normal clone command. The project is currently a Visual Studio solution however it won’t be too hard to port the source code into other more cross platform IDE's if you need to.

``` git clone https://github.com/WilliamTaylor/ioc ```

As part of the project you will find the core lib, a helloworld example and some unit tests.

## Features
- Dynamically Injection class dependency's via the IoC_Container object.
- Remove memory leaks through lifetime objects attached to objects.
- Easily change mappings for easier testing and better customizability.
- Allows easy mocking of implementations for easy unit testing.

## Future Features

* Inject and resolve key based globals.
* Object analysis see what objects as used most.
* Memory information on objects constructed.
* Lockable containers

## Links
[DI Explained]("https://en.wikipedia.org/wiki/Dependency_injection"),  [IoC Explained]("https://en.wikipedia.org/wiki/Inversion_of_control")
