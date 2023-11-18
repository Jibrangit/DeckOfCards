#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "deck.hpp"

template <typename Player> class Dealer {
public:
  Dealer() { this->deck_ = std::make_unique<Deck>(); }
  /// @brief The functions assume the dealee object provides an interface to
  /// get_card(). This is done to deny the dealer access to the dealt cards.
  template <typename Dealee>
  void deal(std::shared_ptr<Dealee> dealee, const uint8_t num_cards);

  virtual void shuffle_for_hand(const uint8_t num_players) = 0;
  virtual void deal_round(std::vector<std::shared_ptr<Player>> players) = 0;

protected:
  std::unique_ptr<Deck> deck_;
  virtual bool cards_sufficient_for_hand(const uint8_t num_players) = 0;
};

template <typename Player> class PokerDealer : public Dealer<Player> {
public:
  PokerDealer<Player>(uint8_t initial_num_players) : Dealer<Player>() {
    this->shuffle_for_hand(initial_num_players);
  }
  void shuffle_for_hand(const uint8_t num_players);
  void deal_round(std::vector<std::shared_ptr<Player>> players) override;

private:
  const uint8_t CARDS_PER_PLAYER = 2;
  const uint8_t NUM_COMMUNITY_CARDS = 5;

  bool cards_sufficient_for_hand(const uint8_t num_players) override;
};

template <typename Player> class BlackJackDealer : public Dealer<Player> {
public:
  BlackJackDealer<Player>(uint8_t num_players)
      : Dealer<Player>(), num_players_(num_players) {
    this->shuffle_for_hand(num_players);
  }
  void shuffle_for_hand(const uint8_t num_players);
  void deal_round(std::vector<std::shared_ptr<Player>> players) override;
  void set_num_players(const uint8_t num_players) {
    this->num_players_ = num_players;
  }

private:
  uint8_t num_players_;
  const uint8_t INITIAL_NUM_CARDS_PER_PLAYER = 2;
};

#include "dealer.inl"