#pragma once
#include <memory>
#include <tokens/TokenData.h>

namespace davincpp::davscript
{
class DavScriptSymbol : public std::enable_shared_from_this<DavScriptSymbol>
{
public:
    DavScriptSymbol(int scopeDepth, SymbolType symbolType);
    virtual ~DavScriptSymbol() = default;

    template<class T>
    [[nodiscard]] std::shared_ptr<T> castToSymbolType();

    [[nodiscard]] int        getScopeDepth() const;
    [[nodiscard]] SymbolType getSymbolType() const;

protected:
    int        m_ScopeDepth;
    SymbolType m_SymbolType;
};
}  // namespace davincpp::davscript
