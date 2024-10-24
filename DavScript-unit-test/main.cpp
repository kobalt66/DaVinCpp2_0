#include <DaVinCppExceptions.h>
#include <DaVinCppFileSystem.h>
#include <lexer/DavScriptLexer.h>

int main()
{
    try {
        davincpp::davscript::DavScript davScript("../test.dav");
        davincpp::davscript::DavScriptLexer lexer(davScript);
    } catch (std::runtime_error& exception) {
        throw davincpp::davincpp_error(exception.what());
    }

    return 0;
}
