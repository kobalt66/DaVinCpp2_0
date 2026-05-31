#pragma once
#include <functional>
#include <libraries/symbols/DavScriptSymbol.h>

namespace davincpp::davscript
{
class DavScriptVirtualMachine;

class DavScriptFunctionSymbol final : public DavScriptSymbol
{
  public:
	DavScriptFunctionSymbol(int scopeDepth, uint32_t functionPtr,
	                        std::function<void(DavScriptVirtualMachine*)> symbolFunction);

	[[nodiscard]] uint32_t getFunctionPtr() const;
	[[nodiscard]] std::function<void(DavScriptVirtualMachine*)> getFunction() const;

  private:
	uint32_t m_FunctionPtr;
	std::function<void(DavScriptVirtualMachine*)> m_Function;
};
} // namespace davincpp::davscript
