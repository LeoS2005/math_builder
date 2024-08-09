//
// Created by leonid on 19.07.24.
//
// класс, хранящий строку (функцию) и считающий набор точек
#ifndef MATH_BUILDER_COUNTER_H
#define MATH_BUILDER_COUNTER_H
#include <string>
#include <exception>
#include <vector>
#include <sstream>
#include <stack>
#include <set>
#include <algorithm>
#include <cmath>

// исплючение, при попытке установить приоритет некорректного опратора
struct IncorrectOperator : std::exception {};


/*
приоритет:
1: +,-
2: *,/
3: ^
*/
// функция по операции возвращает приоритет
int Priority(char operation) {
  if (operation == '^') {
    return 3;
  } else if ((operation == '*') || (operation == '/')) {
    return 2;
  } else if ((operation == '-') || (operation == '+')) {
    return 1;
  } else {
    throw IncorrectOperator{};
  }
}

// разбивает строку на подстроки по пробелам
std::vector<std::string> Split(const std::string& str) {
  std::istringstream iss(str);
  std::vector<std::string> tokens;
  std::string token;

  while (iss >> token) {
    tokens.push_back(token);
  }

  return tokens;
}

double Computing(std::string&& function, double x) {
  std::stack<double> operands_stack;
  std::stack<char> operators_stack;
  auto query = Split(function);
  query.erase(query.begin());
  query.erase(query.begin());
  std::vector<char> operators_set{'+', '-', '*', '/', '^'};
  for (auto& i : query) {
    //std::find(operators_set.begin(), operators_set.end(), i[0]);
    if ((std::find(operators_set.begin(), operators_set.end(), i[0]) != operators_set.end())) {

      if ((operators_stack.size() == 0) || (operators_stack.top() == '(') || (Priority(operators_stack.top()) < Priority(i[0]))) {
          operators_stack.push(i[0]);
      } else {

        while (!(operators_stack.empty()) && (Priority(operators_stack.top()) >= Priority(i[0]))) {
          double operand_2 = operands_stack.top();
          operands_stack.pop();
          double operand_1 = operands_stack.top();
          operands_stack.pop();
          if (operators_stack.top() == '+') {
            operators_stack.pop();
            operands_stack.push(operand_1 + operand_2);
          } else if (operators_stack.top() == '-') {
            operators_stack.pop();
            operands_stack.push(operand_1 - operand_2);
          } else if (operators_stack.top() == '*') {
            operators_stack.pop();
            operands_stack.push(operand_2 * operand_1);
          } else if (operators_stack.top() == '/') {
            operators_stack.pop();
            operands_stack.push(operand_1 / operand_2);
          } else if (operators_stack.top() == '^') {
            operators_stack.pop();
            operands_stack.push(std::pow(operand_1, operand_2));
          } else if (operators_stack.top() == '(') {
            // ????
            operators_stack.push('(');
          }
        }
        operators_stack.push(i[0]);
      }
    }

    else if (i == "(") {
      operators_stack.push('(');
    }

    else if ((i == ")")) {
      while (operators_stack.top() != '(') {
        double operand_2 = operands_stack.top();
        operands_stack.pop();
        double operand_1 = operands_stack.top();
        operands_stack.pop();
        if (operators_stack.top() == '+') {
          operators_stack.pop();
          operands_stack.push(operand_1 + operand_2);
        } else if (operators_stack.top() == '-') {
          operators_stack.pop();
          operands_stack.push(operand_1 - operand_2);
        } else if (operators_stack.top() == '*') {
          operators_stack.pop();
          operands_stack.push(operand_2 * operand_1);
        } else if (operators_stack.top() == '/') {
          operators_stack.pop();
          operands_stack.push(operand_1 / operand_2);
        } else if (operators_stack.top() == '^') {
          operators_stack.pop();
          operands_stack.push(std::pow(operand_1, operand_2));
        }
      }
      operators_stack.pop();
    }

    else if (i == "x") {
      operands_stack.push(x);
    } else {
      operands_stack.push(std::stod(i));
    }
  }
  while (operators_stack.size() != 0) {
    double operand_2 = operands_stack.top();
    operands_stack.pop();
    double operand_1 = operands_stack.top();
    operands_stack.pop();
    if (operators_stack.top() == '+') {
      operators_stack.pop();
      operands_stack.push(operand_1 + operand_2);
    } else if (operators_stack.top() == '-') {
      operators_stack.pop();
      operands_stack.push(operand_1 - operand_2);
    } else if (operators_stack.top() == '*') {
      operators_stack.pop();
      operands_stack.push(operand_2 * operand_1);
    } else if (operators_stack.top() == '/') {
      operators_stack.pop();
      operands_stack.push(operand_1 / operand_2);
    } else if (operators_stack.top() == '^') {
      operators_stack.pop();
      operands_stack.push(std::pow(operand_1, operand_2));
    } else if (operators_stack.top() == '(') {
      // ????
    }
  }
  return operands_stack.top();
}
#endif //MATH_BUILDER_COUNTER_H
