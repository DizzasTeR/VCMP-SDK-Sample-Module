# VCMP SDK Sample Module

This sample module can be used as a base to get started with a C++ module based server implementation with the power of [nod](https://github.com/fr00b0/nod) signaling. Most of the necessary callbacks have been signalized, if you think you need the remaining one, you may add them manually.

## Noteworthy info

The onPlayerCommand signal is customized to a more traditional format, such as

```cpp
signal_onPlayerCommand.connect([](int32_t playerId, std::string command, std::vector<std::string> args) {
  // command :: May be NULL if no command was specified
  // args :: Vector size may be zero if no arguments were specified
});
```
