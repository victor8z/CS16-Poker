#ifndef HAND_H
#define HAND_H

#include "Card.h"

class Hand {
public:
    Hand();
    Hand(const Hand& other);
    ~Hand();

    void add(Card card);
    void clear();
    size_t count() const;
    Card get(size_t index) const;
    void print() const;
    void sort();

    static int getSuitPriority(Suit suit);
    static bool compareCards(const Card& a, const Card& b);

private:
    Card* cards;
    size_t cardCount;
    size_t capacity;

    void resize();
};

// Factory function to create a new hand
Hand* make_hand();

#endif // HAND_H
