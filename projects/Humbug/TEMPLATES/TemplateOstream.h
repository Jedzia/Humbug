#ifndef PROJECT_TEMPLATE_H
#define PROJECT_TEMPLATE_H

//#include "SDL.h"

class Template {
public:

    Template(/*SDL_Surface* screen*/);
    ~Template();

    const char *language(int x) const;

    friend std::ostream& operator<<(std::ostream& o, const Template& r);

private:
	int i;
};

std::ostream& operator<<(std::ostream& o, const Template& r);

#endif // PROJECT_TEMPLATE_H guard
