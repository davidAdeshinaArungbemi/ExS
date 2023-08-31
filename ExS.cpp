#include "ExS.hpp"

bool ExS::is_a_number(const char &character)
{
    int8_t eight_bit_int = static_cast<int8_t>(character);
    if (eight_bit_int > 47 && eight_bit_int < 58)
    {
        return true;
    }
    return false;
}

bool ExS::is_an_operator(const char &character)
{
    switch (character)
    {
    case '^':
    case '(':
    case ')':
    case '+':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

bool ExS::is_a_minus_or_dot(const char &character)
{
    if (character == '-' || character == '.')
        return true;

    return false;
}

bool ExS::string_a_number(const std::string &expr)
{
    for (size_t i = 0; i < expr.length(); i++)
    {
        if (!(is_a_number(expr[i]) || is_a_minus_or_dot(expr[i])))
        {
            return false;
        }
    }
    return true;
}

ExS::IntCharMap ExS::verify_and_collect_pos(const std::string &expr)
{
    IntCharMap operator_map;
    for (size_t i = 0; i < expr.length(); i++)
    {
        assert(is_a_number(expr[i]) || is_an_operator(expr[i]) || is_a_minus_or_dot(expr[i]));

        if (is_an_operator(expr[i]))
        {
            operator_map[i] = expr[i];
        }
    }

    return operator_map;
}

size_t ExS::choose_operator(const ExS::IntCharMap &operator_pos_map)
{
    int priority_level = -1;
    char priority_char = '+';
    size_t return_index;

    for (auto i : operator_pos_map)
    {
        if ((int)operator_map_order[i.second] > priority_level)
        {
            priority_level = (int)operator_map_order[i.second];
            return_index = i.first;
        }
    }

    return return_index;
}

std::tuple<double, double> ExS::bi_operator_operands(std::string &expr, size_t &priority_index, IntCharMap &operator_pos_map)
{
    auto operator_itr = operator_pos_map.find(priority_index);
    double left_val, right_val;
    if (operator_pos_map.begin() != operator_itr || std::prev(operator_pos_map.end()) != operator_itr)
    {
        size_t prev_operator_index = (*std::prev(operator_itr)).first;
        left_val = std::stof(expr.substr(prev_operator_index + 1, priority_index - prev_operator_index - 1));
        size_t next_operator_index = (*std::next(operator_itr)).first;
        right_val = std::stof(expr.substr(priority_index + 1, next_operator_index - priority_index - 1));
    }
    else
    {
        left_val = std::stof(expr.substr(0, priority_index));
        right_val = std::stof(expr.substr(priority_index + 1, expr.length() - priority_index - 1));
    }
    return std::make_tuple(left_val, right_val);
}

std::string ExS::update_expression(std::string &expr, double &result, size_t operator_index, IntCharMap &operator_pos_map)
{
    size_t begin_index = (*std::prev(operator_pos_map.find(operator_index))).first + 1;
    size_t end_index = (*std::next(operator_pos_map.find(operator_index))).first - 1;
    std::string before_sub_expr = expr.substr(0, begin_index);
    std::string after_sub_expr = expr.substr(end_index + 1, expr.length() - end_index);
    std::string string_result = std::to_string(result);
    return before_sub_expr + string_result + after_sub_expr;
}

void ExS::loop(std::string &expr)
{
    if (string_a_number(expr))
    {
        return;
    }
    else
    {
        ExS::IntCharMap operator_pos_map = verify_and_collect_pos(expr);
        size_t priority_index = choose_operator(operator_pos_map);
        char priority_operator = operator_pos_map[priority_index];
        switch (priority_operator)
        {
        case '^':
            try
            {
                size_t begin_index, end_index;
                double left_val, right_val;
                std::tie(left_val, right_val) = bi_operator_operands(expr, priority_index, operator_pos_map);
                double result = powf(left_val, right_val);
                assert(!(std::isinf(result)) && "Result is infinity");

                std::cout << update_expression(expr, result, priority_index, operator_pos_map);
                std::cout << result << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        case '(':
            break;
        case '+':
            break;
        case '*':
            break;
        case '/':
            break;
        }
        // loop(expr);
    }
}

int main(int, char **)
{
    std::cout << "Enter expression: ";
    std::string expr;
    std::cin >> expr;
    ExS::loop(expr);
}
