#include "deck.hpp"
#include <gtest/gtest.h>

struct PokerPlayer {
  std::vector<Card> cards;

  void get_card(const Card dealt_card) { cards.push_back(dealt_card); }
  std::vector<Card> show_cards() { return cards; }
  void clear_cards() { cards.clear(); }
};

class DeckTest : public ::testing::Test {
protected:
  Deck deck;
  const uint8_t TOTAL_NUM_CARDS = 56;
  PokerPlayer dummy_player1, dummy_player2;

  void SetUp() override { deck = Deck(); }

  void TearDown() override {
  }
};

TEST_F(DeckTest, IsDeckSufficientTest) {

  // Deck has all cards
  EXPECT_TRUE(deck.is_deck_sufficient(TOTAL_NUM_CARDS));
  EXPECT_TRUE(deck.is_deck_sufficient(TOTAL_NUM_CARDS - 5));
  EXPECT_FALSE(deck.is_deck_sufficient(TOTAL_NUM_CARDS + 5));

  // Deck has partial cards
  uint8_t NUM_CARDS_REMOVED = 20;
  deck.discard_random_cards_from_deck(NUM_CARDS_REMOVED);
  EXPECT_TRUE(deck.is_deck_sufficient(TOTAL_NUM_CARDS - NUM_CARDS_REMOVED));
  EXPECT_TRUE(deck.is_deck_sufficient(TOTAL_NUM_CARDS - NUM_CARDS_REMOVED - 5));
  EXPECT_FALSE(
      deck.is_deck_sufficient(TOTAL_NUM_CARDS - NUM_CARDS_REMOVED + 5));

  // Deck is empty
  deck.reset();
  deck.discard_random_cards_from_deck(TOTAL_NUM_CARDS);
  EXPECT_TRUE(deck.is_deck_sufficient(0));
  EXPECT_FALSE(deck.is_deck_sufficient(1));

  deck.reset();
}

TEST_F(DeckTest, DealCardsTest) {
    // Deck is initially ordered, so first 3 cards are of last suite and last 3 card indices. 
    deck.deal_cards(dummy_player1, 3);
    auto dealt_cards = dummy_player1.show_cards();

    EXPECT_TRUE(dealt_cards[0] == Card(Suite::CLUB, CardIndex::KING)); 
    EXPECT_TRUE(dealt_cards[1] == Card(Suite::CLUB, CardIndex::QUEEN)); 
    EXPECT_TRUE(dealt_cards[2] == Card(Suite::CLUB, CardIndex::JACK)); 

    deck.reset();
    deck.discard_random_cards_from_deck(TOTAL_NUM_CARDS);
    EXPECT_THROW(deck.deal_cards(dummy_player1, 1), InsufficientDeckException);
}

TEST_F(DeckTest, ShuffleCardsTest) {
  // Deal all cards to Player
  deck.deal_cards(dummy_player1, TOTAL_NUM_CARDS);

  // Deal all shuffled cards to player
  deck.reset();
  deck.shuffle_cards();
  deck.deal_cards(dummy_player2, TOTAL_NUM_CARDS);

  // Check if deck changes after shuffling. The chance for the deck to turn out
  // the same is close to impossible.
  auto player1_cards = dummy_player1.show_cards();
  auto player2_cards = dummy_player2.show_cards();

  EXPECT_FALSE(std::equal(player1_cards.begin(), player1_cards.end(), player2_cards.begin()));

  deck.reset();
  dummy_player1.clear_cards();
  dummy_player2.clear_cards();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}