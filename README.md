CANstream

This is a silly application of using the KVASER CANlib API to send data over
a CAN bus.  The programs were written with sound in mind, but any kind of
data will do, see the examples below!

Compiling:

To compile you will need Kvaser's Linux drivers and SDK, which can be found at

  https://www.kvaser.com/downloads

The drivers and SDK are released under a dual BSD/GPLv2 license. Follow the
instructions in the tar-ball to get started.

Note: For Kvaser CANlib driver versions up to and including v5.13 some kernel
modules use the __DATE__, __TIME__ and __TIMESTAMP__ macros to print build time
for debugging purposes.  In recent GCC versions (4.9+) GCC gives a warnings for
for using these macros, because these hamper making reproducible builds.  Since
the Kvaser drivers are compiled with -Werror flag by default, which causes
compile time warnings to be treated as errors.  This causes an incompatibility
between the drivers and the newer GCC versions.  The affected drivers are leaf,
mhydra and pciefd.  The problem is simple to circumvent by either removing
-Werror from the Makefiles, or by removing the offending lines (seven in
total).

Once CANlib is in place, you should be able to compile the programs by running
make in the root of the source tree.  The binaries end up in the root as well;
there is no install option.


The programs:

There are two main programs and an auxilliary program used as an example.  The
main programs are:

_upstream_

A program for reading data from stdin and sending it over the CAN bus.

_downstream_

A program for reading data from a CAN bus and sending it to stdout.

The auxilliary program is

sounddemo

An implementation of the "one line algorithmic music" examples from

    http://countercomplex.blogspot.com/search/label/algorithmic%20music

This generates a stream of chars which are written to stdout, and can be piped
to an appropriate sound player to the amusement of the listerner.


Usage guidelines:

Setting up the receiving end:

To use the programs, plug in your Kvaser devices to your computer(s). On the
receiving computer, start the listener by

  $ ./downstream

if you want written output, otherwise pipe it or divert the output to your
destination of choice.  On many systems, the following will work for playing
the stream as sound:

  $ ./downstream | aplay

(The _aplay_ program supports many different sound streams, but the default is
mono in 8000 kHz, see "man aplay" for details.)

To save the results to a file, you can use:

  $ ./downstream > mydatafile

Make sure the file doesn't contain any information you care about, since it
will be utterly overwritten if it exists.


Setting up the sender:

When the receiving end is up and running, start the sender.  If you want to
send text you can for instance send this README by issuing:

  $ cat README.md | ./upstream

However, sound is much more fun!  Test it using the sounddemo:

  $ ./sounddemo | ./upstream

If all is setup OK, and your CAN bus is properly terminated (120 Ohm -- never
forget!), then you should now receive output on your listening end, either in
writing or as sweet electronic beats!

The reason the _sounddemo_ works is that raw sound is digitally represented as
stream of bytes, which maps directly to the waveform of the sound.  The same
goes for uncompressed sound formats, such as _wav_. In fact, lets try that
next!  Under the _data_ folder, you can find a file called _CANon.wav_.  Let's
try piping its contents just like we piped this README before.  With the
_downstream_ active and piping to _aplay_ as before, try

  $ cat data/CANon.wav | ./upstream

If your ear is more attuned to classical music than to electronic, you will
likely prefer what you should now be hearing!


Advanced usage:

By default _upstream_ sends on channel 0 and _downstream_ listens on channel 1,
both with a bitrate of 100 kbit/s and with uniform id and dlc settings.  The
defaults can be overridden by command line options which are the same for both
programs; see

    $ upstream --help

for details!


Future improvements:

CAN FD support is desired in the future, for the authentic HiFi experience.


License:

The source is released under the GNU General Public License version 3 (GPLv3),
except sounddemo.c which is public domain. See COPYING.txt for deails on GPLv3!
CANon.wav is derivative of
  https://en.wikipedia.org/wiki/File:Canon_and_Gigue_in_D.ogg
by Jeffrey C. Hall, which is freely available under the Creative Commons
Attribution-Share Alike 3.0 Unported license; see

  https://creativecommons.org/licenses/by-sa/3.0/deed.en

for details!
