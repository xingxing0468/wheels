# CPP implementation for Python to call

* [Background](#background)
  * [How the idea comes](#how-the-idea-comes)
  * [Use Cases](#use-cases)
* [Design Purpose](#design-purpose)
  * [Example](#example)
  * [Approach](#approach)
  * [NOTE THAT](#note-that)
* [Usage](#usage)
  * [Protobuf](#protobuf)
  * [C++](#c)
  * [Python](#python)
  * [Build](#build)
* [Integration](#integration)
  * [Old School](#old-school-homemade-workspace)
  * [Modern Worksapce](#modern-with-3rd-party-workspace-environmenteg-bazel)
* [Further development](#further-development)

## Background
### How the idea comes
Cross language programming is always a topic for software developers, because:
- Every language has its advantage and disadvange.
- In upstream / 3rd party software / dependency, programming language is out of control.
- Hardware / midware / platform limitation.
- Personal preference / interests.
- ...

Therefore, for high level language / script normally already has a mature enough lib/framework included to support the cross language programming. For instance, in Python, to call interfaces which are implemented by C++ language. Due to personal interests and daily work use-cases, currently this wheel is focusing on the Python to call C++ implementation.

### Use Cases
- Speed up the application layer / end point programming, for rapid statics / prototyping / big data analyze/ ...
- Directly use of the underlying implementation with C++, which comes from 3rd parting C++ library / buy software / ...
- Optimization of the underlying implementation for computating / memory resource expensive algorithms, e.g. mathmatic ones.

## Design Purpose
This wheel is **NOT** targeting on how to implement cross language programming between Python and C / C++.

As mentioned above, in Python there is already a mature enough framework to support the cross language programming between Python and C/C++, just go to the official documentaion and it is easy to find and understand.

But, this is always a topic that how to unify the input / output data structure between Python and C++. We have a huge deviation between all the built-in / user defined data structures in Python and C++, also the native cross language framework in Python is **NOT** possible to support all the complicated data structure and, always customized codec is required on both Python / C++ side. It costs developers' more efforts to undertand the underlying implementation of the cross language programming framework instead of focus on the use-case itsself.

Therefore, this wheel actually targets to enable developer to easily understand and define the data structure between Python / C++, instead of spend too much efforts for the implementation of the codec for every new interface between Python / C++.

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

using EnvCollectionT = std::vector<std::tuple<PointT, EmTypeT>>;
```
In Python we are somehow expecting we can call the interface and get the filtered coordinates like:
```python
points = FilterEnv(ems, EmTypeT)
for p : points:
  print("Filtered point: [{}, {}]".format(p.x, p.y))
```
Then there always comes to the problem that how can we give the codec to convert Python structure(Dict, List, ...) to the C++ struct, and after the call to convert the result back to some application python developer friendly data structure in Python(e.g. List)

### Approach:
Here we comes to the idea of the following 2 steps to solve the problem:
  - Define and implement in this wheel **ONLY ONE** interface between Python / C++ based the native cross programming framework, with whose input and output parameter is only raw binary data blob.
  - Find an IDL to supports both Python / C++ bindings, which can help us serialize / deserialize binary data on both Python / C++ side to give us the easy/scalable approach to encode / decode the native / user-defined data structure in Python / C++ with limited effort.

In this wheel, [protobuf](https://github.com/protocolbuffers/protobuf) from google is choosen, which can support most of the requirements.

### NOTE THAT:
The this wheel now is based on the version of:
  - .proto file: `proto3`
  - protoc compiler: `libprotoc 27.1` 

## Usage
### Protobuf
  - Download the proco compilier from [protobuf](https://github.com/protocolbuffers/protobuf), the trial used in the wheel is based on the `libprotoc 27.1`.
  - Define the new service in [proto file](src/interface/IEmService.proto) for the all the new interfaces and input/output binding.
### C++
  - Declear the overriding [class](src/cpp/service_implementation/ZEmService.h) for the service generated from [proto file](src/interface/IEmService.proto).
  - Implement the rpc service calls from the [proto file](src/interface/IEmService.proto), in the [service cpp](src/cpp/service_implementation/ZEmService.cpp). To achieve this, we may need to call the existing C++ implementation and fill the data fields one by one.
  - Add a new [service factory](src/cpp/service_factory/ZEmServiceFactory.h) to generate the new protobuf service.
  - Add this new service factory together with a name into global `ServiceFactories` in [service dispatcher](src/cpp/utils/ZServiceDispatcher.cpp).
### Python
  - With directly using Python bindings from protobuf, all the Python API is easily found on [protobuf website](https://googleapis.dev/python/protobuf/latest/).
  - **NOTE THAT:** Actually Python binding is already a great interface for application developer to deal with all the use-cases, its **NOT** recommanded to have a layer in between to define independent interfaces, and to implement the codec between protobuf type and independent type, **HIGHLY RECOMMANDED** that directly program the application based on protobuf, because:
    - Protobuf binded types already supports mature enough APIs, e.g. [I/O](https://googleapis.dev/python/protobuf/latest/google/protobuf/json_format.html), debug, ...
    - To construct an independent layer already sounds like the beginning for a scalable and well-design product, which violates the design purpose of this wheel, e.g. rapid prototyping. For a scalable / well-design project / product, it has to been evaluate again carefully if Python with C++ approach is a better alternative compare to the pure C++ one, because the latest modern C++(e.g. [C++20](https://en.cppreference.com/w/cpp/20)) has already been improved quite a lot and becomes more user-friendly.
### Build
The build system in this wheel is just a very simple native MAKEFILE based system, a prototype one even without basic dependency/clean-up/rebuilt/... mechanism, only to be used to proove the concept.
- Set the `protoc` compiler in [Makefile](Makefile).
- ```shell
  make
  source .out/setup.sh
  ```
- Now its the time to play with the framework. Please refer to exisiting [trial](trial.py). Happy hacking!
## Integration
### Old School Homemade Workspace
Since the purpose of this wheel is to enable the rapid prototypes with Python, its always the first choice to solve the dependencies with **QUICK** and **DIRTY** approach instead of make it a real 'project'. Therefore, this intergation solution is **HIGHLY** recommanded for the further Python scripts with [Ipython](https://ipython.org/) / [Jupter Notebook](https://jupyter.org/)/ ...
Here are the mandantory artifacts:
- C++ implmentation library: `libzprobe_impl.so` in `src/cpp/.out` after `make`, directly set the `LD_LIBRARY_PATH` with
  ```shell
    export LD_LIBRARY_PATH = $LD_LIBRARY_PATH:$WORKSPACE/src/cpp/.out/
  ```
  or distribute it somewhere else first.
- Python module setup library: `zprobe.cpython-310-x86_64-linux-gnu.so` after `make`, directly set the `PYTHONPATH` with
  ```shell
    export PYTHONPATH = $PYTHONPATH:$WORKSPACE/.out/
  ```
  or distribute it somewhere else first.
- Generated Python files from `protoc`(protobuf compiler) based on the *.proto* file interface, e.g. `proto_out/IEmService_pb2.py` after `make`, directly set the `PYTHONPATH` with
  ```shell
    export PYTHONPATH = $PYTHONPATH:$WORKSPACE/.proto_out/
  ```
  or distribute them somewhere else first.
- Python service implementation files fullfiling the protobuf requirement:
  - [z_service_channel.py](src/python/z_service_channel.py)
  - [z_service_controller](src/python/z_service_controller.py)
  - [z_service_package_helper.py](src/python/z_service_package_helper.py)
  - [i_service_probe.py](src/python/service_probe/i_service_probe.py)
  - [z_c_extension_service_probe.py](src/python/service_probe/z_c_extension_service_probe.py)
  directly set the `PYTHONPATH` with
  ```shell
    export PYTHONPATH = $PYTHONPATH:$WORKSPACE/src/python
  ```
  or distribute them somewhere else first.
- Existing upstream share library from C++ implementation.(**TODO**)

### Modern with 3rd Party Workspace environment(e.g. bazel)

## Further Development
- Make this wheel as a [bazel](https://github.com/bazelbuild/bazel) workspace to be more easier to integrated to the application with bazel build system.