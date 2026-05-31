#include "DavScriptSymbol.h"
#include <Console.h>
#include <error/DavScriptException.h>
#include <libraries/symbols/DavScriptFunctionSymbol.h>

namespace davincpp::davscript
{
DavScriptSymbol::DavScriptSymbol(int scopeDepth, SymbolType symbolType)
    : m_ScopeDepth(scopeDepth)
    , m_SymbolType(symbolType)
{
}

template <class T>
std::shared_ptr<T> DavScriptSymbol::castToSymbolType()
{
	if (const std::shared_ptr<T> symbol = std::dynamic_pointer_cast<T>(std::shared_ptr(shared_from_this()))) {
		return symbol;
	}

	throw DavScriptException(
	    Console::fmtTxt("Failed to cast davscript symbol object: DavScriptSymbol::castToSymbolType(",
	                    SYMBOL_TYPE2STRING.at(m_SymbolType), ")"));
}

int DavScriptSymbol::getScopeDepth() const
{
	return m_ScopeDepth;
}

SymbolType DavScriptSymbol::getSymbolType() const
{
	return m_SymbolType;
}

template std::shared_ptr<DavScriptFunctionSymbol> DavScriptSymbol::castToSymbolType<DavScriptFunctionSymbol>();
} // namespace davincpp::davscript
