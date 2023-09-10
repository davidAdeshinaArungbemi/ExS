#ifndef DESC
#define DESC
#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>
#include <map>
#include <tuple>
#include <cmath>
namespace ExS
{
    namespace ExS
    {

        typedef std::vector<size_t> PositionVector;
        typedef std::map<size_t, char> IntCharMap;
        bool is_a_number(const char &character);
        bool string_a_number(const std::string &expr);
        bool is_an_operator(const char &character);
        bool is_a_minus_or_dot(const char &character);
        std::string remove_whitespace(std::string &expr);
        std::string loop(std::string expr);
        std::string update_expression(std::string &expr, double &result, size_t operator_index, IntCharMap &operator_pos_map);
        size_t choose_operator(const ExS::IntCharMap &operator_map);
        std::tuple<double, double> bi_operator_operands(std::string &expr, size_t &priority_index, IntCharMap &operator_pos_map);
        IntCharMap verify_and_collect_pos(const std::string &expr);
    }
    std::string evaluate(std::string expr);
}

#endif
