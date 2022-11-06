
/* INSTRUCTIONS
 
 * To get a list of country C's (let C be India) neighbours, run neighbour(india, X).
 * To get a list of neighbour's of C with population and area greater than it,
   run biggerPandA(X, india).
 * To get a list of countries that have a higher density than country C, run biggerD(X, india).

*/


/* DATABASE

    country(C, A) <- country C has area A
    population(C, P) <- country C has population P
    neighbour(C, N) <- country N is a neighbour of country C

*/

:- discontiguous
        country/2,
        population/2,
        neighbour/2.

country(russia, 17098242).
population(russia, 146745098).
neighbour(russia, georgia).
neighbour(russia, azerbaijan).
neighbour(russia, kazakhstan).
neighbour(russia, china).
neighbour(russia, mongolia).
neighbour(russia, north_korea).
neighbour(russia, japan).


country(china, 9596961).
population(china, 1439323776).
neighbour(china, afghanistan).
neighbour(china, bhutan).
neighbour(china, india).
neighbour(china, kazakhstan).
neighbour(china,kyrgyzstan ).
neighbour(china, laos).
neighbour(china, mongolia).
neighbour(china, myanmar).
neighbour(china, nepal).
neighbour(china, north_korea).
neighbour(china, pakistan).
neighbour(china, russia).
neighbour(china, tajikistan).
neighbour(china, vietnam).


country(india, 3287263).
population(india, 1380004385).
neighbour(india, bangladesh).
neighbour(india, bhutan).
neighbour(india, china).
neighbour(india, myanmar).
neighbour(india, nepal).
neighbour(india, afghanistan).
neighbour(india, pakistan).


country(kazakhstan, 2455034).
population(kazakhstan, 18776707).
neighbour(kazakhstan, russia).
neighbour(kazakhstan, uzbekistan).
neighbour(kazakhstan, kyrgystan).
neighbour(kazakhstan, china).


country(saudi_arabia, 2149690).
population(saudi_arabia, 34813871).
neighbour(saudi_arabia, bahrain).
neighbour(saudi_arabia, iraq).
neighbour(saudi_arabia, jordan).
neighbour(saudi_arabia, kuwait).
neighbour(saudi_arabia, oman).
neighbour(saudi_arabia, qatar).
neighbour(saudi_arabia, uae).
neighbour(saudi_arabia, yemen).


country(iran, 1648195).
population(iran, 83992949).
neighbour(iran, afghanistan).
neighbour(iran, pakistan).
neighbour(iran, turkmenistan).
neighbour(iran, azerbaijan).
neighbour(iran, armenia).
neighbour(iran, turkey).
neighbour(iran, iraq).


country(mongolia, 1564110).
population(mongolia, 3278290).
neighbour(mongolia, russia).
neighbour(mongolia, china).


country(indonesia, 1472639).
population(indonesia, 273523615).
neighbour(indonesia, timor-leste).
neighbour(indonesia, malaysia).
neighbour(indonesia, india).
neighbour(indonesia, thailand).
neighbour(indonesia, vietnam).
neighbour(indonesia, singapore).
neighbour(indonesia, philippines).


country(pakistan, 881913).
population(pakistan, 220892340).
neighbour(pakistan, china).
neighbour(pakistan, afghanistan).
neighbour(pakistan, india).
neighbour(pakistan, iran).


country(turkey, 747272).
population(turkey, 84339067).
neighbour(turkey, georgia).
neighbour(turkey, armenia).
neighbour(turkey, iran).
neighbour(turkey, iraq).
neighbour(turkey, syria).


country(myanmar, 676578).
population(myanmar, 54409800).
neighbour(myanmar, bangladesh).
neighbour(turkey, india).
neighbour(turkey, laos).
neighbour(turkey, thailand).


country(afghanistan, 652230).
population(afghanistan, 38928346).
neighbour(afghanistan, tajikistan).
neighbour(afghanistan, turkmenistan).
neighbour(afghanistan, uzbekistan).
neighbour(afghanistan, iran).
neighbour(afghanistan, pakistan).
neighbour(afghanistan, china).
neighbour(afghanistan, india).


country(yemen, 527968).
population(yemen, 29825964).
neighbour(yemen, oman).
neighbour(yemen, saudi_arabia).


country(thailand, 513120).
population(thailand, 69799978).
neighbour(thailand, cambodia).
neighbour(thailand, malaysia).
neighbour(thailand, myanmar).
neighbour(thailand, laos).


country(turkmenistan, 488100).
population(turkmenistan, 6031200).
neighbour(turkmenistan, iran).
neighbour(turkmenistan, afghanista).
neighbour(turkmenistan, uzbekistan).
neighbour(turkmenistan, kazakhstan).

country(uzbekistan, 447400).
population(uzbekistan, 33469203).
neighbour(uzbekistan, kazakhstan).
neighbour(uzbekistan, tajikistan).
neighbour(uzbekistan, afghanistan).
neighbour(uzbekistan, turkmenistan).
neighbour(uzbekistan, kyrgyzstan).


country(iraq, 438317).
population(iraq, 40222493).
neighbour(iraq, jordan).
neighbour(iraq, kuwait).
neighbour(iraq, turkey).
neighbour(iraq, syria).
neighbour(iraq, saudi_arabia).
neighbour(iraq, iran).

country(japan, 377930).
population(japan, 126474471).
neighbour(japan, china).
neighbour(japan, north_korea).
neighbour(japan, south_korea).
neighbour(japan, philippines).
neighbour(japan, russia).
neighbour(japan, taiwan).


country(vietnam, 331212).
population(vietnam, 97338579).
neighbour(vietnam, cambodia).
neighbour(vietnam, china).
neighbour(vietnam, laos).


country(malaysia, 330803).
population(malaysia, 32365999).
neighbour(malaysia, brunei).
neighbour(malaysia, indonesia).
neighbour(malaysia, thailand).
neighbour(malaysia, china).
neighbour(malaysia, philippines).
neighbour(malaysia, singapore).
neighbour(malaysia, vietnam).

country(oman, 309500).
population(oman, 5106626).
neighbour(oman, yemen).
neighbour(oman, uae).
neighbour(oman, saudi_arabia).


country(philippines, 300000).
population(philippines, 109581078).
neighbour(philippines, china).
neighbour(philippines, japan).
neighbour(philippines, vietnam).
neighbour(philippines, malaysia).
neighbour(philippines, taiwan).
neighbour(philippines, indonesia).


country(laos, 236800).
population(laos, 7275560).
neighbour(laos, cambodia).
neighbour(laos, thailand).
neighbour(laos, myanmar).
neighbour(laos, china).

country(kyrgyzstan, 199951).
population(kyrgyzstan, 6524195).
neighbour(kyrgyzstan, uzbekistan).
neighbour(kyrgyzstan, kazakhstan).
neighbour(kyrgyzstan, china).
neighbour(kyrgyzstan, tajikistan).


country(syria, 185180).
population(syria, 17500658).
neighbour(syria, lebanon).
neighbour(syria, israel).
neighbour(syria, jordan).


country(cambodia, 181035).
population(cambodia, 16718965).
neighbour(cambodia, laos).
neighbour(cambodia, thailand).
neighbour(cambodia, vietnam).


country(bangladesh, 147570).
population(bangladesh, 164689383).
neighbour(bangladesh, india).
neighbour(bangladesh, myanmar).


country(nepal, 147181).
population(nepal, 29136808).
neighbour(nepal, india).
neighbour(nepal, china).


country(tajikistan, 143100).
population(tajikistan, 9537645).
neighbour(tajikistan, china).
neighbour(tajikistan, afghanistan).
neighbour(tajikistan, uzbekistan).
neighbour(tajikistan, kyrgyzstan).


country(north_korea, 120538).
population(north_korea, 25778816).
neighbour(north_korea, china).
neighbour(north_korea, south_korea).
neighbour(north_korea, russia).


country(south_korea, 100210).
population(south_korea, 51269185).
neighbour(south_korea, north_korea).


country(jordan, 89342).
population(jordan, 10203134).
neighbour(jordan, syria).
neighbour(jordan, israel).
neighbour(jordan, iraq).
neighbour(jordan, saudi_arabia).


country(azerbaijan, 86600).
population(azerbaijan, 10139177).
neighbour(azerbaijan, russia).
neighbour(azerbaijan, iran).
neighbour(azerbaijan, armenia).
neighbour(azerbaijan, georgia).
neighbour(azerbaijan, turkey).


country(uae, 83600).
population(uae, 9890402).
neighbour(uae, saudi_arabia).
neighbour(uae, oman).
neighbour(uae, qatar).


country(georgia, 69000).
population(georgia, 3989167).
neighbour(georgia, azerbaijan).
neighbour(georgia, russia).
neighbour(georgia, armenia).
neighbour(georgia, turkey).


country(sri_lanka, 65610).
population(sri_lanka, 21413249).
neighbour(sri_lanka, india).
neighbour(sri_lanka, maldives).


country(bhutan, 38394).
population(bhutan, 771608).
neighbour(bhutan, china).
neighbour(bhutan, india).
neighbour(bhutan, myanmar).
neighbour(bhutan, bangladesh).
neighbour(bhutan, nepal).


country(taiwan, 36193).
population(taiwan, 23816775).
neighbour(taiwan, china).
neighbour(taiwan, japan).
neighbour(taiwan, philippines).


country(armenia, 29843).
population(armenia, 2963243).
neighbour(armenia, azerbaijan).
neighbour(armenia, turkey).
neighbour(armenia, georgia).
neighbour(armenia, iran).


country(kuwait, 17818).
population(kuwait, 4270571).
neighbour(kuwait, iraq).
neighbour(kuwait, saudi_arabia).


country(timor-leste, 14874).
population(timor-leste, 1318445).
neighbour(timor-leste, indonesia).


country(qatar, 11586).
population(qatar, 2881053).
neighbour(qatar, uae).
neighbour(qatar, iran).
neighbour(qatar, bahrain).
neighbour(qatar, saudi_arabia).


country(lebanon, 10452).
population(lebanon, 6825445).
neighbour(lebanon, israel).
neighbour(lebanon, syria).


country(israel, 22072).
population(israel, 8655535).
neighbour(israel, palestine).
neighbour(israel, lebanon).
neighbour(israel, syria).
neighbour(israel, jordan).


country(palestine, 6220).
population(palestine, 5101414).
neighbour(palestine, jordan).
neighbour(palestine, israel).
neighbour(palestine, syria).


country(brunei, 5765).
population(brunei, 437479).
neighbour(brunei, malaysia).


country(bahrain, 760).
population(bahrain, 1701575).
neighbour(bahrain, iran).
neighbour(bahrain, qatar).
neighbour(bahrain, saudi_arabia).


country(singapore, 697).
population(singapore, 5850342).
neighbour(singapore, thailand).
neighbour(singapore, cambodia).
neighbour(singapore, indonesia).
neighbour(singapore, philippines).
neighbour(singapore, malaysia).


country(maldives, 300).
population(maldives, 540544).
neighbour(maldives, sri_lanka).
neighbour(maldives, india).


/* RULES
 
    density(C, D) <- true if D is the population density of country C
    
    biggerPopulation(X, Y) <- true if country X has a larger polupatioin than country Y
	biggerArea(X, Y) <- true if country X has a larger area than country Y
    biggerDensity(X, Y) <- true if density of country X is greater than that of country Y
    
    biggerPandA(X, Y) <- true if countries X & Y are neighbours, and if both of 
    				  biggerPopulation(X, Y) and biggerArea(X, Y) are true
    biggerD(X, Y) <- true if countries X & Y are neighbours and X has a higher 
                  population density than Y
*/

% divides population P of country C by its area A and assigns it to density D
density(C, D) :- country(C, A), population(C, P), (D is P/A).


biggerPopulation(X, Y) :- population(X, P1), population(Y, P2), (P1>P2).
biggerArea(X, Y) :- country(X, A1), country(Y, A2), (A1>A2).
biggerDensity(X, Y) :- density(X, D1), density(Y, D2), (D1>D2).

biggerPandA(X, Y) :- neighbour(X, Y), (biggerPopulation(X, Y), biggerArea(X, Y)).
biggerD(X, Y) :- neighbour(X, Y), biggerDensity(X,Y).










