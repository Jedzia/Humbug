#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "GUI/Components/Screen.h"

class StartScreen : public Screen {
public:

    StartScreen();
    ~StartScreen();

    const char *language(int x) const;

    virtual GroupId GetGroupID();

private:
	int i;
};

#endif // STARTSCREEN_H
