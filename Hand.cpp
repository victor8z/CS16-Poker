#include "Hand.h"
#include <iostream>
#include <stdexcept>

Hand::Hand() : cards(new Card[4]), cardCount(0), capacity(4) {}

Hand::Hand(const Hand& other) : cards(new Card[other.capacity]), cardCount(other.cardCount), capacity(other.capacity) {
    std::copy(other.cards, other.cards + cardCount, cards);
}

Hand::~Hand() {
    delete[] cards;
}

void Hand::add(Card card) {
    if (cardCount >= capacity) {
        resize();
    }
    size_t insertPos = 0;
    for (insertPos = 0; insertPos < cardCount; ++insertPos) {
        if (compareCards(card, cards[insertPos])) {
            break;
        }
    }
    for (size_t i = cardCount; i > insertPos; --i) {
        cards[i] = cards[i - 1];
    }
    cards[insertPos] = card;
    ++cardCount;
}

void Hand::clear() {
    cardCount = 0;
}

size_t Hand::count() const {
    return cardCount;
}

Card Hand::get(size_t index) const {
    if (index >= cardCount) {
        throw std::out_of_range("Index is out of bounds");
    }
    return cards[index];
}

void Hand::resize() {
    size_t newCapacity = capacity * 2;
    Card* newCards = new Card[newCapacity];
    std::copy(cards, cards + cardCount, newCards);
    delete[] cards;
    cards = newCards;
    capacity = newCapacity;
}

void Hand::print() const {
    if (cardCount > 0) {
        for (size_t i = 0; i < cardCount - 1; ++i) { 
            cards[i].print();
            std::cout << " ";
        }
        cards[cardCount - 1].print();
    }
}


bool Hand::compareCards(const Card& a, const Card& b) {
    if (a.rank == b.rank) {
        return getSuitPriority(a.suit) > getSuitPriority(b.suit);
    }
    return a.rank > b.rank;
}

int Hand::getSuitPriority(Suit suit) {
    switch(suit) {
        case SPADES: return 4;
        case HEARTS: return 3;
        case DIAMONDS: return 2;
        case CLUBS: return 1;
        default: return 0;
    }
}

void Hand::sort() {
    // Sorting in descending order of rank, and then by suit order Spades > Hearts > Diamonds > Clubs
    for (size_t i = 0; i < cardCount - 1; i++) {
        size_t highestIndex = i;
        for (size_t j = i + 1; j < cardCount; j++) {
            if (cards[j].rank > cards[highestIndex].rank ||
               (cards[j].rank == cards[highestIndex].rank && getSuitPriority(cards[j].suit) > getSuitPriority(cards[highestIndex].suit))) {
                highestIndex = j;
            }
        }
        if (i != highestIndex) {
            Card temp = cards[i];
            cards[i] = cards[highestIndex];
            cards[highestIndex] = temp;
        }
    }
}

Hand* make_hand() {
    return new Hand();
}