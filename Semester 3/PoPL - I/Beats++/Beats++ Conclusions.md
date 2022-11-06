# Conclusions and Lessons Learnt


The experience of designing a language was one of a kind. However, every conclusion we arrived at boiled down to the fact that at every step of the design, we faced a tradeoff. Every decision that was made had both pros and cons.

Once again, no language is perfect. It is impossible for the designers to structure a language to suit everyone's needs and it is solely up to the designers to choose how their language is written, and which group of individuals the language is built for.

A challenging part about having to design a language from scratch was that whatever "new" idea we came up with, wasn't original. Almost everything we could think of had already been done by someone at some point. Moreover, we've already been exposed to and closely working with multiple programming languages by now, and trying to create something new posed a bit of a problem because we were already so used to the other existing languages. Thus, our process started with listing features of existing languages which we liked, and pairing them with functionality that no other language provided.

Another huge challenge was the choice of structure of the non-primitive datatypes.

The structure of these datatypes had to be carefully designed, keeping in mind:

-   The implementation of the structure had to be possible, given the currently available tools available

-   It had to be well planned, so as to provide all of the functionality that was needed. For example, the 'Sheet' and 'Measure' datatypes were designed keeping in mind easy compatibility with MIDI files, as this is the predominant file format for all things music.

We discovered that one of the most difficult parts of language design was actually restricting it to a particular domain, while still retaining enough functionality and convenience to be an actual language, rather than a library. But we realised that having a very specific use case would always beg the question: "Why not use a library?". Musical languages are not the only victim. Libraries for scientific programming are widely available in languages like C++ and Python, but there still exist programming languages which are preferred by many over the libraries.

When a language is structured around a specific function, it evolves accordingly. More than the use of the language itself, this fact influences the design stage more. With every iterative update, we saw the language evolve organically. Here, redundancy was automatically avoided because of our focus on a specific part alone.
