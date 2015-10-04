/**
 * Character Test
 */

#ifndef __CHAR_TEST_H__
#define __CHAR_TEST_H__

// Punchbowl headers
#include "Character.h"

const std::string char_bull_type = "char_bull";

class CharTest : public Character {
    private:
        int out();
    public:
        CharTest();

        int eventHandler(const df::Event *p_e);
};

#endif // __CHAR_TEST_H__
