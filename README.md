## Dependency Injection Container for C++.

This project is just a simple implementation of constructor based dependency injection in C++. It’s small and lightweight and will be taken forward and improved as time progresses.

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

## Features
- Dynamically Injection class dependency's via the IoC_Container object.
- Remove memory leaks through lifetime objects attached to objects.
- Easily change mappings for easier testing and better customizability.
- Allows easy mocking of implementations for easy unit testing.

## Relevant Links
http://williamtaylor.github.io/IoC/<br />
https://en.wikipedia.org/wiki/Dependency_injection<br />
https://en.wikipedia.org/wiki/Inversion_of_control
