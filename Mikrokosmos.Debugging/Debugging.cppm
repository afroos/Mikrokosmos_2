module;

#include <iostream>

export module Mikrokosmos.Debugging;

export namespace mk
{
    template <typename Expression>
    void print(Expression expression) noexcept
    {
        std::cout << expression << std::endl;
    }

    template <typename Expression, typename... ExpressionList>
    void print(Expression expression, ExpressionList... rest)
    {
        std::cout << expression << std::endl;
        print(rest...);
    }

    /*template <typename... expressionlist>
    void print(expressionlist... expressionlist)
    {
        (std::cout << ... << expressionlist) << std::endl;
    }*/
}