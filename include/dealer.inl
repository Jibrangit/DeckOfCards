template <typename Player>
template <typename Dealee>
void Dealer<Player>::deal(std::shared_ptr<Dealee> dealee,
                          const uint8_t num_cards) {
  if (!this->deck_->is_deck_sufficient(num_cards))
    throw InsufficientDeckException();

  this->deck_->deal_cards(*dealee, num_cards);
}

template <typename Player>
void PokerDealer<Player>::shuffle_for_hand(const uint8_t num_players) {
  if (!cards_sufficient_for_hand(num_players)) {
    this->deck_->reset();
  }

  this->deck_->shuffle_cards();
}

template <typename Player>
bool PokerDealer<Player>::cards_sufficient_for_hand(const uint8_t num_players) {
  return this->deck_->is_deck_sufficient(
      (num_players * CARDS_PER_PLAYER) + NUM_COMMUNITY_CARDS);
}

template <typename Player>
void PokerDealer<Player>::deal_round(
    std::vector<std::shared_ptr<Player>> players) {

  if (!this->deck_->is_deck_sufficient(players.size() * CARDS_PER_PLAYER))
    throw InsufficientDeckException();

  std::for_each(players.begin(), players.end(), [this](auto player) {
    this->deck_->deal_cards(*player, CARDS_PER_PLAYER);
  });
}

template <typename Player>
void BlackJackDealer<Player>::shuffle_for_hand(const uint8_t num_players) {
  this->deck_->reset();
  this->deck_->shuffle();
}

template <typename Player>
void BlackJackDealer<Player>::deal_round(
    std::vector<std::shared_ptr<Player>> players) {

  std::for_each(players.begin(), players.end(), [this](auto player) {
    this->deck_->deal_cards(*player, INITIAL_NUM_CARDS_PER_PLAYER);
  });
}

