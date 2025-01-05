# Advanced Poker Hand Evaluator

The **Advanced Poker Hand Evaluator** is a C++ program designed to identify and rank poker hands from a given set of cards. It supports all standard poker hands, such as pairs, straights, flushes, and full houses, and is built using object-oriented principles for scalability and performance.

## Features

- **Hand Evaluation:** Accurately detects the best poker hand, including high card, pair, two pair, straight, flush, and more.
- **Object-Oriented Design:** Modular classes for `Card` and `Hand`, enabling robust card management and evaluation.
- **Advanced Sorting:** Implements custom sorting algorithms to organize cards by rank and suit efficiently.
- **Extensibility:** The design allows for easy integration into larger game systems or further feature additions.
- **Robust Error Handling:** Manages edge cases like invalid card input and insufficient cards gracefully.

## Tech Stack

- **Programming Language:** C++
- **Dependencies:** Standard C++ library

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/AdvancedPokerHandEvaluator.git

2. Navigate to the project directory:
   ```bash
   cd AdvancedPokerHandEvaluator

3. Compile the program:
   ```bash
   g++ -o poker best_hand.cpp Hand.cpp -std=c++17
   
4. Run the program:
   ```bash
   ./poker

## Usage:
The program evaluates poker hands based on a given input set of cards:
1. Create a Hand object and add cards using the add() method.
2. Call the best_hand() function to determine the highest-ranked hand.
3. Use the print() method to display the results.

## Example Code:
#include "Hand.h"
#include "best_hand.cpp"

int main() {
    Hand myHand;
    myHand.add(Card(Rank::ACE, Suit::SPADES));
    myHand.add(Card(Rank::KING, Suit::HEARTS));
    myHand.add(Card(Rank::QUEEN, Suit::DIAMONDS));
    myHand.add(Card(Rank::JACK, Suit::CLUBS));
    myHand.add(Card(Rank::TEN, Suit::SPADES));

    Hand* best = best_hand(myHand);
    best->print(); // Outputs the best poker hand
    delete best;

    return 0;
}

## Project Structure:
AdvancedPokerHandEvaluator/
- Card.h           # Defines the Card class and enums for rank and suit
- Hand.h           # Defines the Hand class for managing a set of cards
- Hand.cpp         # Implementation of the Hand class
- best_hand.cpp    # Functions to evaluate the best poker hand
  
## Key Functions:
- **add():** Adds a card to the hand in a sorted position.
- **best_hand():** Determines the highest poker hand from a given hand.
- **sort():** Sorts cards by rank and suit using custom comparison logic.
- **findStraightFlush():** Identifies a straight flush, the highest-ranking hand.
- **get():** Retrieves a specific card by index, with bounds checking.

## Examples:
- **Adding Cards to a Hand**
Hand myHand;
myHand.add(Card(Rank::QUEEN, Suit::DIAMONDS));
myHand.add(Card(Rank::TEN, Suit::SPADES));
myHand.print();

-**Evaluating the Best Hand:**
Hand* best = best_hand(myHand);
best->print(); // Prints the best possible hand
delete best;

