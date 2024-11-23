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
      * [Python in Bazel](#python-in-bazel)
      * [Python StandAlong](#standalong-python-env-like-jupter-or-ipython)
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
  - Define and implement in this wheel **ONLY ONE** interface between Python / C++ based on, with what input and output parameter is only raw binary data blob:
    - the native cross programming framework
    - Inter process communication, e.g. through local unix socket
  - Find an IDL to supports both Python / C++ bindings, which can help us serialize / deserialize binary data on both Python / C++ side to give us the easy/scalable approach to encode / decode the native / user-defined data structure in Python / C++ with limited effort.

In this wheel, [protobuf](https://github.com/protocolbuffers/protobuf) from google is choosen, which can support most of the requirements.

### NOTE THAT:
The this wheel now is based on the version of:
  - .proto file: `proto3`
  - protoc compiler: `libprotoc 27.1` 

## Integration
### Old School Homemade Workspace
Only supported by the old version [v1_0_0_0_makefile](https://github.com/xingxing0468/wheels/tree/v1_0_0_0_makefile/PythonAndCpp#build)

### Bazel
Until now this repository has not been registered in the BCR, so we have to use legacy bazel approaches like `new_git_repository` / `http_archive` / `new_local_repository` to integrate this repository as the 3rd party upstream from your bazel workspace.

And with the support of bazel, everything becomes quite simple and straight forward. Just add the 3rd party deps on your own C++ / Python target, then everything is ready to go. For more details just refer to our example repo's [bazel src](https://github.com/xingxing0468/test_python_cpp/tree/v1_2_0_1/WORKSPACE.bzlmod).

Note that there is still additional 3rd party dependencies needed even we already put this repo in the upstream, just refer to [WORKSPACE.bzlmod](https://github.com/xingxing0468/test_python_cpp/tree/v1_2_0_1/WORKSPACE.bzlmod) and [MODULE.bazel](https://github.com/xingxing0468/test_python_cpp/tree/v1_2_0_1/MODULE.bazel) in our example repository.

## Usage
### Protobuf
First the protobuf interfaces have to been defined and to be built to support both C++ and Python binding. [proto interfaces](https://github.com/xingxing0468/test_python_cpp/tree/v1_2_0_1/src/interface)

### C++
  - Native implementation of the service we want to support. [Service Impl](https://github.com/xingxing0468/test_python_cpp/tree/v1_2_0_1/src/cpp/service_implementation/mm_service/)
  - Implementation of the protobuf service, e.g. some codec between internal data structure and protobuf data structure. [Protobuf service Impl](https://github.com/xingxing0468/test_python_cpp/tree/v1_2_0_1/src/cpp/service_implementation/mm_service)
  - Service factory plugin. Register the protobuf service above and make it visible for the plug-in mechamism. [Service factory plugin]()

### Python
Due to the C++ implementation plugin deployment
  - With the single process approach, its has to been copied to somewhere and been dynamic loaded in the python, but after deployment, the folder structure deviates from the bazel runfiles, we can not support it in the current version python standalong.
  - With the python client with service daemon connected by local IPC, the C++ implementation plugins are hardcoded to `/tmp/`, so even in the standalong python environment its possible.

 |                | With bazel | Python standalong |
 -----------------|------------|-------------------|
 | Single process |     ✅    |         ❌        |
 | Via IPC        |     ✅    |         ✅        |

**NOTE THAT**:
  With the IPC approach, its **MANDATORY** to [deploy the C++ plugins](https://github.com/xingxing0468/test_python_cpp/blob/45c3e17abc94013a3afa432f8486fa7ee262ef26/src/cpp/service_factory/mm_service_factory/BUILD#L29) and launch the service daemon before running the python.
  ```shell
bazel run --config=single_process //src/cpp/service_factory/mm_service_factory:MmServicePlugin
bazel run --config=single_process @z_python_cpp//src/cpp/service_deamon:service_deamon
  ```
  If sometime the service deamon failed to lunch because of the socket file, just rm the existing one `/tmp/IpcSocket`

#### Python in Bazel
- [BUILD file](https://github.com/xingxing0468/test_python_cpp/blob/v1_2_0_1/src/python/example/BUILD)
- [Example code](https://github.com/xingxing0468/test_python_cpp/blob/v1_2_0_1/src/python/example/example.py)
- [Python tests](https://github.com/xingxing0468/test_python_cpp/blob/v1_2_0_1/src/python/example/test_mm_service.py)

#### Standalong python env like jupter or ipython
- Build a python zip package first includes all the python dependence.
``` shell
bazel build --config=single_process  //src/python/example:example --build_python_zip
```
- Unzip the output zip package into somewhere, e.g. `'/home/zett/python_executable/example`
- Import the python system path including this folder and the `_main` under it. [Reference here](https://github.com/xingxing0468/test_python_cpp/blob/v1_2_0_1/example_bazeless_env.ipynb)

## Further Development
Dockerize the service deamon.


