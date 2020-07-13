# PPasianssi solitaire game

![Cover](https://github.com/veikkos/ppasianssi/blob/master/cover.png)

PPasianssi is a solitaire game of mine which I also implemented for PC
using SDL a long time ago. It has been since ported to SDL2.

**Note:** `assets` directory is not covered by the licence.

## Rules

Regular deck is shuffled. No joker cards. Cards are drawn from top of
the deck one by one. Card is restored to bottom of the deck if it
cannot be placed on the table.

Every type has a column and every column can have three rows at
max. It leads to a 4 x 3 matrix at max.

Cards are placed to table starting from the top column. Card can only
be placed on top of same type and with smaller value. If value of the
drawn card is smaller than the card on the table, a new row is
started. If table already has 3 rows for given type, no new row is
started but card is restored to bottom of the deck.

Ace will reset the entire column to the top and ace is placed to the
top. From next draws any value (naturally of same type) can be placed
on top of the ace.

You win if you can place all the cards to the table and you lose if
you can no longer place any cards from the deck.

*Approximately 7.9 % of the games pass.*

### Playing

Just tap Space or left mouse button to draw a card. :) Key `R` resets
the game.
