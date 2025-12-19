#include "Name.hpp"
bool NAME::numLetter(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}
bool NAME::visible(char c)
{
    return (c > ' ' && c < 127);
}
bool NAME::common(char c)
{
    return (c > ' ' && c < 127) && (c != '\"' && c != '\"');
}