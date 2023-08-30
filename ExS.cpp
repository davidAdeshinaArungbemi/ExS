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

void ExS::loop(std::string &expr)
{
    if (string_a_number(expr))
    {
        return;
    }
    else
    {
        ExS::IntCharMap operator_pos_map = verify_and_collect_pos(expr);
        // std::cout << "check";
        size_t priority_index = choose_operator(operator_pos_map);
        char priority_operator = operator_pos_map[priority_index];
        switch (priority_operator)
        {
        case '^':
            try
            {
                // std::cout << "check";
                auto operator_itr = operator_pos_map.find(priority_index);
                float left_val, right_val;
                if (operator_pos_map.begin() != operator_itr && std::prev(operator_pos_map.end()) != operator_itr)
                {
                    std::cout << "check" << std::endl;
                    size_t prev_operator_index = std::distance(operator_pos_map.begin(), std::prev(operator_itr));
                    // left_val = std::stof(expr.substr(prev_operator_index + 1, priority_index - prev_operator_index));
                    size_t next_operator_index = std::distance(operator_pos_map.begin(), std::next(operator_itr));
                    // right_val = std::stof(expr.substr(next_operator_index + 1, next_operator_index - priority_index - 1));
                    std::cout << "Left operand: " << expr.substr(prev_operator_index + 1, priority_index - prev_operator_index) << std::endl;
                    std::cout << "Right operand: " << expr.substr(next_operator_index, next_operator_index - priority_index - 1) << std::endl;
                }
                else
                {
                    // std::cout << expr.substr(0, priority_index) << std::endl;
                    left_val = std::stof(expr.substr(0, priority_index));
                    // std::cout << expr.substr(priority_index + 1, expr.length() - priority_index - 1) << std::endl;
                    right_val = std::stof(expr.substr(priority_index + 1, expr.length() - priority_index - 1));
                }
                // std::cout << left_val << std::endl;
                // std::cout << right_val << std::endl;
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
