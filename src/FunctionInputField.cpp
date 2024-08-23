#include "../headers/FunctionInputField.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../headers/Counter.h"
FunctionInputField::FunctionInputField(sf::RenderWindow& window, float pos_x, float pos_y) : window_(&window), pos_x_(pos_x), pos_y_(pos_y) {
  if (!font.loadFromFile(kWayToFont)) {
    std::cerr << "Failed to load font!" << std::endl;
    return;
  }
  textField.setFont(font);
  textField.setCharacterSize(kCharacterSize);
  textField.setString(kDefaultTitle);
  textField.setColor(kTextColor);
  border.setFillColor(sf::Color::Transparent);
  border.setOutlineColor(kOutLineColor);
  border.setOutlineThickness(kOutLineThickness);
  border.setSize(sf::Vector2f(textField.getGlobalBounds().width + kCorrection, textField.getGlobalBounds().height + kCorrection));
  border.setPosition(pos_x_, pos_y_);
  textField.setPosition(pos_x_, pos_y_ );
}

void FunctionInputField::Draw() {
  window_->draw(border);
  textField.setString(textField.getString());
  window_->draw(textField);
  if (is_graph_) {
    for (int i = 0; i < points_.size() - 1; ++i) {
      sf::Vector2f point_1(points_[i].first, points_[i].second);
      sf::Vector2f point_2(points_[i + 1].first, points_[i + 1].second);
      //window_->draw(point);
      sf::Vertex line[] = {sf::Vertex(point_1),sf::Vertex(point_2)};
      window_->draw(line, 2, sf::Lines);
    }
   /* for (auto pair : points_) {
      sf::CircleShape point(Screen::rad);
      point.setFillColor(sf::Color::White);
      point.setPosition(pair.first, pair.second);
      window_->draw(point);
    }*/
  }
}

void FunctionInputField::UpdateBorder() {
  border.setSize(sf::Vector2f(textField.getGlobalBounds().width + kCorrection, textField.getGlobalBounds().height + kCorrection));
  border.setPosition(pos_x_, pos_y_);
  textField.setPosition(pos_x_ , pos_y_ );
}


void FunctionInputField::HandleInput(sf::Event& event) {
  Draw();
  if (is_active_) {
    if (event.key.code == sf::Keyboard::BackSpace) {
      if (textField.getString().getSize() != 1) {
        textField.setString(textField.getString().substring(0, textField.getString().getSize() - 1));
        std::cout << "backspace\n";
      }
      UpdateBorder();
    } else if (event.type == sf::Event::TextEntered) {
      textField.setString(textField.getString() + event.text.unicode);
      UpdateBorder();
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
      is_active_ = false;
      std::cout << "esc\n";
      return;
    }
  }
}

void FunctionInputField::CountPoints() { // функция расчитывает точки графика по строковому выражению из поля ввода
  points_.clear();
  for (double x = -400.0; x != 400.0; x += delta_) {
    double y = Computing(textField.getString(), x);
    double pos_x = (Screen::lenght / 2) + x * scale_;
    double pos_y = (Screen::width / 2) - y * scale_;
    /*if ((pos_x < Screen::lenght) && (pos_y < Screen::width)) {
      points_.emplace_back(pos_x, pos_y);
    }*/
    points_.emplace_back(pos_x, pos_y);
  }
}

void FunctionInputField::Calculating() {
  is_active_ = false;
  is_graph_ = true;
  try {
    CountPoints();
  } catch (...) {
    std::cout << "IncorrectExpression\n";
    is_graph_ = false;
  }
}

void FunctionInputField::ReturnDefaultState() {
  is_active_ = false;
  is_graph_ = false;
  textField.setString(kDefaultTitle);
  border.setSize(sf::Vector2f(textField.getGlobalBounds().width + kCorrection, textField.getGlobalBounds().height + kCorrection));
}
