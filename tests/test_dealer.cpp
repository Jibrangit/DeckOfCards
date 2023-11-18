#include "dealer.hpp"
#include "deck.hpp"

#include <gtest/gtest.h>

struct PokerPlayer {
  std::vector<Card> cards;

  void get_card(const Card dealt_card) { cards.push_back(dealt_card); }
  std::vector<Card> show_cards() { return cards; }
  void clear_cards() { cards.clear(); }
};

struct PokerTable {
  std::vector<Card> cards;
  void get_card(const Card dealt_card) {
    if (cards.size() == 5)
      cards.clear();
    cards.push_back(dealt_card);
  }

  std::vector<Card> show_cards() { return cards; }
};

class PokerDealerTest : public ::testing::Test {
protected:
  std::vector<std::shared_ptr<PokerPlayer>> players;
  const uint8_t NUM_PLAYERS = 3;
  const uint8_t NUM_CARDS_FULL_DECK = 56;
  const uint8_t NUM_CARDS_FLOP = 3;

  void SetUp() override {
    for (uint8_t i = 0; i < NUM_PLAYERS; i++)
      players.push_back(std::make_shared<PokerPlayer>());
  }

  void TearDown() override {}

  std::unique_ptr<PokerDealer<PokerPlayer>> get_dealer_with_empty_deck();
};

std::unique_ptr<PokerDealer<PokerPlayer>>
PokerDealerTest::get_dealer_with_empty_deck() {
  auto poker_dealer = std::make_unique<PokerDealer<PokerPlayer>>(1);
  auto poker_player = std::make_shared<PokerPlayer>();

  poker_dealer->deal(poker_player, NUM_CARDS_FULL_DECK);
  return poker_dealer;
}

TEST_F(PokerDealerTest, DealTest) {
  auto poker_dealer =
  std::make_unique<PokerDealer<PokerPlayer>>(NUM_PLAYERS); auto poker_table =
  std::make_shared<PokerTable>();
  EXPECT_NO_THROW(poker_dealer->deal(poker_table, NUM_CARDS_FLOP));
}

TEST_F(PokerDealerTest, DealTestWithEmptyDeck) {
  auto poker_table = std::make_shared<PokerTable>();
  EXPECT_THROW(
      this->get_dealer_with_empty_deck()->deal(poker_table, NUM_CARDS_FLOP),
      InsufficientDeckException);
}

TEST_F(PokerDealerTest, ShuffleForHandTest) {

  // Shuffling under normal conditions.
  auto poker_dealer = std::make_unique<PokerDealer<PokerPlayer>>(NUM_PLAYERS);
  EXPECT_NO_THROW(poker_dealer->shuffle_for_hand(NUM_PLAYERS));

  EXPECT_NO_THROW(
      this->get_dealer_with_empty_deck()->shuffle_for_hand(NUM_PLAYERS));

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
    players.at(i)->clear_cards();
}

TEST_F(PokerDealerTest, DealRoundTest) {
  auto poker_dealer =
  std::make_unique<PokerDealer<PokerPlayer>>(NUM_PLAYERS);
  EXPECT_NO_THROW(poker_dealer->deal_round(players));

  EXPECT_THROW(this->get_dealer_with_empty_deck()->deal_round(players),
               InsufficientDeckException);

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
    players.at(i)->clear_cards();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}