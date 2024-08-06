//
// Created by leonid on 06.08.24.
//

#ifndef MATH_BUILDER_COORDINATESNETWORK_H
#define MATH_BUILDER_COORDINATESNETWORK_H
#include <SFML/Graphics.hpp>
#include "Screen.h"
void DrawNetwork(bool flag, sf::RenderWindow& window, double scale) {
  if ((!flag) || (scale < 10)) {
    return;
  }
 for (double x = Screen::width / 2; x < Screen::width; x += scale) {
    sf::RectangleShape line(sf::Vector2f(Screen::lenght, 1));
    line.setPosition(sf::Vector2f(0, static_cast<float>(x)));
    window.draw(line);
  }

  for (double x = Screen::width / 2; x >= 0; x -= scale) {
    sf::RectangleShape line(sf::Vector2f(Screen::lenght, 1));
    line.setPosition(sf::Vector2f(0, x));
    window.draw(line);
  }

  for (double x = Screen::lenght / 2; x >= 0; x -= scale) {
    sf::RectangleShape line(sf::Vector2f(Screen::width, 1));
    line.rotate(90);
    line.setPosition(sf::Vector2f(x, 0));
    window.draw(line);
  }

  for (double x = Screen::lenght / 2; x < Screen::lenght; x += scale) {
    sf::RectangleShape line(sf::Vector2f(Screen::width, 1));
    line.rotate(90);
    line.setPosition(sf::Vector2f(static_cast<float>(x), 0));
    window.draw(line);
  }


  /*sf::RectangleShape line_x(sf::Vector2f(window.getSize().x, 1));
  line_x.setPosition(sf::Vector2f(0, window.getSize().y / 2.f));

  // ось y
  sf::RectangleShape line_y(sf::Vector2f(window.getSize().y, 1));
  line_y.rotate(90);
  line_y.setPosition(sf::Vector2f(window.getSize().x / 2, 0));*/
}
#endif //MATH_BUILDER_COORDINATESNETWORK_H
