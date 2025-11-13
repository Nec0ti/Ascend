#ifndef REQUEST_H
#define REQUEST_H

class Request {
public:
    Request(int fromFloor, int toFloor);

    int getFromFloor() const;
    int getToFloor() const;

private:
    int fromFloor;
    int toFloor;
};

#endif
