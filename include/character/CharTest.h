/**
 * Character Test
 */

#ifndef __CHAR_TEST_H__
#define __CHAR_TEST_H__

// Punchbowl headers
#include "Character.h"

class CharTest : public Character {
    private:
        int out();
    public:
        CharTest();
        ~CharTest();

        int eventHandler(const df::Event *p_e);
};

#endif // __CHAR_TEST_H__
