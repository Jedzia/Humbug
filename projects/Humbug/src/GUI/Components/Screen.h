#ifndef SCREEN_H
#define SCREEN_H
#include "../Visual/Hookable.h"

class Screen : public Hookable {
public:

    Screen();
    ~Screen();

    GroupId GetGroupID();

private:
	int i;
};

#endif // SCREEN_H
