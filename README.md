# CANstream

This is a silly application of using the Kvaser CANlib API to send data over
a CAN bus.  The programs were written with sound in mind, but any kind of
data will do -- see the examples below!

> *Note:* The programs have not really been tested in a real CAN environment,
> in paricular CAN FD has not been tested at all. Reports of your
> user-experiences would therefore be greatly appreciated!

## Compiling:

To compile you will need Kvaser's Linux drivers and SDK, which can be found at

  https://www.kvaser.com/downloads

The drivers and SDK are released under a dual BSD/GPLv2 license. Follow the
instructions in the tar-ball to get started.

> *Note:* For Kvaser CANlib driver versions up to and including v5.13 some
> kernel modules use the `__DATE__`, `__TIME__` and `__TIMESTAMP__` macros to
> print build time for debugging purposes.  In recent GCC versions (4.9+) GCC
> gives warnings for using these macros, because these hamper making
> reproducible builds.  Since the Kvaser drivers are compiled with `-Werror`
> flag by default, which causes compile time warnings to be treated as errors,
> the use of these macros causes an incompatibility between the drivers and the
> newer GCC versions.  The affected drivers are `leaf`, `mhydra` and `pciefd`.
> The problem is simple to circumvent by either removing `-Werror` from the
> Makefiles, by removing the offending lines (seven in total), or by using
> `#pragma GCC diagnostic` as described here:
>
> https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas
>
> Of these three alternatives, the last is the most general and satisfying in my
> humble opinion, especially since on some systems another warning,
> `-Wframe-larger-than=`, can also occur, which is easiest to solve by using
> `#pragma GCC diagnostic`.  See the Dockerfile for examples of both removing
> the afflicted lines and of using `#pragma GCC diagnostic`!

Once CANlib is in place, you should be able to compile the `canStream` programs
by running `make` in the root of the source tree.  The binaries end up in the
root as well; there is no install option.


## The programs:

There are two main programs and an auxilliary program used as an example.  The
main programs are:

### `upstream`

> A program for reading data from `stdin` and sending it over the CAN bus.

### `downstream`

> A program for reading data from a CAN bus and sending it to `stdout`.

The auxilliary program is

### `sounddemo`

> An implementation of the "one line algorithmic music" examples from
>
>    http://countercomplex.blogspot.com/search/label/algorithmic%20music
>
> This generates a stream of chars which are written to stdout, and can be
> piped to an appropriate sound player to the amusement of the listener.


## Usage guidelines:

The general idea is to pipe a data source (such as an audio source) to
`upstream`, which will send it to the CAN bus, while listening with
`downstream` and piping or diverting its output to an application (such as
 an audio player) or a file.

### Setting up the receiving end:

To use the programs, plug in your Kvaser devices to your computer(s). On the
receiving computer, start the listener by

> `$ ./downstream`

if you want written output, otherwise pipe it or divert the output to your
destination of choice.  On many systems, the following will work for playing
the stream as sound:

> `$ ./downstream | aplay`

(The `aplay` program supports many different sound streams, but the default is
mono in 8000 kHz, see `man aplay` for details.)

To save the results to a file, you can use:

>  `$ ./downstream > mydatafile`

Make sure the file doesn't contain any information you care about, since it
will be utterly overwritten if it exists.


### Setting up the sender:

When the receiving end is up and running, start the sender.  If you want to
send text you can for instance send this README by issuing:

>  `$ cat README.md | ./upstream`

However, sound is much more fun!  Test it using the sounddemo:

>  `$ ./sounddemo | ./upstream`

If all is setup OK, and your CAN bus is properly terminated (120 Ohm -- never
forget!), then you should now receive output on your listening end, either in
writing or as sweet electronic beats!

The reason the `sounddemo` works is that raw sound is digitally represented as
stream of bytes, which maps directly to the waveform of the sound.  The same
goes for all uncompressed sound formats, such as `wav`. In fact, lets try that
next!  Under the `data` folder, you can find a file called `CANon.pcm`.  Let's
try piping its contents just like we piped this README before.  With the
`downstream` active and piping to `aplay` as before, try

>  `$ cat data/CANon.pcm | ./upstream`

If your ear is more attuned to classical music than to electronic, you will
likely prefer what you should now be hearing!


## Advanced usage:

By default `upstream` sends on channel 0 and `downstream` listens on channel 1,
both with a *bitrate* of 1 Mbit/s,  with uniform *dlc*, *id* and *timeout*
settings.  The defaults can be overridden by command line options which are
the same for both programs; see

>  `$ upstream --help`

for details!


## Future improvements:

Testing the software on a real CAN bus...

CAN FD support is desired in the future, for the authentic HiFi experience.
It's there and *might* work, but I have no way of testing it...


## License:

The source code of this project is released under the *GNU General Public
License version 3* (GPLv3), except `sounddemo.c` which is public domain.
See `LICENSE` for deails on GPLv3!

`CANon.pcm` is derivative of

  https://en.wikipedia.org/wiki/File:Canon_and_Gigue_in_D.ogg

by *Jeffrey C. Hall*, which is freely available under the *Creative Commons
Attribution-Share Alike 3.0 Unported* license; see

  https://creativecommons.org/licenses/by-sa/3.0/deed.en

for details!
