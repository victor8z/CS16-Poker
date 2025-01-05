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

