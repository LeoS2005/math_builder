#ifndef MATH_BUILDER_CURSORCOORDINATES_H
#define MATH_BUILDER_CURSORCOORDINATES_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Screen.h"
#include "VectorShift.h"
// функция отрисовывающая координаты рядом с графиком
void WriteCursorCoordinates(sf::RenderWindow& window, double delta) {
  sf::Font font;
  if (!font.loadFromFile("../font/ofont.ru_Times New Roman.ttf")) {
    std::cout << "error"; // Ошибка загрузки шрифта
  }
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(20);
  text.setFillColor(sf::Color::White);

  // Получаем текущие координаты мыши
  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

  // Преобразуем координаты в строку
  std::ostringstream oss;
  oss << "(" << (- Screen::lenght / 2 + mousePosition.x) / delta - VectorShift::x << ", " << (Screen::width / 2 - mousePosition.y) / delta - VectorShift::y << ")";
  text.setString(oss.str());

  // Устанавливаем позицию текста около курсора
  text.setPosition(static_cast<float>(mousePosition.x) + 10, static_cast<float>(mousePosition.y) + 10);

  window.draw(text);
}
#endif //MATH_BUILDER_CURSORCOORDINATES_H
