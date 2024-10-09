# CPP implementation for Python to call

* [Background](#background)
  * [How the idea comes](#how-the-idea-comes)
  * [Use Cases](#use-cases)
* [Design Purpose](#design-purpose)
  * [Example](#example)
  * [Approach](#approach)
  * [NOTE THAT](#note-that)
* [Integration](#integration)
  * [Old School](#old-school-homemade-workspace)
  * [Bazel](#bazel)
* [Usage](#usage)
  * [Protobuf](#protobuf)
  * [C++](#c)
  * [Python](#python)
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

## Integration
### Old School Homemade Workspace
No longer supported

### Bazel
Until now this repository has not been registered in the BCR, so we have to use legacy bazel approaches like `new_git_repository` / `http_archive` / `new_local_repository` to integrate this repository as the 3rd party upstream from your bazel workspace.

And with the support of bazel, everything becomes quite simple and straight forward. Just add the 3rd party deps on your own C++ / Python target, then everything is ready to go. For more details just refer to our example repo's [src]().

Note that there is still additional 3rd party dependencies needed even we already put this repo in the upstream, just refer to [WORKSPACE.bzlmod]() and [MODULE.bazel]() in our example repository.

## Usage
### Protobuf
First the protobuf interfaces have to been defined and to be built to support both C++ and Python binding. [proto interfaces]()

### C++
  - Native implementation of the service we want to support. [Service Impl]()
  - Implementation of the protobuf service, e.g. some codec between internal data structure and protobuf data structure. [Protobuf service Impl]()
  - Service factory plugin. Register the protobuf service above and make it visible for the plug-in mechamism. [Service factory plugin]()

### Python
Already ready to go with the expected plugins and dependencies correctly described in the [BUILD](). In the python file just import the needed modules and call the protobuf interfaces. [example]().


## Further Development
Since the support of real-time interactive python environment with bazel is not suppprted, and with the current cross language the python pachage supported by native bazel it not working anymore, we are now developing another deamon version of the apporaches. It will
  - Put all the C++ implementation into a servie deamon purely implemented by C++ and can launch independent with `bazel run` for instance.
  - The caller then becomes a pure python environment and can run independently, we can package the python with the native bazel and to make it runnable in another real-time interactive python environment, e.g. `Jupter` / `IPython`.