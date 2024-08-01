#include "main.h"

int main() {
  //std::cout << Computing("y = x ^ 2 + 5 * x + 2", 2);
  sf::RenderWindow window(sf::VideoMode(Screen::lenght, Screen::width), "Text Input Field");

  // ось х
  sf::RectangleShape line_x(sf::Vector2f(window.getSize().x, 1));
  line_x.setPosition(sf::Vector2f(0, window.getSize().y / 2.f));

  // ось y
  sf::RectangleShape line_y(sf::Vector2f(window.getSize().y, 1));
  line_y.rotate(90);
  line_y.setPosition(sf::Vector2f(window.getSize().x / 2, 0));

  // поля для ввода
  FunctionInputField text_field_1(window, 5, 5);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      // проверка не ткнули ли мышью на поле
      if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (text_field_1.border.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                           static_cast<float>(mousePos.y))) {
          // первая поле
          text_field_1.is_active_ = true;
        }
      }

      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        } else if (event.key.code == sf::Keyboard::Enter) {
          text_field_1.is_active_ = false;
          text_field_1.is_graph_ = true;
          text_field_1.CountPoints();
        }
      }
      window.clear();

      text_field_1.HandleInput(event);
      window.draw(line_x);
      window.draw(line_y);
      window.display();
    }
  }
  return 0;
}