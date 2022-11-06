
/* DISCLAIMER:
   All data is according to available spreadsheets at the time of making the database.
*/


/* INSTRUCTIONS
 
 * To check the category of hostel N, run category(N, X).
 * To get a list of the hostels against whom N won, run won(N, X). 
 * To get a list of the hostels to whom N lost, run lost(N, X). 

*/


/* DATABASE

    won(X, Y) <- hostel X won against hostel Y in a match
*/

:- discontiguous
        won/2.

/* Pool A */
won(b, a).
won(a, d).
won(b, d).

/* Pool B */
won(g, p).
won(p, h).
won(g, h).

/* Pool C */
won(e, f).
won(f, c).
won(e, c).

/* Girls' Matches */
won(j, i).

/* Top 3 */
won(g, b).
won(g, e).
won(b, e).

/* Finals */
won(g, b).

/* RULES
 
    lost(X, Y) <- true if hostel X lost to hostel Y in a match
    
*/

lost(X, Y) :- won(Y, X).

/* PREDICATES

    category(S, C) <- team S belongs to category C
    
    Category 1 - The team has no losses.
    Category 2 - The team has both won and lost.
    Category 3 - The team has no wins.
 
 */

category(S, 1) :- (won(S, _), not(lost(S, _))), !.
category(S, 2) :- (won(S, _), lost(S, _)), !.
category(S, 3) :- (not(won(S, _)), not(not(lost(S, _)))).