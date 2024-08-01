// содержатся парамаметры экрана
#ifndef MATH_BUILDER_SCREEN_H
#define MATH_BUILDER_SCREEN_H
struct Screen {
  constexpr static double lenght = 800; // длина экрана
  constexpr static double width = 600; // ширина экрана
  constexpr static double delta = 0.5; // расстояние между соседними точками
  constexpr static double rad = 1.f; // расстояние между точками
};
#endif //MATH_BUILDER_SCREEN_H
