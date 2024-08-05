#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Screen.h"
#include <SFML/Graphics.hpp>

class FunctionInputField {
public:
  sf::RenderWindow *  window_;
  sf::Font font;
  sf::Text textField;
  sf::RectangleShape border;
  float pos_x_;
  float pos_y_;
  bool is_active_ = false;
  double scale_ = 1;
  double delta_ = 0.5;

  const float kBoardShift = 10;
  const sf::Color kTextColor = sf::Color::White;
  const int kCharacterSize = 32;
  const std::string kDefaultTitle = "|Enter";
  const std::string kWayToFont = "../font/ofont.ru_Times New Roman.ttf";
  const float kCorrection = 9;
  const sf::Color kOutLineColor = sf::Color::White;
  const float kOutLineThickness = 2;

  bool is_graph_ = false;
  std::vector<std::pair<double, double>> points_;

  FunctionInputField(sf::RenderWindow& window, float pos_x, float pos_y);
  void Draw();
  void UpdateBorder();
  void HandleInput(sf::Event& event);
  void CountPoints();
};


