#pragma once
#include <functional>
#include <unordered_map>

#include "LogManager.h"

namespace FEXCore {

class CPUIDEmu final {
private:
  constexpr static uint32_t CPUID_VENDOR_INTEL1 = 0x756E6547; // "Genu"
  constexpr static uint32_t CPUID_VENDOR_INTEL2 = 0x49656E69; // "ineI"
  constexpr static uint32_t CPUID_VENDOR_INTEL3 = 0x6C65746E; // "ntel"

  constexpr static uint32_t CPUID_VENDOR_AMD1 = 0x68747541; // "Auth"
  constexpr static uint32_t CPUID_VENDOR_AMD2 = 0x69746E65; // "enti"
  constexpr static uint32_t CPUID_VENDOR_AMD3 = 0x444D4163; // "cAMD"

public:
  void Init();

  struct FunctionResults {
    // Results in registers EAX, EBX, EDX, ECX respectively
    uint32_t Res[4];
  };

  FunctionResults RunFunction(uint32_t Function) {
    LogMan::Throw::A(FunctionHandlers.find(Function) != FunctionHandlers.end(), "Don't have a CPUID handler for 0x%08x", Function);
    return FunctionHandlers[Function]();
  }
private:

  using FunctionHandler = std::function<FunctionResults()>;
  void RegisterFunction(uint32_t Function, FunctionHandler Handler) {
    FunctionHandlers[Function] = Handler;
  }

  std::unordered_map<uint32_t, FunctionHandler> FunctionHandlers;

  // Functions
  FunctionResults Function_0h();
  FunctionResults Function_01h();
  FunctionResults Function_07h();
  FunctionResults Function_8000_0000h();
  FunctionResults Function_8000_0001h();
  FunctionResults Function_8000_0007h();

  FunctionResults Function_Reserved();
};
}
