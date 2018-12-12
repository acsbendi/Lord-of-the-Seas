#ifndef DIRECTION_H
#define DIRECTION_H

/*!
 * The possible directions in which 2 GridSquares or 2 GridPoints can be relative to each other.
 */
enum Direction { left, right, up, down };
/*!
 * The possible directions in which a GridSquare and a GridPoint can be relative to each other.
 */
enum IntermediateDirection {northwest, northeast, southeast, southwest};

#endif //DIRECTION_H
