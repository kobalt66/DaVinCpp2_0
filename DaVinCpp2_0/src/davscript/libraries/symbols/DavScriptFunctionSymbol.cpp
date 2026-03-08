#include "DavScriptFunctionSymbol.h"
#include <utility>

namespace davincpp::davscript
{
    DavScriptFunctionSymbol::DavScriptFunctionSymbol(
        int scopeDepth,
        uint32_t functionPtr,
        std::function<void(DavScriptVirtualMachine*)> function
    ) : DavScriptSymbol(scopeDepth, SymbolType::FUNCTION),
        m_FunctionPtr(functionPtr),
        m_Function(std::move(function))
    { }

    uint32_t DavScriptFunctionSymbol::getFunctionPtr() const
    {
        return m_FunctionPtr;
    }

    std::function<void(DavScriptVirtualMachine*)> DavScriptFunctionSymbol::getFunction() const
    {
        return m_Function;
    }
}
