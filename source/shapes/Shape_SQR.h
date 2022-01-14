// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_SQR.h, 2021-12-18 - 2022-01-13
// Contains the declaration of the Shape_SQR-class.
//

#ifndef TETRIS_SHAPE_SQR_H
#define TETRIS_SHAPE_SQR_H


#include "Shape.h"

/**
 * Class that inherits from the Shape-class to create a tetris Square-shape.
 */
class Shape_SQR: public Shape {
public:
    Shape_SQR();

    void rotate(bool clockwise) override { }
};


#endif //TETRIS_SHAPE_SQR_H
