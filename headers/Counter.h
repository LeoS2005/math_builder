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
4: ln, sin, cos, tg, ctg
*/
// функция по операции возвращает приоритет
int Priority(std::string& operation) {
  if ((operation == "sin") || (operation == "cos") || (operation == "tg") || (operation == "ctg") || (operation == "ln")) {
    return 4;
  }
  if (operation == "^") {
    return 3;
  }
  if ((operation == "*") || (operation == "/")) {
    return 2;
  }
  if ((operation == "-") || (operation == "+")) {
    return 1;
  }
  throw IncorrectOperator{};
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
  std::stack<std::string> operators_stack;
  auto query = Split(function);
  query.erase(query.begin());
  query.erase(query.begin());
  std::vector<std::string> operators_set{"+", "-", "*", "/", "^", "sin", "cos", "tg", "ctg", "ln"};
  for (auto& i : query) {
    //std::find(operators_set.begin(), operators_set.end(), i[0]);
    if ((std::find(operators_set.begin(), operators_set.end(), i) != operators_set.end())) {

      if ((operators_stack.size() == 0) || (operators_stack.top() == "(") || (Priority(operators_stack.top()) < Priority(i))) {
          operators_stack.push(i);
      } else {

        while (!(operators_stack.empty()) && (Priority(operators_stack.top()) >= Priority(i))) {

          double operand_2 = operands_stack.top();
          operands_stack.pop();

          if (operators_stack.top() == "+") {
            double operand_1 = operands_stack.top();
            operands_stack.pop();
            operators_stack.pop();
            operands_stack.push(operand_1 + operand_2);
          } else if (operators_stack.top() == "-") {
            double operand_1 = operands_stack.top();
            operands_stack.pop();
            operators_stack.pop();
            operands_stack.push(operand_1 - operand_2);
          } else if (operators_stack.top() == "*") {
            double operand_1 = operands_stack.top();
            operands_stack.pop();
            operators_stack.pop();
            operands_stack.push(operand_2 * operand_1);
          } else if (operators_stack.top() == "/") {
            double operand_1 = operands_stack.top();
            operands_stack.pop();
            operators_stack.pop();
            operands_stack.push(operand_1 / operand_2);
          } else if (operators_stack.top() == "^") {
            double operand_1 = operands_stack.top();
            operands_stack.pop();
            operators_stack.pop();
            operands_stack.push(std::pow(operand_1, operand_2));
          } else if (operators_stack.top() == "(") {
            operators_stack.push("(");
          } else if (operators_stack.top() == "sin") {
            operators_stack.pop();
            operands_stack.push(std::sin(operand_2));
          } else if (operators_stack.top() == "cos") {
            operators_stack.pop();
            operands_stack.push(std::cos(operand_2));
          } else if (operators_stack.top() == "tg") {
            operators_stack.pop();
            operands_stack.push(std::tan(operand_2));
          } else if (operators_stack.top() == "ctg") {
            operators_stack.pop();
            operands_stack.push(1 / std::tan(operand_2));
          } else if (operators_stack.top() == "ln") {
            operators_stack.pop();
            operands_stack.push(std::log(operand_2));
          }
        }
        operators_stack.push(i);
      }
    }

    else if (i == "(") {
      operators_stack.push("(");
    }

    else if ((i == ")")) {
      while (operators_stack.top() != "(") {
        double operand_2 = operands_stack.top();
        operands_stack.pop();

        if (operators_stack.top() == "+") {
          double operand_1 = operands_stack.top();
          operands_stack.pop();
          operators_stack.pop();
          operands_stack.push(operand_1 + operand_2);
        } else if (operators_stack.top() == "-") {
          double operand_1 = operands_stack.top();
          operands_stack.pop();
          operators_stack.pop();
          operands_stack.push(operand_1 - operand_2);
        } else if (operators_stack.top() == "*") {
          double operand_1 = operands_stack.top();
          operands_stack.pop();
          operators_stack.pop();
          operands_stack.push(operand_2 * operand_1);
        } else if (operators_stack.top() == "/") {
          double operand_1 = operands_stack.top();
          operands_stack.pop();
          operators_stack.pop();
          operands_stack.push(operand_1 / operand_2);
        } else if (operators_stack.top() == "^") {
          double operand_1 = operands_stack.top();
          operands_stack.pop();
          operators_stack.pop();
          operands_stack.push(std::pow(operand_1, operand_2));
        } else if (operators_stack.top() == "sin") {
          operators_stack.pop();
          operands_stack.push(std::sin(operand_2));
        } else if (operators_stack.top() == "cos") {
          operators_stack.pop();
          operands_stack.push(std::cos(operand_2));
        } else if (operators_stack.top() == "tg") {
          operators_stack.pop();
          operands_stack.push(std::tan(operand_2));
        } else if (operators_stack.top() == "ctg") {
          operators_stack.pop();
          operands_stack.push(1 / std::tan(operand_2));
        } else if (operators_stack.top() == "ln") {
          operators_stack.pop();
          operands_stack.push(std::log(operand_2));
        }
      }
      //operators_stack.push(i);
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

    if (operators_stack.top() == "+") {
      double operand_1 = operands_stack.top();
      operands_stack.pop();
      operators_stack.pop();
      operands_stack.push(operand_1 + operand_2);
    } else if (operators_stack.top() == "-") {
      double operand_1 = operands_stack.top();
      operands_stack.pop();
      operators_stack.pop();
      operands_stack.push(operand_1 - operand_2);
    } else if (operators_stack.top() == "*") {
      double operand_1 = operands_stack.top();
      operands_stack.pop();
      operators_stack.pop();
      operands_stack.push(operand_2 * operand_1);
    } else if (operators_stack.top() == "/") {
      double operand_1 = operands_stack.top();
      operands_stack.pop();
      operators_stack.pop();
      operands_stack.push(operand_1 / operand_2);
    } else if (operators_stack.top() == "^") {
      double operand_1 = operands_stack.top();
      operands_stack.pop();
      operators_stack.pop();
      operands_stack.push(std::pow(operand_1, operand_2));
    } else if (operators_stack.top() == "sin") {
      operators_stack.pop();
      operands_stack.push(std::sin(operand_2));
    } else if (operators_stack.top() == "cos") {
      operators_stack.pop();
      operands_stack.push(std::cos(operand_2));
    } else if (operators_stack.top() == "tg") {
      operators_stack.pop();
      operands_stack.push(std::tan(operand_2));
    } else if (operators_stack.top() == "ctg") {
      operators_stack.pop();
      operands_stack.push(1 / std::tan(operand_2));
    } else if (operators_stack.top() == "ln") {
      operators_stack.pop();
      operands_stack.push(std::log(operand_2));
    }
  }
  return operands_stack.top();
}
#endif //MATH_BUILDER_COUNTER_H
