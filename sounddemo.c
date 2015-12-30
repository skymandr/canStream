// sounddemo:
// Online music examples from
//     http://countercomplex.blogspot.com/search/label/algorithmic%20music
// To test, compile, run and pipe to e.g. aplay:
//     $ gcc sounddemo.c -o sounddemo && sounddemo | aplay
// Public domain. ABSOLUTELY NO WARRANTY!

// main(t){for(t=0;;t++)putchar((t*(((t>>12)|(t>>8))&(63&(t>>4))))&64);}
main(t){for(t=0;;t++)putchar((t*(42&t>>10))&64);}
