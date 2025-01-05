
#include "Hand.h"

void sortCardsByRank(Card* cards, size_t cardCount) {
    for (size_t i = 1; i < cardCount; ++i) {
        Card key = cards[i];
        int j = i - 1;
        
        // Move cards of greater rank one position ahead of their current position
        while (j >= 0 && cards[j].rank > key.rank) {
            cards[j + 1] = cards[j];
            j = j - 1;
        }
        cards[j + 1] = key;
    }
}

Hand* findHighCard(const Hand& sortedHand) {
    if (sortedHand.count() == 0) {
        return nullptr;
    }
    
    Hand* highCardHand = new Hand();
    highCardHand->add(sortedHand.get(0)); // Add the highest-ranked card
    
    return highCardHand;
}

Hand* findPair(const Hand& sortedHand) {
    Hand* pairHand = new Hand();
    size_t pairsFound = 0;

    if (sortedHand.count() < 2) {
        delete pairHand; 
        return nullptr;
    }
    for (size_t i = 0; i < sortedHand.count() - 1 && pairsFound == 0; i++) {
        if (sortedHand.get(i).rank == sortedHand.get(i + 1).rank) {
            pairHand->add(sortedHand.get(i));
            pairHand->add(sortedHand.get(i + 1));
            pairsFound++;
            i++;
        }
    }
    if (pairsFound == 1) {
        return pairHand;
    } else {
        delete pairHand;
        return nullptr;
    }
}

Hand* findTwoPair(const Hand& sortedHand) {
    Hand* twoPairHand = new Hand();
    size_t pairsFound = 0;
    for (size_t i = 0; i < sortedHand.count() - 1 && pairsFound < 2; i++) {
        if (sortedHand.get(i).rank == sortedHand.get(i + 1).rank) {
            twoPairHand->add(sortedHand.get(i));
            twoPairHand->add(sortedHand.get(i + 1));
            pairsFound++;
            i++;
        }
    }
    if (pairsFound == 2) {
        return twoPairHand;
    } else {
        delete twoPairHand;
        return nullptr;
    }
}

Hand* findThreeOfAKind(const Hand& sortedHand) {
    if (sortedHand.count() < 3) {
        return nullptr; 
    }

    for (size_t i = 0; i <= sortedHand.count() - 3; ++i) {
        if (sortedHand.get(i).rank == sortedHand.get(i + 1).rank &&
            sortedHand.get(i).rank == sortedHand.get(i + 2).rank) {
            Hand* threeOfAKindHand = new Hand();
            for (size_t j = 0; j < 3; ++j) {
                threeOfAKindHand->add(sortedHand.get(i + j));
            }

            return threeOfAKindHand;
        }
    }

    return nullptr;
}

Hand* findStraight(const Hand& sortedHand) {
    if (sortedHand.count() < 5) {
        return nullptr;
    }

    Hand* straightHand = nullptr;

    // Check for regular straight
    for (size_t i = 0; i <= sortedHand.count() - 5; ++i) {
        Hand* currentStraight = new Hand();
        currentStraight->add(sortedHand.get(i));

        int lastRank = sortedHand.get(i).rank;

        for (size_t j = i + 1; j < sortedHand.count() && currentStraight->count() < 5; ++j) {
            int nextRank = sortedHand.get(j).rank;
            if (nextRank == lastRank - 1) {
                currentStraight->add(sortedHand.get(j));
                lastRank = nextRank;
            } else if (nextRank < lastRank - 1) {
                break;
            }
        }

        if (currentStraight->count() == 5) {
            delete straightHand; // Delete previous best straight if it exists
            straightHand = currentStraight;
            break;
        } else {
            delete currentStraight;
        }
    }

    // Check for Ace low straight (wheel straight)
    if (!straightHand && sortedHand.get(0).rank == Rank::ACE) {
        straightHand = new Hand();
        straightHand->add(sortedHand.get(0)); // Add Ace
        int neededRanks[] = {5, 4, 3, 2}; // Wheel straight ranks

        for (int rank : neededRanks) {
            bool rankFound = false;
            for (size_t k = 1; k < sortedHand.count(); ++k) {
                if (sortedHand.get(k).rank == rank) {
                    straightHand->add(sortedHand.get(k)); // Add the necessary ranks to the straight
                    rankFound = true;
                    break;
                }
            }
            if (!rankFound) {
                delete straightHand;
                straightHand = nullptr;
                break;
            }
        }
    }

    return straightHand;
}

Hand* findFlush(const Hand& sortedHand) {
    if (sortedHand.count() < 5) return nullptr;

    Hand* bestFlush = nullptr;
    int suitCount[4] = {0};
    Hand suitHands[4]; // Assuming default constructor is available and sets capacity

    for (size_t i = 0; i < sortedHand.count(); ++i) {
        Card card = sortedHand.get(i);
        suitHands[card.suit].add(card);
        suitCount[card.suit]++;
    }

    for (int suit = 0; suit < 4; ++suit) {
        int numCardsInSuit = static_cast<int>(suitCount[suit]);
        if (numCardsInSuit >= 5) {
            suitHands[suit].sort(); // Sort the suit hand to ensure the highest cards are first

            for (int start = 0; start <= numCardsInSuit - 5; ++start) {
                Hand* flushHand = new Hand();

                for (int i = start; i < start + 5; ++i) {
                    flushHand->add(suitHands[suit].get(i));
                }

                bool isBetter = false;
                if (!bestFlush) {
                    isBetter = true;
                } else {
                    for (size_t i = 0; i < 5; ++i) {
                        if (flushHand->get(i).rank > bestFlush->get(i).rank) {
                            isBetter = true;
                            break;
                        } else if (flushHand->get(i).rank < bestFlush->get(i).rank) {
                            break;
                        }
                    }
                }

                if (isBetter) {
                    delete bestFlush; // Delete the old bestFlush if necessary
                    bestFlush = flushHand; // Update bestFlush
                } else {
                    delete flushHand; // Otherwise, discard the current flushHand
                }
            }
        }
    }

    return bestFlush;
}

Hand* findFullHouse(const Hand& sortedHand) {
    Hand* threeOfAKindHand = findThreeOfAKind(sortedHand);
    if (threeOfAKindHand == nullptr) {
        return nullptr;
    }

    Hand tempHand;
    for (size_t i = 0; i < sortedHand.count(); ++i) {
        bool isInThreeKind = false;
        for (size_t j = 0; j < threeOfAKindHand->count(); ++j) {
            if (sortedHand.get(i).rank == threeOfAKindHand->get(j).rank) {
                isInThreeKind = true;
                break;
            }
        }
        if (!isInThreeKind) {
            tempHand.add(sortedHand.get(i));
        }
    }

    Hand* pairHand = findPair(tempHand);
    if (pairHand == nullptr) {
        delete threeOfAKindHand;
        return nullptr;
    }

    Hand* fullHouseHand = new Hand();
    for (size_t i = 0; i < threeOfAKindHand->count(); ++i) {
        fullHouseHand->add(threeOfAKindHand->get(i));
    }
    for (size_t i = 0; i < pairHand->count(); ++i) {
        fullHouseHand->add(pairHand->get(i));
    }

    delete threeOfAKindHand;
    delete pairHand;

    return fullHouseHand;
}

Hand* findFourOfAKind(const Hand& sortedHand) {
    if (sortedHand.count() < 4) {
        return nullptr;
    }

    for (size_t i = 0; i <= sortedHand.count() - 4; ++i) {
        if (sortedHand.get(i).rank == sortedHand.get(i + 1).rank &&
            sortedHand.get(i).rank == sortedHand.get(i + 2).rank &&
            sortedHand.get(i).rank == sortedHand.get(i + 3).rank) {
            Hand* fourOfAKindHand = new Hand();
            for (size_t j = 0; j < 4; ++j) {
                fourOfAKindHand->add(sortedHand.get(i + j));
            }

            return fourOfAKindHand;
        }
    }

    return nullptr; 
}

Hand* findStraightFlush(const Hand& sortedHand) {
    if (sortedHand.count() < 5) {
        return nullptr;
    }

    Hand* bestStraightFlush = nullptr;

    // Iterate through each suit
    for (int suit = 0; suit < 4; ++suit) {
        Hand suitHand; // Temporary hand for the current suit

        // Collect cards of the current suit
        for (size_t i = 0; i < sortedHand.count(); ++i) {
            if (sortedHand.get(i).suit == suit) {
                suitHand.add(sortedHand.get(i));
            }
        }

        // Check if there are enough cards of the current suit for a straight flush
        if (suitHand.count() < 5) {
            continue; // Not enough cards of this suit, move to the next suit
        }

        // Check for straight flushes
        for (size_t i = 0; i <= suitHand.count() - 5; ++i) {
            Hand* currentStraightFlush = new Hand();
            currentStraightFlush->add(suitHand.get(i)); // Add the highest card of the straight flush

            int lastRank = suitHand.get(i).rank;

            // Check for a straight flush starting from the current card
            for (size_t j = i + 1; j < suitHand.count() && currentStraightFlush->count() < 5; ++j) {
                int nextRank = suitHand.get(j).rank;
                if (nextRank == lastRank - 1) {
                    currentStraightFlush->add(suitHand.get(j));
                    lastRank = nextRank;
                } else if (nextRank < lastRank - 1) {
                    break; // Not part of a straight flush
                }
            }


            if (currentStraightFlush->count() == 5) {
                if (!bestStraightFlush || currentStraightFlush->get(0).rank > bestStraightFlush->get(0).rank) {
                    delete bestStraightFlush;
                    bestStraightFlush = currentStraightFlush;
                } else {
                    delete currentStraightFlush; 
                }
            } else {
                delete currentStraightFlush;
            }
        }
    }

    // If no regular straight flush was found, check for Ace-low straight flush
    if (!bestStraightFlush) {
        for (int suit = 0; suit < 4; ++suit) {
            Hand suitHand;

            for (size_t i = 0; i < sortedHand.count(); ++i) {
                if (sortedHand.get(i).suit == suit) {
                    suitHand.add(sortedHand.get(i));
                }
            }

            if (suitHand.count() < 5) {
                continue;
            }

            // Check for Ace-low straight flush
            bool aceLowFound = false;
            for (size_t i = 0; i < suitHand.count(); ++i) {
                if (suitHand.get(i).rank == Rank::ACE) {
                    aceLowFound = true;
                    break;
                }
            }

            if (aceLowFound) {
                Hand* aceLowStraightFlushHand = new Hand();
                for (size_t i = 0; i < suitHand.count(); ++i) {
                    if (suitHand.get(i).rank == Rank::ACE) {
                        aceLowStraightFlushHand->add(suitHand.get(i)); // Add Ace
                        break;
                    }
                }
                for (int rank = 5; rank >= 2; --rank) {
                    bool rankFound = false;
                    for (size_t i = 0; i < suitHand.count(); ++i) {
                        if (suitHand.get(i).rank == rank) {
                            aceLowStraightFlushHand->add(suitHand.get(i)); // Add the necessary ranks to the straight flush
                            rankFound = true;
                            break;
                        }
                    }
                    if (!rankFound) {
                        delete aceLowStraightFlushHand;
                        aceLowStraightFlushHand = nullptr;
                        break; // Not a valid Ace-low straight flush
                    }
                }
                return aceLowStraightFlushHand;
            }
        }
    }

    return bestStraightFlush;
}

Hand* best_hand(const Hand& hand) {
    if (hand.count() == 0) {
        return new Hand();
    }

    Hand sortedHand = hand;
    sortedHand.sort(); // Sort the hand in descending order of rank

    Hand* best = findStraightFlush(sortedHand);
    if (best) return best;

    best = findFourOfAKind(sortedHand);
    if (best) return best;

    best = findFullHouse(sortedHand);
    if (best) return best;

    best = findFlush(sortedHand);
    if (best) return best;

    best = findStraight(sortedHand);
    if (best) return best;

    best = findThreeOfAKind(sortedHand);
    if (best) return best;

    best = findTwoPair(sortedHand);
    if (best) return best;

    best = findPair(sortedHand);
    if (best) return best;

    return findHighCard(sortedHand);
}