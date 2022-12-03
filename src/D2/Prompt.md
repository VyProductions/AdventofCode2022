### --- Day 2: Rock Paper Scissors ---
The Elves begin to set up camp on the beach. To decide whose tent gets to be closest to the snack storage, a giant [<span style="color:#007F00">Rock Paper Scissors</span>](https://en.wikipedia.org/wiki/Rock_paper_scissors) tournament is already in progress.

Rock Paper Scissors is a game between two players. Each game contains many rounds; in each round, the players each simultaneously choose one of Rock, Paper, or Scissors using a hand shape. Then, a winner for that round is selected: Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. If both players choose the same shape, the round instead ends in a draw.

Appreciative of your help yesterday, one Elf gives you an <b>encrypted strategy guide</b> (your puzzle input) that they say will be sure to help you win. "The first column is what your opponent is going to play: `A` for Rock, `B` for Paper, and `C` for Scissors. The second column--" Suddenly, the Elf is called away to help with someone's tent.

The second column, you reason, must be what you should play in response: `X` for Rock, `Y` for Paper, and `Z` for Scissors. Winning every time would be suspicious, so the responses must have been carefully chosen.

The winner of the whole tournament is the player with the highest score. Your <b>total</b> score is the sum of your scores for each round. The score for a single round is the score for the <b>shape you selected</b> (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score for the <b>outcome of the round</b> (0 if you lost, 3 if the round was a draw, and 6 if you won).

Since you can't be sure if the Elf is trying to help you or trick you, you should calculate the score you would get if you were to follow the strategy guide.

For example, suppose you were given the following strategy guide:

    A Y
    B X
    C Z

This strategy guide predicts and recommends the following:

- In the first round, your opponent will choose Rock (`A`), and you should choose Paper (`Y`). This ends in a win for you with a score of 8 (2 because you chose Paper + 6 because you won).
- In the second round, your opponent will choose Paper (`B`), and you should choose Rock (`X`). This ends in a loss for you with a score of 1 (1 + 0).
- The third round is a draw with both players choosing Scissors, giving you a score of 3 + 3 = 6.

In this example, if you were to follow the strategy guide, you would get a total score of <b>15</b> (8 + 1 + 6).

<b>What would your total score be if everything goes exactly according to your strategy guide?</b>

Your puzzle answer was `13809`.

### --- Part Two ---
The Elf finishes helping with the tent and sneaks back over to you. "Anyway, the second column says how the round needs to end: `X` means you need to lose, `Y` means you need to end the round in a draw, and `Z` means you need to win. Good luck!"

The total score is still calculated in the same way, but now you need to figure out what shape to choose so the round ends as indicated. The example above now goes like this:

- In the first round, your opponent will choose Rock (`A`), and you need the round to end in a draw (`Y`), so you also choose Rock. This gives you a score of 1 + 3 = <b>4</b>.
- In the second round, your opponent will choose Paper (`B`), and you choose Rock so you lose (`X`) with a score of 1 + 0 = <b>1</b>.
- In the third round, you will defeat your opponent's Scissors with Rock for a score of 1 + 6 = <b>7</b>.

Now that you're correctly decrypting the ultra top secret strategy guide, you would get a total score of <b>12</b>.

Following the Elf's instructions for the second column, <b>what would your total score be if everything goes exactly according to your strategy guide?</b>

Your puzzle answer was `12316`.

<span style="color:#FFFF6F">Both parts of this puzzle are complete! They provide two gold stars: **</span>

At this point, you should [<span style="color:#007F00">return to your Advent calendar</span>](https://adventofcode.com/2022) and try another puzzle.

If you still want to see it, you can [<span style="color:#007F00">get your puzzle input</span>](https://adventofcode.com/2022/day/2/input).

You can also <span style="color:#007F00">[Share on [<span style="color:#007F00">Twitter</span>](https://twitter.com/intent/tweet?text=I%27ve+completed+%22Rock+Paper+Scissors%22+%2D+Day+2+%2D+Advent+of+Code+2022&url=https%3A%2F%2Fadventofcode%2Ecom%2F2022%2Fday%2F2&related=ericwastl&hashtags=AdventOfCode) or Mastodon]</span> this puzzle.