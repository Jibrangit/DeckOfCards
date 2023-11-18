#pragma once 

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>

enum Suite { HEART, DIAMOND, SPADE, CLUB, NUM_SUITES };

enum CardIndex {
  ACE,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  NUM_CARD_INDICES
};

struct Card {
  Suite card_suite;
  CardIndex card_index;

  Card(int suite, int card_index) {
    this->card_suite = static_cast<Suite>(suite);
    this->card_index = static_cast<CardIndex>(card_index);

  }

  Card() : Card(0, 0) {}

  void operator=(const Card &c) {
    this->card_suite = c.card_suite;
    this->card_index = c.card_index;
  }
};

class Deck {
public:
  Deck();
  void shuffle_cards();
  bool is_deck_sufficient(uint8_t required_num_cards) const;
  void reset();
  void discard_random_cards_from_deck(const uint8_t num_cards);

  template <typename Dealee>
  void deal_cards(Dealee &dealee, const uint8_t num_cards);
  
private:
  static const uint8_t TOTAL_NUM_CARDS = 56;
  std::vector<Card> cards_;
  std::array<Card, TOTAL_NUM_CARDS> complete_deck_of_cards_;
};

bool operator==(const Card &lhs, const Card &rhs) {
  return (lhs.card_suite == rhs.card_suite) &&
         (lhs.card_index == rhs.card_index);
}

class InsufficientDeckException : public std::out_of_range {
public:
  explicit InsufficientDeckException()
      : std::out_of_range("Insufficient cards in deck!") {}
};

#include "deck.inl"