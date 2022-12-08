### --- Day 6: Tuning Trouble ---
The preparations are finally complete; you and the Elves leave camp on foot and begin to make your way toward the <span style="color:#FFFF6F">star</span> fruit grove.

As you move through the dense undergrowth, one of the Elves gives you a handheld device. He says that it has many fancy features, but the most important one to set up right now is the <b>communication system</b>.

However, because he's heard you have [<span style="color:#007F00">significant</span>](https://adventofcode.com/2016/day/6) [<span style="color:#007F00">experience</span>](https://adventofcode.com/2016/day/25) [<span style="color:#007F00">dealing</span>](https://adventofcode.com/2019/day/7) [<span style="color:#007F00">with</span>](https://adventofcode.com/2019/day/9) [<span style="color:#007F00">signal-based</span>](https://adventofcode.com/2019/day/16) [<span style="color:#007F00">systems</span>](https://adventofcode.com/2021/day/25), he convinced the other Elves that it would be okay to give you their one malfunctioning device - surely you'll have no problem fixing it.

As if inspired by comedic timing, the device emits a few colorful sparks.

To be able to communicate with the Elves, the device needs to <b>lock on to their signal</b>. The signal is a series of seemingly-random characters that the device receives one at a time.

To fix the communication system, you need to add a subroutine to the device that detects a <b>start-of-packet marker</b> in the datastream. In the protocol being used by the Elves, the start of a packet is indicated by a sequence of <b>four characters that are all different</b>.

The device will send your subroutine a datastream buffer (your puzzle input); your subroutine needs to identify the first position where the four most recently received characters were all different. Specifically, it needs to report the number of characters from the beginning of the buffer to the end of the first such four-character marker.

For example, suppose you receive the following datastream buffer:

    mjqjpqmgbljsphdztnvjfqwrcgsmlb
After the first three characters (`mjq`) have been received, there haven't been enough characters received yet to find the marker. The first time a marker could occur is after the fourth character is received, making the most recent four characters `mjqj`. Because `j` is repeated, this isn't a marker.

The first time a marker appears is after the <b>seventh</b> character arrives. Once it does, the last four characters received are `jpqm`, which are all different. In this case, your subroutine should report the value <b>7</b>, because the first start-of-packet marker is complete after 7 characters have been processed.

Here are a few more examples:

- `bvwbjplbgvbhsrlpgdmjqwftvncz`: first marker after character 5
- `nppdvjthqldpwncqszvftbrmjlhg`: first marker after character 6
- `nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg`: first marker after character 10
- `zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw`: first marker after character 11

<b>How many characters need to be processed before the first start-of-packet marker is detected?</b>

Your puzzle answer was `1920`.

### --- Part Two ---
Your device's communication system is correctly detecting packets, but still isn't working. It looks like it also needs to look for <b>messages</b>.

A <b>start-of-message marker</b> is just like a start-of-packet marker, except it consists of <b>14 distinct characters</b> rather than 4.

Here are the first positions of start-of-message markers for all of the above examples:

- mjqjpqmgbljsphdztnvjfqwrcgsmlb: first marker after character 19
- bvwbjplbgvbhsrlpgdmjqwftvncz: first marker after character 23
- nppdvjthqldpwncqszvftbrmjlhg: first marker after character 23
- nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg: first marker after character 29
- zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw: first marker after character 26

<b>How many characters need to be processed before the first start-of-message marker is detected?</b>

Your puzzle answer was `2334`.

<span style="color:#FFFF6F">Both parts of this puzzle are complete! They provide two gold stars: **</span>

At this point, you should [<span style="color:#007F00">return to your Advent calendar</span>](https://adventofcode.com/2022) and try another puzzle.

If you still want to see it, you can [<span style="color:#007F00">get your puzzle input</span>](https://adventofcode.com/2022/day/6/input).

You can also <span style="color:#007F00">[Share on [<span style="color:#007F00">Twitter</span>](https://twitter.com/intent/tweet?text=I%27ve+completed+%22Supply+Stacks%22+%2D+Day+5+%2D+Advent+of+Code+2022&url=https%3A%2F%2Fadventofcode%2Ecom%2F2022%2Fday%2F5&related=ericwastl&hashtags=AdventOfCode) or Mastodon]</span> this puzzle.
