Deck::Deck() {

  for (uint8_t suite = 0; suite < Suite::NUM_SUITES; suite++) {
    for (uint8_t index = 0; index < CardIndex::NUM_CARD_INDICES; index++) {
      this->complete_deck_of_cards_.at(suite * CardIndex::NUM_CARD_INDICES +
                                       index) = Card(suite, index);
    }
  }

  std::copy(this->complete_deck_of_cards_.begin(),
            this->complete_deck_of_cards_.end(),
            std::back_inserter(this->cards_));
}

void Deck::reset() {
  this->cards_.clear();
  std::copy(this->complete_deck_of_cards_.begin(),
            this->complete_deck_of_cards_.end(),
            std::back_inserter(this->cards_));
}

void Deck::shuffle_cards() {
  std::random_shuffle(this->cards_.begin(), this->cards_.end());
}

template <typename Dealee>
void Deck::deal_cards(Dealee &dealee, const uint8_t num_cards) {

  if (!this->is_deck_sufficient(num_cards)) {
    throw InsufficientDeckException();
  }

  for (uint8_t i = 0; i < num_cards; i++) {
    dealee.get_card(this->cards_.back());
    this->cards_.pop_back();
  }
}

bool Deck::is_deck_sufficient(const uint8_t required_num_cards) const {
  return this->cards_.size() >= required_num_cards;
}

void Deck::discard_random_cards_from_deck(const uint8_t num_cards) {
  for (uint8_t i = 0; i < num_cards; i++)
    this->cards_.pop_back();
}
