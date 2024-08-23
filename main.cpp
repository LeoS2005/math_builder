#include "main.h"

int main() {
  bool network_flag = false;
  sf::RenderWindow window(sf::VideoMode(Screen::lenght, Screen::width), "Text Input Field", sf::Style::Titlebar | sf::Style::Close);

  // ось х
  sf::RectangleShape line_x(sf::Vector2f(window.getSize().x - 1, 3));
  line_x.setPosition(sf::Vector2f(0, window.getSize().y / 2.f));

  // ось y
  sf::RectangleShape line_y(sf::Vector2f(window.getSize().y - 1, 3));
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
          //window.close();
          text_field_1.ReturnDefaultState(); // default state
        } else if (event.key.code == sf::Keyboard::Enter) {
          text_field_1.Calculating();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
          std::cout << "ctrl\n";
          network_flag = !network_flag;
        }
      }

      if ((event.type == sf::Event::MouseWheelScrolled) && text_field_1.is_graph_) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
          if (event.mouseWheelScroll.delta == 1) {
            if (text_field_1.scale_ <= 256) {
              text_field_1.scale_ *= 2;
              if (text_field_1.delta_ > 0.125) {
                text_field_1.delta_ /= 2;
              }
              text_field_1.CountPoints();
            }
          }
          if (event.mouseWheelScroll.delta == -1) {
            if (text_field_1.scale_ > 0.0625) {
              text_field_1.scale_ /= 2;
              text_field_1.delta_ = std::max(0.125, 1 / text_field_1.scale_);
              text_field_1.delta_ *= 2;
              text_field_1.CountPoints();
            }
          }
        }
        std::cout << text_field_1.scale_ << '\n';
      }

      window.clear();

      WriteCursorCoordinates(window, text_field_1.scale_);

      text_field_1.HandleInput(event);
      window.draw(line_x);
      window.draw(line_y);
      DrawNetwork(network_flag, window, text_field_1.scale_);
      window.display();
    }
  }
  return 0;
}