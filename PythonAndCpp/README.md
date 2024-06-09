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

## Example:

## Usage

## Integration

## Further development