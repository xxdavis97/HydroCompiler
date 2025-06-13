#include <optional>
#include "TokenType.h"

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};