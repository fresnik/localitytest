# localitytest

## How much does locality matter?

This program is a simple test that permutes loops so that a function scans a three dimensional array with a stride-1 reference pattern (good locality) versus a stride-MN reference pattern (bad locality).

## Compile the program

Just run `make`, it should work on most Linux systems.

## Usage

    ./localitytest [iterations]

Where `iterations` is the number of times to run the loops. You can skip the argument for a default of 100 iterations.

## Output

The program will tell you

* Input
 * How many iterations it will be running
 * Size of test array (hardcoded at the moment)
* Output
 * How long time is spent running the loops with bad locality
 * How long time is spent running the loops with good locality
 * The difference between the two

### Example output

Here are a couple outputs when run on my machine:

    $ ./localitytest 1000
    Running test with 1000 iterations.
    Test array is 2304000 bytes in size.
    Time spent running bad locality: 2.531270113 sec.
    Time spent running good locality: 1.863334975 sec.
    Difference between averages: 0.667935138 sec.

    $ ./localitytest 10000
    Running test with 10000 iterations.
    Test array is 2304000 bytes in size.
    Time spent running bad locality: 25.254116078 sec.
    Time spent running good locality: 18.713775802 sec.
    Difference between averages: 6.540340276 sec.

## Author

Author:  
 Freyr Bergsteinsson <freyrb12@ru.is>  

## Copyleft

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc-sa/3.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US">Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License</a>.

