# CPP implementation for Python to call

## Background
### How the idea comes
Cross language programming is always a topic for software developers, because:
- Every language has its advantage and disadvange.
- Upstream / 3rd party software / dependency language which is out of control.
- Hardware / midware / platform limitation.
- Personal preference / interests.
- etc...
Therefore, for high level language / script normally already has a mature enough lib/framework included to supports the cross language programming, for instance, python to call interfaces which is implemented by C++ language. Due to personal interests and daily work use cases, currently this wheel is focus on the python to call C++ implementation.

### Use Cases
- Speed up the application layer / end point programming, for rapid statics / prototyping / big data / ...
- Directly use of the underlying implementation with C++, which could be some 3rd parting C++ library / buy software / ...
- Optimization of the underlying implementation for computating / memory resource expensive algorithms, e.g. mathmatic ones.

## Design Purpose
This wheel is **NOT** targeting on how to implement cross language programming between python and C / C++.

As mentioned above, in python there is already a mature enough framework to support the cross language programming between python and c/c++, just go to the official documentaion and it is easy to find and understand.

But, this is always a topic that how to unify the input / output data structure between python and c++. We have a huge deviation between all the built-in / user defined data structures in python and c++, also the native cross language framework in python is **NOT** possible to support all the complicated data structure and always customized codec is required on both python / C++ side. It costs developers' more efforts to undertand the underlying implementation of the cross language programming framework instead of focus on the use-case its self.

Therefore, this wheel actually is targeting to enable developer easily understand and define the data structure between python / C++, instead of spend too much efforts for the implementation of the codec for every new interface between python / C++.

### Example:
There is an implementation in C++ to filter out the expected environment type
```cpp
std::vector<PointT> FilterE(const EnvCollectionT& es, EmTypeT& type);
```
where the data structure definition is:
```cpp
struct PointT {
  float x{-101.};
  float y{-101.};
};

enum class EmTypeT : std::uint8_t {
  UNKNOWN = 0,
  // ...
};

using EnvCollectionT = std::unordered_map<PointT, EmTypeT, PointTHash>;
```
In Python we are somehow expecting we can call the interface and get the filtered coordinates like:
```python
points = FilterEnv(ems: Dict[PointT, EmTypeT])
for p : points:
  print("Filtered point: [{}, {}]".format(p.x, p.y))
```
Then there always comes to the problem that how can we give the codec to convert python struction(Dict, List, ...) to the C++ struct, and after the call to convert the result back to some application python developer friendly data structure in python(e.g. List)

### Approach:
Here we comes to the idea of the following 2 steps to solve the problem:
  - Define and implement in this wheel **ONLY ONE** interface between Python / C++ based the native cross programming framework, with whose input and output parameter is only raw binary data.
  - Find an IDL to supports both Python / C++ bindings, which can help us serialize / deserialize binary data on both Python / C++ side to give us the easy/scalable approach to encode / decode the native / user-defined data structure in Python / C++ with limited effort.
In this wheel, [protobuf](https://github.com/protocolbuffers/protobuf) from google is choosen, which can support most of the requirements.

### NOTE THAT:
The this wheel now is based on the version of:
  - .proto file: `proto3`
  - protoc compiler: `libprotoc 27.1` 

## Usage
### C++ implementation for protobuf C++ binding
  - Download the proco compilier from [protobuf](https://github.com/protocolbuffers/protobuf), the trial used in the wheel is based on the `libprotoc 27.1` 
  - Define the new service in [proto file](src/interface/IEmService.proto) for the all the new interfaces and input/output binding.
  - Declear the overriding [class](src/cpp/service_implementation/ZEmService.h) for the service generated from [proto file](src/interface/IEmService.proto)
  - Implement the rpc service calls from the [proto file](src/interface/IEmService.proto), in the [service cpp](src/cpp/service_implementation/ZEmService.cpp), to achieve this, we need to call the existing C++ implementation and fill the data fields one by one.
  - Add a new [service factory](src/cpp/service_factory/ZEmServiceFactory.h) to generate the new protobuf service.
  - Add this new service factory together with a name into global `ServiceFactories` in [service dispatcher](src/cpp/utils/ZServiceDispatcher.cpp)


## Integration

## Further development