#include "request.h"

Request::Request(int fromFloor, int toFloor)
    : fromFloor(fromFloor), toFloor(toFloor) {}

int Request::getFromFloor() const {
    return fromFloor;
}

int Request::getToFloor() const {
    return toFloor;
}
